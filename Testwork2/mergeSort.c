#include "mergeSort.h"
#include <stdlib.h>

void merge(int* array, int left, int right)
{
    int middle = (left + right) / 2;
    int* result = malloc((right - left + 1) * sizeof(int));
    int iterator1 = 0;
    int iterator2 = 0;
    while (left + iterator1 < middle && middle + iterator2 < right) {
        if (array[left + iterator1] >= array[middle + iterator2]) {
            result[iterator1 + iterator2] = array[left + iterator1];
            ++iterator1;
        } else {
            result[iterator1 + iterator2] = array[middle + iterator2];
            ++iterator2;
        }
    }
    while (left + iterator1 < middle) {
        result[iterator1 + iterator2] = array[left + iterator1];
        ++iterator1;
    }
    while (middle + iterator2 < right) {
        result[iterator1 + iterator2] = array[middle + iterator2];
        ++iterator2;
    }
    for (int i = 0; i < right - left; ++i)
        array[left + i] = result[i];

    free(result);
}

void mergeSort(int* array, int left, int right)
{
    if (left + 1 < right) {
        int middle = (left + right) / 2;
        mergeSort(array, left, middle);
        mergeSort(array, middle, right);
        merge(array, left, right);
    }
}

void sort(int* array, int arraySize)
{
    mergeSort(array, 0, arraySize);
}