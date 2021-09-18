#include <stdio.h>
#include <stdlib.h>

const int INF = (int)1e9;

int getMaximumMoreThanOnce(int* array, int arraySize)
{
    int maximum = -INF;
    for (int i = 0; i < arraySize; ++i)
        if (array[i] > maximum)
            for (int j = i + 1; j < arraySize; ++j)
                if (array[j] == array[i]) {
                    maximum = array[i];
                    break;
                }
    return maximum;
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
    printf("The maximum element of an array that occurs more than once: ");
    printf("%i", maximumMoreThanOnes);
    return 0;
}