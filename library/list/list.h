#pragma once
#ifndef HOMEWORK2_LIST_H
#define HOMEWORK2_LIST_H

#include "../values/values.h"
#include <bits/types/FILE.h>
#include <stdbool.h>

typedef struct ListElement {
    Value value;
    struct ListElement* previous;
    struct ListElement* next;
} ListElement;

typedef struct List {
    ListElement* head;
    ListElement* tail;
    int listSize;
} List;

int getListSize(List* list);
List* makeNewList();
void deleteList(List* list);
ListElement* getListElement(List* list, int position);
void addListElement(List* list, Value value, int position);
void deleteListElement(List* list, int position);

#endif