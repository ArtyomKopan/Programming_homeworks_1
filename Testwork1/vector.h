#pragma once
#ifndef TESTWORK1_VECTOR_H
#define TESTWORK1_VECTOR_H

typedef struct Vector Vector;
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

struct Vector {
    List* coordinates;
    int dim;
};

Vector* makeNewVector();
void deleteVector(Vector* v);

void addElement(Vector* v, int data);
Vector* sum(Vector* v1, Vector* v2);
Vector* difference(Vector* v1, Vector* v2);
int product(Vector* v1, Vector* v2);
double length(Vector* v);
void printVector(Vector* v);
#endif // TESTWORK1_VECTOR_H
