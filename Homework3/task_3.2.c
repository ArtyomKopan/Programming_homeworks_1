#include <memory.h>
#include <stdint.h>
#include <stdio.h>

int64_t abs(int64_t x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

int main()
{
    double x = 0;
    printf("Enter a real number: ");
    scanf("%lf", &x);

    int64_t i = 0;
    memcpy(&i, &x, sizeof(double));

    printf("Result: ");
    printf("%c", (i >> 63 == 0) ? '+' : '-');

    int64_t exponent = abs(i >> 52) - 1023;

    int64_t bitMask = 0;
    for (int k = 12; k < 64; ++k)
        bitMask = bitMask * 2 + 1;
    double mantissa = (double)(i & bitMask) / (double)((int64_t)1 << 52) + 1;
    printf("%lf*2^%ld", mantissa, exponent);
    return 0;
}