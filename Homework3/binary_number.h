#pragma once
#ifndef HOMEWORK3_BINARY_NUMBER_H
#define HOMEWORK3_BINARY_NUMBER_H

#define MAX_NUMBER_LENGTH 33 // 32 бита под число + 1 бит под знак

int* toBinary(int x);
void toReverseCode(int* b);
int firstNonZeroBit(int* b);
int* sum(int* a, int* b);
int toDecimal(int* b);

#endif
