#include "../library/list/list.h"
#include "../library/values/values.h"
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

List* bfs(int** graph, int vertexCount, int start)
{
    int dist[vertexCount];
    for (int i = 0; i < vertexCount; ++i)
        dist[i] = INF;
    List* queue = makeNewList();
    addListElement(queue, wrapInt(start), 0);
    dist[start] = 0;
    while (getListSize(queue) != 0) {
        int u = getInt(getListElement(queue, getListSize(queue) - 1)->value);
        deleteListElement(queue, getListSize(queue) - 1);
        for (int i = 0; i < vertexCount; ++i) {
            if (graph[u][i] == 1) {
                if (dist[i] == INF) {
                    dist[i] = dist[u] + 1;
                    addListElement(queue, wrapInt(i), 0);
                }
            }
        }
    }
    deleteList(queue);
    List* result = makeNewList();
    for (int i = 0; i < vertexCount; ++i)
        if (dist[i] != INF) {
            addListElement(result, wrapInt(i), 0);
        }
    return result;
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
        fclose(outputFile);
        return 0;
    } else if (!outputFile) {
        printf("Output file open error!");
        fclose(inputFile);
        return 0;
    }

    int vertexCount = 0;
    int edgesCount = 0;
    fscanf(inputFile, "%i %i", &vertexCount, &edgesCount);

    int** incidenceMatrix;
    incidenceMatrix = (int**)calloc(vertexCount, sizeof(*incidenceMatrix));
    for (int i = 0; i < vertexCount; ++i)
        incidenceMatrix[i] = (int*)calloc(edgesCount, sizeof(*incidenceMatrix[i]));
    for (int i = 0; i < vertexCount; ++i)
        for (int j = 0; j < edgesCount; ++j)
            fscanf(inputFile, "%i", &incidenceMatrix[i][j]);
    int** adjacencyMatrix;
    adjacencyMatrix = (int**)calloc(vertexCount, sizeof(*adjacencyMatrix));
    for (int i = 0; i < vertexCount; ++i)
        adjacencyMatrix[i] = (int*)calloc(vertexCount, sizeof(*adjacencyMatrix[i]));

    for (int j = 0; j < edgesCount; ++j) {
        int u = -1;
        int v = -1;
        for (int i = 0; i < vertexCount; ++i) {
            if (incidenceMatrix[i][j] == 1)
                u = i;
            else if (incidenceMatrix[i][j] == -1)
                v = i;
            if (u != -1 && v != -1)
                break;
        }
        adjacencyMatrix[u][v] = 1;
    }

    List** array = malloc(vertexCount * sizeof(List*));
    for (int i = 0; i < vertexCount; ++i) {
        array[i] = bfs(adjacencyMatrix, vertexCount, i);
    }
    for (int k = 0; k < vertexCount; ++k) {
        bool achievable = true;
        for (int j = 0; j < vertexCount; ++j) {
            bool flag = false;
            for (ListElement* current = array[j]->head; current; current = current->next)
                if (getInt(current->value) == k) {
                    flag = true;
                    break;
                }
            if (!flag) {
                achievable = false;
                break;
            }
        }
        if (achievable)
            fprintf(outputFile, "%i ", k);
    }

    fclose(inputFile);
    fclose(outputFile);
    for (int i = 0; i < vertexCount; ++i) {
        deleteList(array[i]);
    }
    free(array);
    for (int i = 0; i < vertexCount; ++i) {
        free(adjacencyMatrix[i]);
        free(incidenceMatrix[i]);
    }
    free(adjacencyMatrix);
    free(incidenceMatrix);
    return 0;
}
