#include "AVL_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int signum(int x)
{
    if (x < 0)
        return -1;
    else if (x == 0)
        return 0;
    else
        return 1;
}

int stringValueCompare(Value a, Value b)
{
    return signum(strcmp(getString(a), getString(b)));
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

    Tree* tree = NULL;
    while (!feof(inputFile)) {
        char* string = malloc(256 * sizeof(char));
        fscanf(inputFile, "%s", string);
        tree = tree ? put(tree, wrapString(string), wrapInt(0)) : createTree(wrapString(string), wrapInt(0), stringValueCompare);
    }

    while (!isEmpty(tree)) {
        char* minimum = getString(getMinimum(tree));
        tree = removeKey(tree, wrapString(minimum));
        fprintf(outputFile, "%s ", minimum);
    }

    fclose(inputFile);
    fclose(outputFile);
    deleteTree(tree);
    return 0;
}