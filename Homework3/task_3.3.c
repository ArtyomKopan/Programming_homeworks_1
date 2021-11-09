#include "binary_number.h"
#include <stdio.h>
#include <stdlib.h>

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