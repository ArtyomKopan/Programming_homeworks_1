#include "hash_map.h"
#include "list.h"
#include "values.h"
#include <stdint.h>
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

    HashMap* starMap1 = createHashMap(hash);
    HashMap* starMap2 = createHashMap(hashList);
    while (!feof(inputFile)) {
        char operation[11];
        fscanf(inputFile, "%s", operation);
        if (strcmp(operation, "REGISTER") == 0 || strcmp(operation, "register") == 0) {
            char* system = malloc(64 * sizeof(char));
            int n = 0;
            fscanf(inputFile, "%s %i", system, &n);
            List* starList = makeNewList();
            for (int i = 0; i < n; ++i) {
                char* star = malloc(64 * sizeof(char));
                int azimuth = 0;
                fscanf(inputFile, "%s %i", star, &azimuth);
                Pair* starDirection = malloc(sizeof(Pair));
                starDirection->first = wrapString(star);
                starDirection->second = wrapInt(azimuth);
                putToHashMap(starMap1, wrapString(system), wrapPointer(starDirection));
                addListElement(starList, wrapString(star), wrapInt(azimuth), getListSize(starList));
            }
            putToHashMap(starMap2, wrapPointer(starList), wrapString(system));
        } else if (strcmp(operation, "FIND") == 0 || strcmp(operation, "find") == 0) {
            int n = 0;
            fscanf(inputFile, "%i", &n);
            List* starList = makeNewList();
            for (int i = 0; i < n; ++i) {
                char* star = malloc(64 * sizeof(char));
                int azimuth = 0;
                fscanf(inputFile, "%s %i", star, &azimuth);
                addListElement(starList, wrapString(star), wrapInt(azimuth), getListSize(starList));
            }
            List* foundElements = getHashMapElements(starMap2, wrapPointer(starList));
            if (getListSize(foundElements) > 0)
                fprintf(outputFile, "%s\n", getString(foundElements->head->value));
            else
                fprintf(outputFile, "NOT FOUND\n");
        } else if (strcmp(operation, "UNREGISTER") == 0 || strcmp(operation, "unregister") == 0) {
            char* system = malloc(64 * sizeof(char));
            fscanf(inputFile, "%s", system);
            uint32_t systemHash = hash(wrapString(system));
            List* starList = makeNewList();
            for (int i = getListSize(starMap1->hashTable[systemHash]->list) - 1; i >= 0; --i) {
                ListElement* element = getListElement(starMap1->hashTable[systemHash]->list, i);
                if (strcmp(system, getString(element->key))) {
                    Pair* star = (Pair*)getPointer(element->value);
                    addListElement(starList, star->first, star->second, getListSize(starList));
                }
            }
            removeKey(starMap1, wrapString(system));
            removeKey(starMap2, wrapPointer(starList));
        } else if (strcmp(operation, "GET_INFO") == 0 || strcmp(operation, "get_info") == 0) {
            char* system = malloc(64 * sizeof(char));
            fscanf(inputFile, "%s", system);
            List* foundElements = getHashMapElements(starMap1, wrapString(system));
            fprintf(outputFile, "%i ", getListSize(foundElements));
            for (ListElement* current = foundElements->head; current; current = current->next) {
                Pair* starDirection = (Pair*)getPointer(current->value);
                fprintf(outputFile, "%s %i ", getString(starDirection->first), getInt(starDirection->second));
            }
            fprintf(outputFile, "\n");
        }
    }

    deleteHashMap(starMap1);
    deleteHashMap(starMap2);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
