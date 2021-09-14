#include <stdio.h>

int abs(int x) {
    if (x < 0)
        return -x;
    else
        return x;
}

int division(int a, int b) {
    int abs_a = abs(a);
    int abs_b = abs(b);
    int result = 0;
    while (abs_a >= abs_b) {
        abs_a -= abs_b;
        result++;
    }
    if (a < 0 && abs_a == 0)
        result = -result;
    else if (a < 0 && abs_a > 0)
        result = -result - 1;
    if (b < 0 && abs_a == 0)
        result = -result;
    else if (b < 0 && abs_a > 0)
        result = -result - 1;
    return result;
}

int main() {
    printf("Enter two integers A and B:\n");
    int a = 0, b = 0;
    printf("A =");
    scanf_s("%i", &a);
    printf("\nB =");
    scanf_s("%i", &b);
    if (b == 0)
        printf("ERROR! Division by zero!");
    else {
        int divisionResult = division(a, b);
        printf("\n");
        printf("A / B = ");
        printf("%i", divisionResult);
    }
    return 0;
}