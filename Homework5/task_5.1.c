#include "AVL_tree.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE* shopLogs = fopen(argv[1], "r");
    FILE* shopResults = fopen(argv[2], "w");
    FILE* shopBalance = fopen(argv[3], "w");

    Tree* store = NULL;
    int operationsCount = 0;
    fscanf(shopLogs, "%i", &operationsCount);
    for (int k = 0; k < operationsCount; ++k) {
        char operation[7];
        int size = 0;
        fscanf(shopLogs, "%s", operation);
        if (strcmp(operation, "ADD") == 0) {
            int count = 0;
            fscanf(shopLogs, "%i", &size);
            fscanf(shopLogs, "%i", &count);
            if (!store)
                store = createTree(size, count);
            else
                store = put(store, size, count);
        } else if (strcmp(operation, "GET") == 0) {
            fscanf(shopLogs, "%i", &size);
            fprintf(shopResults, "%i\n", get(store, size));
        } else {
            fscanf(shopLogs, "%i", &size);
            int foundSize = getLowerBound(store, size);
            if (foundSize == 0)
                fprintf(shopResults, "SORRY\n");
            else {
                fprintf(shopResults, "%i\n", foundSize);
                store = put(store, foundSize, get(store, foundSize) - 1);
                if (get(store, foundSize) == 0)
                    store = removeKey(store, foundSize);
            }
        }
    }

    while (store) {
        int minimum = getMinimum(store);
        fprintf(shopBalance, "%i %i\n", minimum, get(store, minimum));
        store = removeKey(store, minimum);
    }

    deleteTree(store);
    fclose(shopLogs);
    fclose(shopResults);
    fclose(shopBalance);
    return 0;
}