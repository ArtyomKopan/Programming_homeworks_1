#include <stdint.h>
#include <stdio.h>

int64_t fibonacci(int n)
{
    if (n == 0)
        return 0;
    int64_t fib0 = 0;
    int64_t fib1 = 1;
    for (int i = 1; i < n; ++i) {
        int64_t temp = fib0 + fib1;
        fib0 = fib1;
        fib1 = temp;
    }
    return fib1;
}

int main()
{
    int n = 0;
    printf("Enter integer N as number of the Fibonacci number: ");
    scanf("%i", &n);
    if (n < 0)
        printf("The number must be positive!");
    else if (n > 90)
        printf("N is too large!");
    else
        printf("Fibonacci number with number N: %ld", fibonacci(n));
    return 0;
}