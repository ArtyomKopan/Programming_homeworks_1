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

ListElement* makeNewListElement(Value key, Value value)
{
    ListElement* element = malloc(sizeof(ListElement));
    element->key = key;
    element->value = value;
    element->previous = NULL;
    element->next = NULL;
    return element;
}

ListElement* getListElement(List* list, int position)
{
    if (position < 0 || position >= list->listSize)
        return NULL;
    ListElement* element = list->head;
    for (int i = 0; i < position; ++i)
        element = element->next;
    return element;
}

ListElement* getListElementByKey(List* list, Value key)
{
    for (ListElement* current = list->head; current; current = current->next)
        if (equals(current->key, key))
            return current;
    return NULL;
}

void addListElement(List* list, Value key, Value value, int position)
{
    ListElement* elementWithThisKey = getListElementByKey(list, key);
    if (elementWithThisKey) {
        elementWithThisKey->value = value;
        return;
    }
    if (position < 0 || position > list->listSize)
        return;
    ListElement* element = makeNewListElement(key, value);
    element->previous = getListElement(list, position - 1);
    element->next = element->previous ? element->previous->next : list->head;
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

void deleteListElement(List* list, int position)
{
    if (position < 0 || position >= list->listSize)
        return;
    ListElement* element = getListElement(list, position);
    if (element->next)
        element->next->previous = element->previous;
    else
        list->tail = element->previous;
    if (element->previous)
        element->previous->next = element->next;
    else
        list->head = element->next;
    free(element);
    list->listSize--;
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

int getListSize(List* list)
{
    return list->listSize;
}