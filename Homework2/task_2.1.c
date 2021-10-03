#include "dictionary.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void readInputFile(FILE* inputFile, Dictionary* dict)
{
    char word[128];
    while ((fscanf(inputFile, "%s", word)) != EOF) {
        if (!hasKey(dict, word))
            put(dict, word, 1);
        else {
            DictElement* currentElement = dict->head;
            while (currentElement != NULL) {
                if (strcmp(currentElement->key, word) == 0) {
                    currentElement->value++;
                    break;
                }
                currentElement = currentElement->nextElement;
            }
        }
    }
}

void writeOutputFile(FILE* outputFile, Dictionary* dict)
{
    DictElement* currentElement = dict->head;
    while (currentElement != NULL) {
        fprintf(outputFile, "%s,%i\n", currentElement->key, currentElement->value);
        currentElement = currentElement->nextElement;
    }
    printf("Data processing was successfully!");
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if (inputFile == NULL || outputFile == NULL) {
        printf("File open error!");
        return 0;
    }

    Dictionary* dict = makeNewDictionary();

    readInputFile(inputFile, dict);

    writeOutputFile(outputFile, dict);

    deleteDictionary(dict);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}