#include "dictionary.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Dictionary* makeNewDictionary()
{
    Dictionary* dict = malloc(sizeof(Dictionary));
    dict->head = NULL;
    dict->tail = NULL;
    dict->dictSize = 0;
    return dict;
}

DictionaryElement* makeNewDictionaryElement(const char* key, int value)
{
    DictionaryElement* newElement = malloc(sizeof(DictionaryElement));
    newElement->key = malloc((strlen(key) + 1) * sizeof(char));
    stpcpy(newElement->key, key);
    newElement->value = value;
    newElement->nextElement = NULL;
    return newElement;
}

void put(Dictionary* dict, const char* key, int value)
{
    if (!hasKey(dict, key)) {
        DictionaryElement* newElement = makeNewDictionaryElement(key, value);
        if (!dict->head) {
            dict->head = newElement;
            dict->tail = newElement;
        } else {
            dict->tail->nextElement = newElement;
            dict->tail = newElement;
        }
        dict->dictSize++;
    } else
        for (DictionaryElement* current = dict->head; current; current = current->nextElement)
            if (strcmp(current->key, key) == 0) {
                current->value = value;
                break;
            }
}

int get(Dictionary* dict, const char* key)
{
    if (!dict->head)
        return 0; // элемент не найден
    for (DictionaryElement* current = dict->head; current; current = current->nextElement)
        if (strcmp(current->key, key) == 0)
            return current->value; // элемент найден
    return 0; // элемент не найден
}

bool hasKey(Dictionary* dict, const char* key)
{
    if (!dict->head)
        return false;
    for (DictionaryElement* current = dict->head; current; current = current->nextElement)
        if (strcmp(current->key, key) == 0)
            return true;
    return false;
}

void deleteDictionary(Dictionary* dict)
{
    DictionaryElement* currentElement = dict->head;
    DictionaryElement* nextElement = NULL;
    while (currentElement) {
        nextElement = currentElement->nextElement;
        free(currentElement);
        currentElement = nextElement;
    }
    free(currentElement);
    free(nextElement);
    free(dict);
}