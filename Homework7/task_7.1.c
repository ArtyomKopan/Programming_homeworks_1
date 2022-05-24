#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

void Dijkstra(int** graph, int nVertex, int start, int* dist, int* prev)
{
    Heap* heap = createNewHeap();
    dist[start] = 0;
    insert(heap, start, dist[start]);
    while (!isEmpty(heap)) {
        int u = extractMin(heap);
        for (int v = 0; v < nVertex; ++v) {
            if (graph[u][v] != 0) {
                if (dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    prev[v] = u;
                    insert(heap, v, dist[v]);
                }
            }
        }
    }
    deleteHeap(heap);
}

void printPath(int* prev, int vertex, int countVertex, FILE* outputFile)
{
    if (prev[vertex] == -1) {
        fprintf(outputFile, "%i\n", countVertex + 1);
        fprintf(outputFile, "%i ", vertex);
        return;
    }
    printPath(prev, prev[vertex], countVertex + 1, outputFile);
    fprintf(outputFile, "%i ", vertex);
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");
    if (!inputFile && !outputFile) {
        printf("Input and output file open error!");
        return 0;
    } else if (!inputFile) {
        printf("Input file open error!");
        return 0;
    } else if (!outputFile) {
        printf("Output file open error!");
        return 0;
    }

    int nVertex = 0;
    int nEdges = 0;
    fscanf(inputFile, "%i %i", &nVertex, &nEdges);
    int** graph = malloc(nVertex * sizeof(int*)); // матрица смежности
    for (int i = 0; i < nVertex; ++i) {
        graph[i] = malloc(nVertex * sizeof(int));
        for (int j = 0; j < nVertex; ++j)
            graph[i][j] = 0;
    }
    for (int i = 0; i < nEdges; ++i) {
        int from = 0;
        int to = 0;
        int weight = 0;
        fscanf(inputFile, "%i %i %i", &from, &to, &weight);
        graph[from][to] = weight;
    }
    int start = 0;
    int finish = 0;
    fscanf(inputFile, "%i %i", &start, &finish);

    int* dist = malloc(nVertex * sizeof(int));
    int* prev = malloc(nVertex * sizeof(int));
    for (int i = 0; i < nVertex; ++i) {
        dist[i] = INF;
        prev[i] = -1;
    }

    Dijkstra(graph, nVertex, start, dist, prev);
    fprintf(outputFile, "%i ", dist[finish]);
    printPath(prev, finish, 0, outputFile);

    for (int i = 0; i < nVertex; ++i)
        free(graph[i]);
    free(graph);
    free(dist);
    free(prev);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
