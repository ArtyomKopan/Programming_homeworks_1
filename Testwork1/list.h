#pragma once
#ifndef HOMEWORK2_LIST_H
#define HOMEWORK2_LIST_H

#include <bits/types/FILE.h>
#include <stdbool.h>

typedef struct List List;
typedef struct ListElement ListElement;

struct ListElement {
    int data;
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

void addElement(List* lst, int data, int position);

int getListSize(List* l);
void printList(List* l, FILE* outputFile);
#endif // HOMEWORK2_LIST_H
