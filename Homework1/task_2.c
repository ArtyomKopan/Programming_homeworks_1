#include <stdio.h>
#include <stdlib.h>

int getMaximumMoreThanOnce(int* array, int arraySize)
{
    int indexOfMaximum = -1;
    for (int i = 0; i < arraySize; ++i)
        if (indexOfMaximum == -1 || array[i] > array[indexOfMaximum])
            for (int j = i + 1; j < arraySize; ++j)
                if (array[j] == array[i]) {
                    indexOfMaximum = i;
                    break;
                }
    return indexOfMaximum;
}

int main()
{
    int arraySize = 0;
    printf("Enter the number of elements of the array: ");
    scanf("%i", &arraySize);
    printf("\nEnter array elements separated by space: ");
    int* array = (int*)calloc(arraySize, sizeof(int));
    for (int i = 0; i < arraySize; ++i)
        scanf("%i", &array[i]);

    int maximumMoreThanOnes = getMaximumMoreThanOnce(array, arraySize);
    if (maximumMoreThanOnes == -1)
        printf("There is no maximum value that occurs more than once ");
    else {
        printf("The maximum element of an array that occurs more than once: ");
        printf("%i", array[maximumMoreThanOnes]);
    }
    free(array);
    return 0;
}