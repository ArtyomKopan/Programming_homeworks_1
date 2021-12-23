#pragma once
#ifndef HOMEWORK2_LIST_H
#define HOMEWORK2_LIST_H

#include <bits/types/FILE.h>
#include <stdbool.h>

typedef struct ListElement {
    char data;
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
ListElement* get(List* list, int position);
void addElement(List* list, char data, int position);
void addElements(List* list, char* data, int dataSize, int position);
void deleteElement(List* list, int position);
void deleteRange(List* list, int start, int end);
void printList(List* list, FILE* outputFile);

#endif