#include "list.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

List* makeNewList()
{
    List* list = malloc(sizeof(List));
    list->head = NULL;
    list->tail = NULL;
    list->listSize = 0;
    return list;
}

ListElement* makeNewListElement(char data)
{
    ListElement* element = malloc(sizeof(ListElement));
    element->data = data;
    element->previous = NULL;
    element->next = NULL;
    return element;
}

ListElement* get(List* list, int position)
{
    if (position < 0 || position >= list->listSize)
        return NULL;
    if (position == 0)
        return list->head;
    ListElement* element = list->head;
    for (int i = 0; i < position; ++i)
        element = element->next;
    return element;
}

void addElement(List* list, char data, int position)
{
    if (position < 0 || position > list->listSize)
        return;
    ListElement* element = makeNewListElement(data);
    element->previous = get(list, position - 1);
    if (position == 0)
        element->next = list->head;
    else
        element->next = element->previous ? element->previous->next : NULL;
    if (element->next)
        element->next->previous = element;
    else
        list->tail = element;
    if (element->previous)
        element->previous->next = element;
    else
        list->head = element;
    list->listSize++;
}

void addElements(List* list, char* data, int dataSize, int position)
{
    if (position < 0 || position > list->listSize)
        return;
    ListElement* previous = get(list, position - 1);
    ListElement* next = get(list, position);
    ListElement** temp = malloc(sizeof(ListElement) * dataSize);
    for (int i = 0; i < dataSize; ++i)
        temp[i] = makeNewListElement(data[i]);
    for (int i = 0; i < dataSize; ++i) {
        if (i > 0)
            temp[i]->previous = temp[i - 1];
        if (i < dataSize - 1)
            temp[i]->next = temp[i + 1];
    }
    if (list->listSize == 0) {
        list->head = temp[0];
        list->tail = temp[dataSize - 1];
    } else if (list->listSize == 1) {
        if (position == 0) {
            temp[dataSize - 1]->next = list->head;
            list->head->previous = temp[dataSize - 1];
            list->head = temp[0];
        } else {
            temp[0]->previous = list->tail;
            list->tail->next = temp[0];
            list->tail = temp[dataSize - 1];
        }
    } else if (!previous) {
        temp[dataSize - 1]->next = list->head;
        list->head->previous = temp[dataSize - 1];
        list->head = temp[0];
    } else if (!next) {
        temp[0]->previous = list->tail;
        list->tail->next = temp[0];
        list->tail = temp[dataSize - 1];
    } else {
        temp[0]->previous = previous;
        previous->next = temp[0];
        temp[dataSize - 1]->next = next;
        next->previous = temp[dataSize - 1];
    }
    list->listSize += dataSize;
    free(temp);
}

void deleteElement(List* list, int position)
{
    if (position < 0 || position >= list->listSize)
        return;
    ListElement* element = get(list, position);
    element->next->previous = element->previous;
    element->previous->next = element->next;
    if (position == 0)
        list->head = element->next;
    if (position == list->listSize - 1)
        list->tail = element->previous;
    free(element);
    list->listSize--;
}

// удаляет элементы с номерами start <= position <= end
void deleteRange(List* list, int start, int end)
{
    if (list->listSize == 0 || start < 0 || end < 0 || start >= list->listSize || end >= list->listSize || start > end)
        return;
    if (list->listSize == 1) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->listSize = 0;
        return;
    }
    ListElement* previous = get(list, start - 1);
    ListElement* next = get(list, end + 1);
    if (!previous) {
        ListElement* temp = NULL;
        for (ListElement* current = list->head; current != next;) {
            temp = current->next;
            free(current);
            current = temp;
        }
        list->head = next;
    } else if (!next) {
        ListElement* temp = NULL;
        for (ListElement* current = previous->next; current != next;) {
            temp = current->next;
            free(current);
            current = temp;
        }
        list->tail = previous;
    } else {
        ListElement* temp = NULL;
        for (ListElement* current = previous->next; current != next;) {
            temp = current->next;
            free(current);
            current = temp;
        }
        previous->next = next;
        next->previous = previous;
    }
    list->listSize -= (end - start + 1);
}

void deleteList(List* list)
{
    ListElement* nextElement = NULL;
    for (ListElement* currentElement = list->head; currentElement; currentElement = nextElement) {
        nextElement = currentElement->next;
        free(currentElement);
    }
    free(list);
}

void printList(List* list, FILE* outputFile)
{
    for (ListElement* currentElement = list->head; currentElement; currentElement = currentElement->next)
        fprintf(outputFile, "%c", currentElement->data);
    fprintf(outputFile, "\n");
}