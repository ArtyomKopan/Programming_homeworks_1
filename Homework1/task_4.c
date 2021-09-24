#include <stdbool.h>
#include <stdio.h>

bool isPrime(int x)
{
    for (int probe = 2; probe < x; ++probe)
        if (x % probe == 0)
            return false;
    return true;
}

int main()
{
    printf("Enter the upper limit of the range of prime numbers:");
    int border = 0;
    scanf("%i", &border);
    if (border <= 1)
        printf("There are no primes in this range");
    else {
        printf("Prime numbers not exceeding border:\n");
        for (int x = 2; x <= border; ++x)
            if (isPrime(x))
                printf("%i ", x);
    }
    return 0;
}