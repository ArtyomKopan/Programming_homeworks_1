#include "../library/list/list.h"
#include "../library/values/values.h"
#include <stdio.h>
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

typedef struct Pair {
    int first;
    int second;
} Pair;

int main()
{
    List* list = makeNewList();
    printf("Enter array elements: ");
    int x = 0;
    scanf("%i", &x);
    while (x != 0) {
        addListElement(list, wrapInt(x), getListSize(list));
        scanf("%i", &x);
    }
    const int arraySize = getListSize(list);
    int* array = malloc(arraySize * sizeof(int));
    int k = 0;
    for (ListElement* current = list->head; current; current = current->next)
        array[k++] = getInt(current->value);
    sort(array, arraySize);
    List* counts = makeNewList();
    printf("%i ", array[0]);
    int count = 1;
    for (int i = 1; i < arraySize; ++i) {
        if (array[i] == array[i - 1])
            count++;
        else {
            Pair* pair = malloc(sizeof(Pair));
            pair->first = array[i - 1];
            pair->second = count;
            addListElement(counts, wrapPointer(pair), getListSize(counts));
            printf("%i ", array[i]);
            count = 1;
        }
    }
    Pair* pair = malloc(sizeof(Pair));
    pair->first = array[arraySize - 1];
    pair->second = count;
    addListElement(counts, wrapPointer(pair), getListSize(counts));
    printf("\n");
    for (ListElement* current = counts->head; current; current = current->next) {
        int number = ((Pair*)getPointer(current->value))->first;
        int numberCount = ((Pair*)getPointer(current->value))->second;
        printf("%i : %i\n", number, numberCount);
    }

    free(list);
    free(array);
    for (ListElement* current = counts->head; current; current = current->next)
        free(current);
    free(counts);
    return 0;
}