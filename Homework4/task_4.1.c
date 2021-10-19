#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arraySize = 0;
    printf("Enter size of array: ");
    scanf("%i", &arraySize);
    int* array = malloc(arraySize * sizeof(int));
    printf("Enter array elements separated by space: ");
    for (int i = 0; i < arraySize; ++i)
        scanf("%i", &array[i]);

    sort(array, arraySize);

    for (int i = 0; i < arraySize; ++i)
        printf("%i ", array[i]);

    free(array);
    return 0;
}
