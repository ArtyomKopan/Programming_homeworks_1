#include "AVL_tree.h"
#include "values.h"
#include <stdio.h>
#include <string.h>

int compareIntegers(Value a, Value b)
{
    if (getInt(a) < getInt(b))
        return -1;
    else if (getInt(a) == getInt(b))
        return 0;
    else
        return 1;
}

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
                store = createTree(wrapInt(size), wrapInt(count), compareIntegers);
            else if (!hasKey(store, wrapInt(size)))
                store = put(store, wrapInt(size), wrapInt(count));
            else
                store = put(store, wrapInt(size), wrapInt(getInt(get(store, wrapInt(size))) + count));
        } else if (strcmp(operation, "GET") == 0) {
            fscanf(shopLogs, "%i", &size);
            Value result = get(store, wrapInt(size));
            fprintf(shopResults, "%i\n", !isNone(result) ? getInt(result) : 0);
        } else {
            fscanf(shopLogs, "%i", &size);
            Value foundSize = getLowerBound(store, wrapInt(size));
            if (isNone(foundSize) || equals(foundSize, wrapInt(0)))
                fprintf(shopResults, "SORRY\n");
            else {
                fprintf(shopResults, "%i\n", getInt(foundSize));
                store = put(store, foundSize, wrapInt(getInt(get(store, foundSize)) - 1));
                if (equals(get(store, foundSize), wrapInt(0)))
                    store = removeKey(store, foundSize);
            }
        }
    }

    while (store) {
        int minimum = getInt(getMinimum(store));
        fprintf(shopBalance, "%i %i\n", minimum, getInt(get(store, wrapInt(minimum))));
        store = removeKey(store, wrapInt(minimum));
    }

    deleteTree(store);
    fclose(shopLogs);
    fclose(shopResults);
    fclose(shopBalance);
    return 0;
}