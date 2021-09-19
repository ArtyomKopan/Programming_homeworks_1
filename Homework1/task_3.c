#include <stdio.h>
#include <stdlib.h>

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

    for (int k = 0; k < m; ++k) {
        int temp = array[0];
        for (int i = 0; i < m + n - 1; ++i)
            array[i] = array[i + 1];
        array[m + n - 1] = temp;
    }

    /*
    if (m == n)
        for (int i = 0; i < m; ++i) {
            int temp = array[i];
            array[i] = array[m + i];
            array[m + i] = temp;
        }
    else if (m < n){
        for (int i = 0; i < m; ++i) {
            int temp = array[i];
            array[i] = array[m + i];
            array[m + i] = temp;
        }
        for (int i = 0; i < n - m; ++i) {
            int temp = array[m + i];
            array[m + i] = array[m + m + i];
            array[m + m + i] = temp;
        }
        for (int i = n, j = 2 * m; i < 2 * m, j < n + m; ++i, ++j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    else {

    }
    */

    for (int i = 0; i < m + n; ++i)
        printf("%i ", array[i]);
    free(array);
    return 0;
}