#include <stdio.h>

int power2(int x)
{
    return 1 << x;
}

int log2(double x)
{
    if (x == 0)
        return 0;
    int i = 0;
    int power = power2(i);
    while (x > power)
        power = power2(++i);
    if (x == power)
        return i;
    else
        return i - 1;
}

int main()
{
    double x = 0;
    printf("Enter a real number: ");
    scanf("%lf", &x);
    printf("Result: ");

    if (x < 0) {
        printf("%s", "-");
        x = -x;
    } else if (x > 0)
        printf("%s", "+");

    int exponent = log2(x);
    double mantissa = x / power2(exponent);
    printf("%lf*2^%i", mantissa, exponent);
    return 0;
}