#pragma once
#ifndef HOMEWORK2_LIST_H
#define HOMEWORK2_LIST_H

#include <bits/types/FILE.h>
#include <stdbool.h>
#include "values.h"

typedef struct ListElement {
    Value data;
    struct ListElement* previous;
    struct ListElement* next;
} ListElement;

typedef struct List {
    ListElement* head;
    ListElement* tail;
    int listSize;
} List;

List* makeNewList();
void deleteList(List* list);
ListElement* getListElement(List* list, int position);
void addElement(List* list, Value data, int position);
void deleteElement(List* list, int position);
int getListSize(List* list);

#endif