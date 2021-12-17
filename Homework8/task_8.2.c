#include "../library/values/values.h"
#include "automaton.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{

    if (argc < 2) {
        printf("ERROR! Automaton description not found!");
        return 0;
    }
    FILE* automatonDescription = fopen(argv[1], "r");
    if (!automatonDescription) {
        printf("Automaton description open error!");
        return 0;
    }
    int transitionsCount = 0;
    fscanf(automatonDescription, "%i", &transitionsCount);
    Transition** transitions = malloc(transitionsCount * sizeof(Transition*));
    for (int i = 0; i < transitionsCount; ++i) {
        int from = 0;
        int to = 0;
        char type[8];
        fscanf(automatonDescription, "%i %i %s", &from, &to, type);
        if (strcmp(type, "char") == 0) {
            char transitionValue = '\0';
            fscanf(automatonDescription, " %c", &transitionValue);
            transitions[i] = createTransition(from, to, wrapChar(transitionValue));
        } else if (strcmp(type, "string") == 0) {
            char transitionValue[8];
            fscanf(automatonDescription, "%s", transitionValue);
            if (strcmp(transitionValue, "digit") == 0)
                transitions[i] = createTransition(from, to, wrapString("digit"));
            else if (strcmp(transitionValue, "letter") == 0)
                transitions[i] = createTransition(from, to, wrapString("letter"));
            else {
                printf("ERROR! Incorrect transition value!");
                return 0;
            }
        } else {
            printf("ERROR! Incorrect transition value type!");
            return 0;
        }
    }
    int startState = 0;
    fscanf(automatonDescription, "%i", &startState);
    int acceptStatesCount = 0;
    fscanf(automatonDescription, "%i", &acceptStatesCount);
    int* acceptStates = malloc(acceptStatesCount * sizeof(int));
    for (int i = 0; i < acceptStatesCount; ++i)
        fscanf(automatonDescription, "%i", &acceptStates[i]);

    Automaton* automaton = createAutomaton(transitionsCount, acceptStatesCount, transitions, acceptStates, startState);

    char* word = malloc(1024 * sizeof(char));
    printf("Enter the word to check: ");
    scanf("%s", word);

    if (isCorrect(automaton, word))
        printf("This is number!");
    else
        printf("This is not number!");

    free(word);
    deleteAutomaton(automaton);
    free(transitions);
    free(acceptStates);
    return 0;
}
