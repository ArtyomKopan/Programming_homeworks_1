#pragma once
#ifndef HOMEWORK3_BINARY_NUMBER_H
#define HOMEWORK3_BINARY_NUMBER_H

#define MAX_NUMBER_LENGTH 32

int* toBinary(int x);
void toReverseCode(int* b);
int firstNonZeroBit(int* b);
int* sum(int* a, int* b);
void add(int* a, int* b); // аналог a += b
int toDecimal(int* b);

#endif
