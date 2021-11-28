#include "automaton.h"
#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    /*
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
    Transition** transitions = malloc(transitionsCount * sizeof(Transition));
    for (int i = 0; i < transitionsCount; ++i) {
        int from = 0;
        int to = 0;
        char type[8];
        fscanf(automatonDescription, "%i %i %s", &from, &to, type);
        if (strcmp(type, "char") == 0) {
            char transitionValue = '\0';
            fscanf(automatonDescription, "%c", &transitionValue);
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
    int acceptStatesCount = 0;
    fscanf(automatonDescription, "%i", &acceptStatesCount);
    int* acceptStates = malloc(acceptStatesCount * sizeof(int));
    for (int i = 0; i < acceptStatesCount; ++i)
        fscanf(automatonDescription, "%i", &acceptStates[i]);

    */
    int transitionsCount = 16;
    int acceptStatesCount = 3;
    int* acceptStates = malloc(acceptStatesCount * sizeof(int));
    acceptStates[0] = 2;
    acceptStates[1] = 4;
    acceptStates[2] = 7;

    Transition** transitions = malloc(transitionsCount * sizeof(Transition));
    transitions[0] = createTransition(0, 2, wrapString("digit"));
    transitions[1] = createTransition(0, 1, wrapChar('+'));
    transitions[2] = createTransition(0, 1, wrapChar('-'));
    transitions[3] = createTransition(0, 3, wrapChar('.'));
    transitions[4] = createTransition(1, 2, wrapString("digit"));
    transitions[5] = createTransition(2, 2, wrapString("digit"));
    transitions[6] = createTransition(2, 3, wrapChar('.'));
    transitions[7] = createTransition(2, 5, wrapChar('E'));
    transitions[8] = createTransition(3, 4, wrapString("digit"));
    transitions[9] = createTransition(4, 4, wrapString("digit"));
    transitions[10] = createTransition(4, 5, wrapChar('E'));
    transitions[11] = createTransition(5, 7, wrapString("digit"));
    transitions[12] = createTransition(5, 6, wrapChar('+'));
    transitions[13] = createTransition(5, 6, wrapChar('-'));
    transitions[14] = createTransition(6, 7, wrapString("digit"));
    transitions[15] = createTransition(7, 7, wrapString("digit"));

    Automaton* automaton = createAutomaton(transitionsCount, acceptStatesCount, transitions, acceptStates);

    char* word = malloc(1024 * sizeof(char));
    printf("Enter the word to check: ");
    scanf("%s", word);

    if (isCorrect(automaton, word, 0))
        printf("This is number!");
    else
        printf("This is not number!");

    free(word);
    deleteAutomaton(automaton);
    free(transitions);
    free(acceptStates);
    return 0;
}
