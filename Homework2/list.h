#pragma once
#ifndef HOMEWORK2_LIST_H
#define HOMEWORK2_LIST_H

#include <bits/types/FILE.h>
#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;

struct ListElement {
    char data;
    ListElement* prev;
    ListElement* next;
};

struct List {
    ListElement* head;
    ListElement* tail;
    int listSize;
};

typedef struct List List;
typedef struct ListElement ListElement;

List* makeNewList();
void deleteList(List* lst);

void addElement(List* lst, char data, int position);
void deleteElementByIndex(List* lst, int position);

int getListSize(List* l);
void printListAsString(List* l, FILE* outputFile);
#endif // HOMEWORK2_LIST_H
