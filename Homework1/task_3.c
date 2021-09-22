#include <stdio.h>
#include <stdlib.h>

void swapBeginningWithEnd(int* array, int m, int n)
{
    for (int k = 0; k < m; ++k) {
        int temp = array[0];
        for (int i = 0; i < m + n - 1; ++i)
            array[i] = array[i + 1];
        array[m + n - 1] = temp;
    }
}

int main()
{
    int m = 0, n = 0;
    printf("Enter number m - the length of the first part of the array: ");
    scanf("%i", &m);
    printf("Enter number n - the length of the second part of the array: ");
    scanf("%i", &n);
    int* array = (int*)calloc(m + n, sizeof(int));
    printf("Enter the array elements separated by a space: ");
    for (int i = 0; i < m + n; ++i)
        scanf("%i", &array[i]);
    
    swapBeginningWithEnd(array, m, n);

    for (int i = 0; i < m + n; ++i)
        printf("%i ", array[i]);
    free(array);
    return 0;
}