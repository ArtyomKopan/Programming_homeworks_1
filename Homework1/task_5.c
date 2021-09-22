#include <stdio.h>
#include <stdlib.h>

void fillArray(int** array, int n)
{
    int nowValueForFilling = n * n;
    int i = 0, j = n - 1;
    int direction = 0;
    /* direction == 0: движение влево
     * direction == 1: движение вниз
     * direction == 2: движение вправо
     * direction == 3: движение вверх
     */
    while (nowValueForFilling > 0) {
        array[i][j] = nowValueForFilling--;
        if (direction == 0) {
            if (j - 1 < 0 || array[i][j - 1]) {
                direction = 1;
                i++;
            } else
                j--;
        } else if (direction == 1) {
            if (i + 1 >= n || array[i + 1][j]) {
                direction = 2;
                j++;
            } else
                i++;
        } else if (direction == 2) {
            if (j + 1 >= n || array[i][j + 1]) {
                direction = 3;
                i--;
            } else
                j++;
        } else {
            if (i - 1 < 0 || array[i - 1][j]) {
                direction = 0;
                j--;
            } else
                i--;
        }
    }
}

void printArray(int** array, int n)
{
    printf("An array filled with numbers from 1 to n^2 in a spiral: \n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%4i ", array[i][j]);
        printf("\n");
    }
}

int main()
{
    int n = 0;
    int** array;
    printf("Enter an integer - the size of the array: ");
    scanf("%i", &n);
    array = (int**)calloc(n, sizeof(*array));
    for (int i = 0; i < n; ++i)
        array[i] = (int*)calloc(n, sizeof(*array[i]));

    fillArray(array, n);

    printArray(array, n);

    for (int i = 0; i < n; ++i)
        free(array[i]);
    free(array);
    return 0;
}