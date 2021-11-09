#include "binary_number.h"
#include <memory.h>
#include <stdlib.h>

int* toBinary(int x)
{
    int* binary = calloc(MAX_NUMBER_LENGTH, sizeof(int));
    if (x < 0)
        binary[0] = 1;
    x = abs(x);
    for (int i = MAX_NUMBER_LENGTH - 1; i > 0; --i) {
        binary[i] = x % 2;
        x /= 2;
    }
    return binary;
}

int firstNonZeroBit(int* b)
{
    for (int i = 1; i < MAX_NUMBER_LENGTH; ++i)
        if (b[i] == 1)
            return i;
    return 0;
}

void toReverseCode(int* b)
{
    if (b[0] == 0)
        return;
    for (int i = 1; i < MAX_NUMBER_LENGTH; ++i)
        b[i] = 1 - b[i];
}

int getCarry(const int* a, const int* b)
{
    int carry = 0;
    for (int i = MAX_NUMBER_LENGTH - 1; i >= 0; --i) {
        int tempSum = a[i] + b[i] + carry;
        carry = (tempSum <= 1) ? 0 : 1;
    }
    return carry;
}

void sum(int* a, int* b)
{
    int carry = 0;
    for (int i = MAX_NUMBER_LENGTH - 1; i >= 0; --i) {
        int tempSum = a[i] + b[i] + carry;
        a[i] = tempSum % 2;
        carry = (tempSum <= 1) ? 0 : 1;
    }
}

void add(int* a, int* b)
{
    sum(a, b);
    int carry = getCarry(a, b);
    if (carry == 1)
        sum(a, toBinary(1));
}

int toDecimal(int* b)
{
    if (firstNonZeroBit(b) == 0)
        return 0;
    int signum = b[0] == 0 ? 1 : -1;
    int x = 1;
    for (int i = firstNonZeroBit(b) + 1; i < MAX_NUMBER_LENGTH; ++i)
        x = 2 * x + b[i];
    return signum * x;
}

void rotateRight(int* b)
{
    for (int i = MAX_NUMBER_LENGTH - 1; i >= 2; --i)
        b[i] = b[i - 1];
    b[1] = 0;
}

void rotateLeft(int* b)
{
    for (int i = 1; i < MAX_NUMBER_LENGTH - 1; ++i)
        b[i] = b[i + 1];
    b[MAX_NUMBER_LENGTH - 1] = 0;
}

int* multiply(int* a, int* b)
{
    int* result = calloc(MAX_NUMBER_LENGTH, sizeof(int));
    if (a[0] != b[0])
        result[0] = 1;
    a[0] = 0;
    b[0] = 0;
    while (firstNonZeroBit(a) != 0) {
        if (a[MAX_NUMBER_LENGTH - 1] != 0)
            add(result, b);
        rotateLeft(b);
        rotateRight(a);
    }
    return result;
}