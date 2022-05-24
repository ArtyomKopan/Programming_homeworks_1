#include "automaton.h"
#include "../library/list/list.h"
#include "../library/values/values.h"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

struct Transition {
    int from;
    int to;
    Value transitionValue;
};

struct Automaton {
    int transitionsCount;
    int acceptStatesCount;
    Transition** transitions;
    int* acceptStates;
    int startState;
};

Automaton* createAutomaton(int transitionsCount, int acceptStatesCount, Transition** transitions, int* acceptStates, int startState)
{
    Automaton* automaton = malloc(sizeof(Automaton));
    automaton->transitionsCount = transitionsCount;
    automaton->acceptStatesCount = acceptStatesCount;
    automaton->startState = startState;
    automaton->transitions = malloc(transitionsCount * sizeof(Transition));
    automaton->acceptStates = malloc(acceptStatesCount * sizeof(int));
    for (int i = 0; i < transitionsCount; ++i)
        automaton->transitions[i] = transitions[i];
    for (int i = 0; i < acceptStatesCount; ++i)
        automaton->acceptStates[i] = acceptStates[i];
    return automaton;
}

Transition* createTransition(int from, int to, Value transitionValue)
{
    Transition* transition = malloc(sizeof(Transition));
    transition->from = from;
    transition->to = to;
    transition->transitionValue = transitionValue;
    return transition;
}

void deleteAutomaton(Automaton* automaton)
{
    for (int i = 0; i < automaton->transitionsCount; ++i)
        free(automaton->transitions[i]);
    free(automaton->transitions);
    free(automaton->acceptStates);
    free(automaton);
}

bool isAccept(Automaton* automaton, int state)
{
    for (int i = 0; i < automaton->acceptStatesCount; ++i)
        if (automaton->acceptStates[i] == state)
            return true;
    return false;
}

bool isLetter(char symbol)
{
    return (symbol >= 'A' && symbol <= 'Z') || (symbol >= 'a' && symbol <= 'z');
}

bool isDigit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}

bool isCorrectTransition(Value transitionValue, char* pointer)
{
    return (transitionValue.type == CHAR_TYPE && *pointer == getChar(transitionValue)) || (transitionValue.type == STRING_TYPE && strcmp(getString(transitionValue), "digit") == 0 && isDigit(*pointer)) || (transitionValue.type == STRING_TYPE && strcmp(getString(transitionValue), "letter") == 0 && isLetter(*pointer));
}

bool isCorrect(Automaton* automaton, char* word)
{
    if (strlen(word) == 0)
        return false;
    int currentState = automaton->startState;
    for (char* pointer = word; *pointer != '\0'; pointer++) {
        bool isMoved = false;
        List* possibleTransitions = makeNewList();
        for (int i = 0; i < automaton->transitionsCount; ++i)
            if (automaton->transitions[i]->from == currentState)
                addListElement(possibleTransitions, wrapPointer(automaton->transitions[i]),
                    getListSize(possibleTransitions));
        for (ListElement* element = possibleTransitions->head; element; element = element->next) {
            Transition* transition = (Transition*)getPointer(element->value);
            Value transitionValue = transition->transitionValue;
            if (isCorrectTransition(transitionValue, pointer)) {
                currentState = transition->to;
                isMoved = true;
                break;
            }
        }
        if (!isMoved)
            return false;
        deleteList(possibleTransitions);
    }
    return isAccept(automaton, currentState);
}
