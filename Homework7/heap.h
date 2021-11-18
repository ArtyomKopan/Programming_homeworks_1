#ifndef HOMEWORK7_HEAP_H
#define HOMEWORK7_HEAP_H

#define START_HEAP_SIZE 256

#include <stdbool.h>

typedef struct Pair {
    int vertex;
    int priority;
} Pair;

typedef struct Heap {
    Pair* heap;
    int size;
} Heap;

void insert(Heap* heap, int vertex, int priority);
int extractMin(Heap* heap);
Heap* createNewHeap();
void deleteHeap(Heap* heap);
bool isEmpty(Heap* heap);

#endif
