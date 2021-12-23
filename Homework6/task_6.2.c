#include "hash_map.h"
#include "values.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparePair(Pair a, Pair b)
{ // Pair <double, double>
    if (getDouble(a.first) == getDouble(b.first)) {
        if (getDouble(a.second) == getDouble(b.second))
            return 0;
        else if (getDouble(a.second) < getDouble(b.second))
            return -1;
        else
            return 1;
    } else if (getDouble(a.first) < getDouble(b.first))
        return -1;
    else
        return 1;
}

int comparePairValue(Value a, Value b)
{
    return comparePair(*(Pair*)getPointer(a), *(Pair*)getPointer(b));
}

uint32_t hashPair(Value x, int mod)
{ // Pair <double, double>
    Pair pair = *(Pair*)getPointer(x);
    return (hash(pair.first, mod) + 239 * hash(pair.second, mod)) % mod;
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

    HashMap* map = createHashMap(hashPair, comparePairValue);
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
            Pair pair = { wrapDouble(x), wrapDouble(y) };
            putToHashMap(map, wrapPointer(&pair), wrapInt(index));
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
            Pair pair = { wrapDouble(x), wrapDouble(y) };
            ListElement* element = getHashMapElements(map, wrapPointer(&pair))->head;
            if (element)
                fprintf(outputFile, "%i\n", getInt(element->value));
            else
                fprintf(outputFile, "None\n");
        }
    }

    deleteHashMap(map);
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}