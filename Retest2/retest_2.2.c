#include "../library/list/list.h"
#include "../library/values/values.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool isSymmetricList(List* list)
{
    ListElement* begin = list->head;
    ListElement* end = list->tail;
    int beginPosition = 0;
    int endPosition = getListSize(list) - 1;
    while (beginPosition < endPosition) {
        if (!equals(begin->value, end->value))
            return false;
        begin = begin->next;
        end = end->previous;
        beginPosition++;
        endPosition--;
    }
    return true;
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Input file open error!");
        return 0;
    }
    List* list = makeNewList();
    while (!feof(inputFile)) {
        int x = 0;
        fscanf(inputFile, "%i", &x);
        addListElement(list, wrapInt(x), getListSize(list));
    }
    if (isSymmetricList(list))
        printf("SYMMETRIC");
    else
        printf("ASYMMETRIC");
    deleteList(list);
    fclose(inputFile);
    return 0;
}