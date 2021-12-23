#include "mergeSort.h"
#include <stdlib.h>

void merge(int* array, int leftIndex, int rightIndex)
{
    int middleIndex = (leftIndex + rightIndex) / 2;
    int* sortedArray = malloc((rightIndex - leftIndex + 1) * sizeof(int));
    int leftIterator = 0;
    int rightIterator = 0;
    while (leftIndex + leftIterator < middleIndex && middleIndex + rightIterator < rightIndex) {
        if (array[leftIndex + leftIterator] <= array[middleIndex + rightIterator]) {
            sortedArray[leftIterator + rightIterator] = array[leftIndex + leftIterator];
            leftIterator++;
        } else {
            sortedArray[leftIterator + rightIterator] = array[middleIndex + rightIterator];
            rightIterator++;
        }
    }
    while (leftIndex + leftIterator < middleIndex) {
        sortedArray[leftIterator + rightIterator] = array[leftIndex + leftIterator];
        leftIterator++;
    }
    while (middleIndex + rightIterator < rightIndex) {
        sortedArray[leftIterator + rightIterator] = array[middleIndex + rightIterator];
        rightIterator++;
    }
    for (int i = 0; i < rightIndex - leftIndex; ++i)
        array[leftIndex + i] = sortedArray[i];

    free(sortedArray);
}

void mergeSort(int* array, int leftIndex, int rightIndex)
{
    if (leftIndex + 1 < rightIndex) {
        int middleIndex = (leftIndex + rightIndex) / 2;
        mergeSort(array, leftIndex, middleIndex);
        mergeSort(array, middleIndex, rightIndex);
        merge(array, leftIndex, rightIndex);
    }
}

void sort(int* array, int arraySize)
{
    mergeSort(array, 0, arraySize);
}