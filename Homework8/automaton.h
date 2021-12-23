#pragma once
#ifndef HOMEWORK8_AUTOMATON_H
#define HOMEWORK8_AUTOMATON_H

#include "../library/values/values.h"
#include <stdbool.h>

typedef struct Transition Transition;
typedef struct Automaton Automaton;

Transition* createTransition(int from, int to, Value transitionValue);

Automaton* createAutomaton(int transitionsCount, int acceptStatesCount, Transition** transitions, int* acceptStates, int startState);
void deleteAutomaton(Automaton* automaton);

bool isCorrect(Automaton* automaton, char* word);

#endif
