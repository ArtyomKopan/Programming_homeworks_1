#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b)
{
    int result = 0, signum = 0;
    if ((a >= 0 && b >= 0) || (a < 0 && b < 0))
        signum = 1;
    else
        signum = -1;
    a = abs(a);
    b = abs(b);
    while (a != 0) {
        if (a % 2 != 0)
            result += b;
        b <<= 1;
        a >>= 1;
    }
    return signum * result;
}

int main()
{
    int a = 0, b = 0;
    printf("Enter the first number: ");
    scanf("%i", &a);
    printf("Enter the second number: ");
    scanf("%i", &b);

    printf("Product of these numbers = %i", multiply(a, b));
    return 0;
}