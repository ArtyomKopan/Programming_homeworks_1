#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(int* array, int arraySize)
{
    for (int i = 1; i < arraySize; ++i) {
        int j = i - 1;
        while (j >= 0 && array[j] > array[j + 1]) {
            int temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
            j--;
        }
    }
}

int main()
{
    char mode[8];
    int arraySize = 0;
    printf("Enter array size: ");
    scanf("%i", &arraySize);
    int* array = malloc(arraySize * sizeof(int));
    printf("Enter CONSOLE if you want to enter array values from the console, or enter RANDOM if you want to populate the array with random numbers: ");
    scanf("%s", mode);
    if (strcmp(mode, "CONSOLE") == 0 || strcmp(mode, "console") == 0 || strcmp(mode, "Console") == 0) {
        printf("Enter array elements: ");
        for (int i = 0; i < arraySize; ++i)
            scanf("%i", &array[i]);
    } else if (strcmp(mode, "RANDOM") == 0 || strcmp(mode, "random") == 0 || strcmp(mode, "Random") == 0) {
        for (int i = 0; i < arraySize; ++i)
            array[i] = rand() % (42 - 11 + 1) + 11;
    } else {
        printf("Incorrect input!");
        return 0;
    }

    int evenIndexesCount = arraySize % 2 == 0 ? arraySize / 2 : arraySize / 2 + 1;
    int* evenIndexes = malloc(evenIndexesCount * sizeof(int));
    for (int i = 0; i < arraySize; i += 2)
        evenIndexes[i / 2] = array[i];
    insertionSort(evenIndexes, evenIndexesCount);
    for (int i = 0; i < evenIndexesCount; ++i)
        array[2 * i] = evenIndexes[i];

    for (int i = 0; i < arraySize; ++i)
        printf("%i ", array[i]);

    free(array);
    free(evenIndexes);
    return 0;
}