#include "list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    int a = 0, b = 0;
    List* first = makeNewList();
    List* second = makeNewList();
    List* third = makeNewList();

    printf("Enter integers A and B: ");
    scanf("%i", &a);
    scanf("%i", &b);

    int temp = 0;
    while (fscanf(inputFile, "%i", &temp) != EOF) {
        if (temp < a)
            addElement(first, temp, first->listSize);
        else if (temp >= a && temp <= b)
            addElement(second, temp, second->listSize);
        else
            addElement(third, temp, third->listSize);
    }

    printList(first, outputFile);
    printList(second, outputFile);
    printList(second, outputFile);

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
