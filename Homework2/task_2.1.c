#include "dictionary.h"
#include <stdio.h>

void readInputFile(FILE* inputFile, Dictionary* dict)
{
    char word[128];
    while ((fscanf(inputFile, "%s", word)) != EOF)
        put(dict, word, get(dict, word) + 1);
}

void writeOutputFile(FILE* outputFile, Dictionary* dict)
{
    for (DictionaryElement* current = dict->head; current; current = current->nextElement)
        fprintf(outputFile, "%s,%i\n", current->key, current->value);
    printf("Data processing was successfully!");
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    FILE* outputFile = fopen(argv[2], "w");

    if (!inputFile && !outputFile) {
        printf("Input and output files open error!");
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

    Dictionary* dict = makeNewDictionary();

    readInputFile(inputFile, dict);

    writeOutputFile(outputFile, dict);

    deleteDictionary(dict);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}