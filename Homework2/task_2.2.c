#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// ищет индекс первого вхождения последовательности pattern в список lst
int search(List* lst, char pattern[])
{
    int index = 0;
    ListElement* currentElement = lst->head;
    while (currentElement) {
        if (currentElement->data == pattern[0]) {
            ListElement* now = currentElement;
            bool found = true;
            for (int j = 1; j < strlen(pattern); ++j) {
                now = now->next;
                if (now == NULL || now->data != pattern[j]) {
                    found = false;
                    break;
                }
            }
            if (found)
                return index;
        }
        index++;
        currentElement = currentElement->next;
    }
    return -1;
}

void insert(List* lst, char start[], char fragment[])
{
    int startIndex = search(lst, start) + strlen(start);
    for (int i = 0; i < strlen(fragment); ++i)
        addElement(lst, fragment[i], startIndex + i);
}

void delete (List* lst, char start[], char end[])
{
    int startIndex = search(lst, start);
    int endIndex = search(lst, end) + strlen(end);
    for (int i = startIndex; i < endIndex; ++i)
        deleteElementByIndex(lst, startIndex);
}

void replace(List* lst, char* template, char* fragment)
{
    int startIndex = search(lst, template);
    delete (lst, template, template);
    for (int i = 0; i < strlen(fragment); ++i)
        addElement(lst, fragment[i], startIndex + i);
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("File open error!");
        return 0;
    }

    List* lst = makeNewList();

    int lengthDNA = 0, operationsCount = 0;
    fscanf(inputFile, "%i", &lengthDNA);
    char dna[lengthDNA + 1];

    fscanf(inputFile, "%s", dna);
    for (int i = 0; i < lengthDNA; ++i)
        addElement(lst, dna[i], i);
    fscanf(inputFile, "%i", &operationsCount);

    for (int k = 0; k < operationsCount; ++k) {
        char operation[8];
        fscanf(inputFile, "%s", operation);
        if (strcmp(operation, "INSERT") == 0) {
            char start[128];
            char fragment[128];
            fscanf(inputFile, "%s %s", start, fragment);
            insert(lst, start, fragment);
        } else if (strcmp(operation, "DELETE") == 0) {
            char start[128];
            char end[128];
            fscanf(inputFile, "%s %s", start, end);
            delete (lst, start, end);
        } else {
            char template[128];
            char fragment[128];
            fscanf(inputFile, "%s %s", template, fragment);
            replace(lst, template, fragment);
        }
        printListAsString(lst, outputFile);
    }
    deleteList(lst);
    fclose(inputFile);
    fclose(outputFile);
    printf("Data processing was successful!");
    return 0;
}