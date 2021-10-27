#include "binary_number.h"
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
    if (b[0] == 1)
        for (int i = 1; i < MAX_NUMBER_LENGTH; ++i) {
            if (b[i] == 0)
                b[i] = 1;
            else
                b[i] = 0;
        }
}

int* sum(int* a, int* b)
{
    int* result = calloc(sizeof(int), MAX_NUMBER_LENGTH);
    toReverseCode(a);
    toReverseCode(b);
    int carry = 0;
    for (int i = MAX_NUMBER_LENGTH - 1; i >= 0; --i) {
        int tempSum = a[i] + b[i] + carry;
        if (tempSum <= 1) {
            result[i] = tempSum;
            carry = 0;
        } else if (tempSum == 2) {
            result[i] = 0;
            carry = 1;
        } else {
            result[i] = 1;
            carry = 1;
        }
    }
    if (carry == 1) {
        for (int i = MAX_NUMBER_LENGTH - 1; i >= 0; --i) {
            int tempSum = result[i] + carry;
            if (tempSum <= 1) {
                result[i] = tempSum;
                carry = 0;
            } else if (tempSum == 2) {
                result[i] = 0;
                carry = 1;
            } else {
                result[i] = 1;
                carry = 1;
            }
        }
    }
    toReverseCode(result);
    return result;
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