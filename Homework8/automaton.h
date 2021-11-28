#pragma once
#ifndef HOMEWORK8_AUTOMATON_H
#define HOMEWORK8_AUTOMATON_H

#include "values.h"
#include <stdbool.h>

typedef struct Transition {
    int from;
    int to;
    Value transitionValue;
} Transition;

typedef struct Automaton {
    int transitionsCount;
    int acceptStatesCount;
    Transition** transitions;
    int* acceptStates;
} Automaton;

Transition* createTransition(int from, int to, Value transitionValue);

Automaton* createAutomaton(int transitionsCount, int acceptStatesCount, Transition** transitions, int* acceptStates);
void deleteAutomaton(Automaton* automaton);

bool isCorrect(Automaton* automaton, char* word, int startState);

#endif
