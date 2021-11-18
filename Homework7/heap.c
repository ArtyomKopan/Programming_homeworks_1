#include "heap.h"
#include <stdlib.h>

int parent(int i)
{
    return (i - 1) / 2;
}

int leftChild(int i)
{
    return 2 * i + 1;
}

int rightChild(int i)
{
    return 2 * i + 2;
}

void swap(Pair* array, int i, int j)
{
    Pair temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void siftUp(Heap* heap, int index)
{
    while (index > 0 && heap->heap[parent(index)].priority > heap->heap[index].priority) {
        swap(heap->heap, index, parent(index));
        index = parent(index);
    }
}

void siftDown(Heap* heap, int index)
{
    int left = leftChild(index);
    int right = rightChild(index);
    int largest = index;
    if (left < heap->size && heap->heap[left].priority < heap->heap[largest].priority)
        largest = left;
    if (right < heap->size && heap->heap[right].priority < heap->heap[largest].priority)
        largest = right;
    if (largest != index) {
        swap(heap->heap, index, largest);
        siftDown(heap, largest);
    }
}

void insert(Heap* heap, int vertex, int priority)
{
    if (heap->size >= START_HEAP_SIZE - 1)
        heap->heap = realloc(heap->heap, heap->size * START_HEAP_SIZE * sizeof(int));
    heap->heap[heap->size].vertex = vertex;
    heap->heap[heap->size].priority = priority;
    heap->size++;
    siftUp(heap, heap->size - 1);
}

int extractMin(Heap* heap)
{
    int minimum = heap->heap[0].vertex;
    heap->heap[0] = heap->heap[heap->size - 1];
    heap->size--;
    siftDown(heap, 0);
    return minimum;
}

Heap* createNewHeap()
{
    Heap* heap = malloc(sizeof(Heap));
    heap->heap = malloc(START_HEAP_SIZE * sizeof(int));
    heap->size = 0;
    return heap;
}

void deleteHeap(Heap* heap)
{
    free(heap);
}

bool isEmpty(Heap* heap)
{
    return heap->size == 0;
}