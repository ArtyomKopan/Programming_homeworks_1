#include "binary_number.h"
#include <stdio.h>
#include <stdlib.h>

void printBinaryNumber(int* b)
{
    printf("%c", (b[0] == 0) ? '+' : '-');
    for (int i = firstNonZeroBit(b); i < MAX_NUMBER_LENGTH; ++i)
        printf("%i", b[i]);
}

int main()
{
    int x = 0;
    int y = 0;
    printf("Enter the first number: ");
    scanf("%i", &x);
    printf("Enter the second number: ");
    scanf("%i", &y);

    int* a = toBinary(x);
    int* b = toBinary(y);

    printf("The first number in binary notation: ");
    printBinaryNumber(a);
    printf("\nThe second number in binary notation: ");
    printBinaryNumber(b);

    int* s = sum(a, b);
    printf("\nFirst number + Second number = ");
    printBinaryNumber(s);
    printf(" in binary format\n");
    printf("First number + Second number = %i in decimal format", toDecimal(s));

    free(a);
    free(b);
    free(s);
    return 0;
}