#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

typedef struct Pair {
    int first;
    int second;
} Pair;

bool equal(Pair a, Pair b)
{
    return (a.first == b.first) && (a.second == b.second);
}

int main()
{
    int m = 0;
    int n = 0;
    printf("Enter count rows and columns of array: ");
    scanf("%i %i", &m, &n);
    int** array;
    array = (int**)calloc(m, sizeof(*array));
    for (int i = 0; i < m; ++i)
        array[i] = (int*)calloc(n, sizeof(*array[i]));
    printf("Enter array: ");
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%i", &array[i][j]);

    Pair* minRows = malloc(m * sizeof(Pair));
    Pair* maxColumns = malloc(n * sizeof(Pair));
    for (int i = 0; i < m; ++i) {
        int min = INF;
        int minIndex = 0;
        for (int j = 0; j < n; ++j) {
            if (array[i][j] < min) {
                min = array[i][j];
                minIndex = j;
            }
        }
        Pair pair = { i, minIndex };
        minRows[i] = pair;
    }
    for (int j = 0; j < n; ++j) {
        int max = -INF;
        int maxIndex = 0;
        for (int i = 0; i < m; ++i) {
            if (array[i][j] > max) {
                max = array[i][j];
                maxIndex = i;
            }
        }
        Pair pair = { maxIndex, j };
        maxColumns[j] = pair;
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (equal(minRows[i], maxColumns[j]))
                printf("%i %i\n", minRows[i].first, minRows[i].second);

    for (int i = 0; i < m; ++i)
        free(array[i]);
    free(array);
    free(minRows);
    free(maxColumns);
    return 0;
}