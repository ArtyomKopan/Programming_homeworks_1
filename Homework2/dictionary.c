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

DictionaryElement* find(Dictionary* dict, const char* key)
{
    for (DictionaryElement* current = dict->head; current; current = current->nextElement)
        if (strcmp(current->key, key) == 0)
            return current;
    return NULL;
}

void put(Dictionary* dict, const char* key, int value)
{
    DictionaryElement* currentElement = find(dict, key);
    if (!currentElement) {
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
        currentElement->value = value;
}

int get(Dictionary* dict, const char* key)
{
    if (!dict->head)
        return 0; // элемент не найден
    DictionaryElement* foundElement = find(dict, key);
    if (foundElement)
        return foundElement->value; // элемент найден
    else
        return 0; // элемент не найден
}

bool hasKey(Dictionary* dict, const char* key)
{
    return find(dict, key);
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