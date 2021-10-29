#include "binary_number.h"
#include <stdio.h>
#include <stdlib.h>

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
            // result = sum(result, b);
            add(result, b);
        rotateLeft(b);
        rotateRight(a);
    }
    return result;
}

int main()
{
    int a = 0;
    int b = 0;
    printf("Enter the first number: ");
    scanf("%i", &a);
    printf("Enter the second number: ");
    scanf("%i", &b);

    int* binaryA = toBinary(a);
    int* binaryB = toBinary(b);

    int* product = multiply(binaryA, binaryB);
    printf("Product of these numbers = %i", toDecimal(product));

    free(binaryA);
    free(binaryB);
    free(product);
    return 0;
}