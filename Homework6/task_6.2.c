#include "hash_map.h"
#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    HashMap* map = createHashMap(hash);
    while (!feof(inputFile)) {
        char operation[4];
        fscanf(inputFile, "%s", operation);
        if (strcmp(operation, "PUT") == 0 || strcmp(operation, "put") == 0) {
            char s[32];
            char t[32];
            fscanf(inputFile, "%s %s", s, t);
            for (int i = 0; i < 32; ++i) {
                if (s[i] == ',') {
                    s[i] = '.';
                    break;
                }
            }
            for (int i = 0; i < 32; ++i) {
                if (t[i] == ',') {
                    t[i] = '.';
                    break;
                }
            }
            double x = strtod(s, NULL);
            double y = strtod(t, NULL);
            int index = 0;
            fscanf(inputFile, "%i", &index);
            putToHashMap(map, wrapDouble(x / y), wrapInt(index));
        } else if (strcmp(operation, "GET") == 0 || strcmp(operation, "get") == 0) {
            char s[32];
            char t[32];
            fscanf(inputFile, "%s %s", s, t);
            for (int i = 0; i < 32; ++i) {
                if (s[i] == ',') {
                    s[i] = '.';
                    break;
                }
            }
            for (int i = 0; i < 32; ++i) {
                if (t[i] == ',') {
                    t[i] = '.';
                    break;
                }
            }
            double x = strtod(s, NULL);
            double y = strtod(t, NULL);
            int index = getInt(getHashMapElements(map, wrapDouble(x / y))->head->value);
            fprintf(outputFile, "%i\n", index);
        }
    }

    deleteHashMap(map);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}