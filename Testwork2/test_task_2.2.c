#include "mergeSort.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vasyaNotesCount = 0;
    printf("Enter the Vasya's notes count: ");
    scanf("%i", &vasyaNotesCount);
    int* vasyaNotes = malloc(vasyaNotesCount * sizeof(int));
    printf("Enter Vasya's notes: ");
    for (int i = 0; i < vasyaNotesCount; ++i)
        scanf("%i", &vasyaNotes[i]);
    int petyaNotesCount = 0;
    printf("Enter the Petya's notes count: ");
    scanf("%i", &petyaNotesCount);
    int* petyaNotes = malloc(petyaNotesCount * sizeof(int));
    printf("Enter Petya's notes: ");
    for (int i = 0; i < petyaNotesCount; ++i)
        scanf("%i", &petyaNotes[i]);

    int* unitedArray = malloc((vasyaNotesCount + petyaNotesCount) * sizeof(int));
    for (int i = 0; i < vasyaNotesCount; ++i)
        unitedArray[i] = vasyaNotes[i];
    for (int i = 0; i < petyaNotesCount; ++i)
        unitedArray[vasyaNotesCount + i] = petyaNotes[i];
    sort(unitedArray, vasyaNotesCount + petyaNotesCount);

    printf("Sorted array: ");
    for (int i = 0; i < vasyaNotesCount + petyaNotesCount; ++i)
        printf("%i ", unitedArray[i]);

    free(vasyaNotes);
    free(petyaNotes);
    free(unitedArray);
    return 0;
}