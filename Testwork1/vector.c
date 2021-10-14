#include "vector.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Vector* makeNewVector()
{
    List* coordinates = malloc(sizeof(List));
    coordinates->head = NULL;
    coordinates->tail = NULL;
    coordinates->listSize = 0;
    Vector* newVector = malloc(sizeof(Vector));
    newVector->coordinates = coordinates;
    newVector->dim = coordinates->listSize;
    return newVector;
}

ListElement* makeNewListElement(int data)
{
    ListElement* element = malloc(sizeof(ListElement));
    element->data = data;
    element->prev = NULL;
    element->next = NULL;
    return element;
}

void addElement(Vector* v, int data)
{
    ListElement* newElement = makeNewListElement(data);
    if (v->coordinates->head == NULL) {
        v->coordinates->head = newElement;
        v->coordinates->tail = newElement;
    } else {
        v->coordinates->tail->next = newElement;
        newElement->prev = v->coordinates->tail;
        v->coordinates->tail = newElement;
    }
    v->coordinates->listSize++;
    v->dim++;
}

Vector* sum(Vector* v1, Vector* v2)
{
    Vector* result = makeNewVector();
    ListElement* current1 = v1->coordinates->head;
    ListElement* current2 = v2->coordinates->head;
    for (; current1 && current2; current1 = current1->next, current2 = current2->next)
        addElement(result, current1->data + current2->data);
    return result;
}

Vector* difference(Vector* v1, Vector* v2)
{
    Vector* result = makeNewVector();
    ListElement* current1 = v1->coordinates->head;
    ListElement* current2 = v2->coordinates->head;
    for (; current1 && current2; current1 = current1->next, current2 = current2->next)
        addElement(result, current1->data - current2->data);
    return result;
}

int product(Vector* v1, Vector* v2)
{
    int result = 0;
    ListElement* current1 = v1->coordinates->head;
    ListElement* current2 = v2->coordinates->head;
    for (; current1 && current2; current1 = current1->next, current2 = current2->next)
        result += (current1->data * current2->data);
    return result;
}

double length(Vector* v)
{
    double result = 0;
    ListElement* current1 = v->coordinates->head;
    for (; current1; current1 = current1->next)
        result += (current1->data * current1->data);
    return result;
}

void deleteVector(Vector* v)
{
    ListElement* currentElement = v->coordinates->head;
    ListElement* nextElement = NULL;
    while (currentElement) {
        nextElement = currentElement->next;
        free(currentElement);
        currentElement = nextElement;
    }
    free(v->coordinates);
    free(v);
}

void printVector(Vector* v)
{
    printf("(");
    ListElement* current = v->coordinates->head;
    for (; current; current = current->next) {
        if (current == v->coordinates->tail)
            printf("%i", current->data);
        else
            printf("%i, ", current->data);
    }
    printf(")\n");
}