#include "list.h"
#include <stdio.h>
#include <string.h>

// ищет индекс первого вхождения последовательности pattern в список list строго после позиции after
int search(List* list, char* pattern, int after)
{
    int index = 0;
    for (ListElement* current = get(list, after + 1); current; current = current->next) {
        ListElement* element = current;
        for (char* pointer = pattern;; pointer++) {
            if (!*pointer)
                return index;
            if (!element || element->data != *pointer)
                break;
            element = element->next;
        }
        index++;
    }
    return -1;
}

void insert(List* list, char* start, char* fragment)
{
    int startIndex = search(list, start, -1) + strlen(start);
    addElements(list, fragment, strlen(fragment), startIndex);
}

void deleteFragment(List* list, char* start, char* end)
{
    int startIndex = search(list, start, -1);
    int endIndex = search(list, end, startIndex + strlen(start) - 1) + strlen(end);
    deleteRange(list, startIndex, endIndex - 1);
}

void replace(List* list, char* template, char* fragment)
{
    int startIndex = search(list, template, -1);
    deleteFragment(list, template, template);
    addElements(list, fragment, strlen(fragment), startIndex);
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if (!inputFile && !outputFile) {
        printf("Input and output file open error!");
        return 0;
    } else if (!inputFile) {
        printf("Input file open error!");
        fclose(outputFile);
        return 0;
    } else if (!outputFile) {
        printf("Output file open error!");
        fclose(inputFile);
        return 0;
    }

    List* list = makeNewList();

    int lengthDNA = 0;
    int operationsCount = 0;
    fscanf(inputFile, "%i", &lengthDNA);
    char dna[lengthDNA + 1];

    fscanf(inputFile, "%s", dna);
    addElements(list, dna, lengthDNA, 0);
    fscanf(inputFile, "%i", &operationsCount);

    for (int k = 0; k < operationsCount; ++k) {
        char operation[8];
        fscanf(inputFile, "%s", operation);
        if (strcmp(operation, "INSERT") == 0) {
            char start[128];
            char fragment[128];
            fscanf(inputFile, "%s %s", start, fragment);
            insert(list, start, fragment);
        } else if (strcmp(operation, "DELETE") == 0) {
            char start[128];
            char end[128];
            fscanf(inputFile, "%s %s", start, end);
            deleteFragment(list, start, end);
        } else {
            char template[128];
            char fragment[128];
            fscanf(inputFile, "%s %s", template, fragment);
            replace(list, template, fragment);
        }
        printList(list, outputFile);
    }
    deleteList(list);
    fclose(inputFile);
    fclose(outputFile);
    printf("Data processing was successful!");
    return 0;
}