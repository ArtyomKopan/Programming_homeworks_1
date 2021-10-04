#include "list.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

List* makeNewList()
{
    List* lst = malloc(sizeof(List));
    lst->head = NULL;
    lst->tail = NULL;
    lst->listSize = 0;
    return lst;
}

int getListSize(List* lst)
{
    return lst->listSize;
}

ListElement* makeNewListElement(char data)
{
    ListElement* element = malloc(sizeof(ListElement));
    element->data = data;
    element->prev = NULL;
    element->next = NULL;
    return element;
}

void addElement(List* lst, char data, int position)
{
    // если position больше, чем длина списка, то элемент вставляется в конец
    ListElement* newElement = makeNewListElement(data);
    if (lst->head == NULL) {
        lst->head = newElement;
        lst->tail = newElement;
    } else if (position == 0) {
        newElement->next = lst->head;
        lst->head = newElement;
    } else if (lst->listSize >= position) {
        lst->tail->next = newElement;
        newElement->prev = lst->tail;
        lst->tail = newElement;
    } else {
        ListElement* prevElement = lst->head;
        for (int i = 0; i < position - 1; ++i)
            prevElement = prevElement->next;
        ListElement* nextElement = prevElement->next;
        newElement->prev = prevElement;
        prevElement->next = newElement;
        newElement->next = nextElement;
        nextElement->prev = newElement;
    }
    lst->listSize++;
}

void deleteElementByIndex(List* lst, int position)
{
    if (position < 0 || position >= getListSize(lst))
        return;
    ListElement* currentElement = lst->head;
    for (int i = 0; i < getListSize(lst); ++i) {
        if (i == position) {
            if (i != getListSize(lst) - 1)
                (currentElement->next)->prev = currentElement->prev;
            (currentElement->prev)->next = currentElement->next;
            free(currentElement);
            lst->listSize--;
            break;
        }
        currentElement = currentElement->next;
    }
}

void deleteList(List* lst)
{
    ListElement* currentElement = lst->head;
    ListElement* nextElement = NULL;
    while (currentElement) {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    free(lst);
}

void printListAsString(List* lst, FILE* outputFile)
{
    char str[2048];
    ListElement* currentElement = lst->head;
    int index = 0;
    while (currentElement) {
        str[index++] = currentElement->data;
        currentElement = currentElement->next;
    }
    fprintf(outputFile, "%s", str);
    fprintf(outputFile, "\n");
}
