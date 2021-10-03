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

DictElement* makeNewDictElement(const char* key, int value)
{
    DictElement* newElement = malloc(sizeof(DictElement));
    newElement->key = malloc((strlen(key) + 1) * sizeof(char));
    stpcpy(newElement->key, key);
    newElement->value = value;
    newElement->nextElement = NULL;
    return newElement;
}

void put(Dictionary* dict, const char* key, int value)
{
    DictElement* newElement = makeNewDictElement(key, value);
    if (dict->head == NULL) {
        dict->head = newElement;
        dict->tail = newElement;
    } else {
        DictElement* penultimateElement = dict->tail;
        dict->tail = newElement;
        penultimateElement->nextElement = dict->tail;
    }
    dict->dictSize++;
}

int get(Dictionary* dict, const char* key)
{
    if (dict->head == NULL)
        return -1; // элемент не найден
    DictElement* currentElement = dict->head;
    while (currentElement != NULL) {
        if (strcmp(currentElement->key, key) == 0)
            return currentElement->value; // элемент найден
        currentElement = currentElement->nextElement;
    }
    return -1; // элемент не найден
}

bool hasKey(Dictionary* dict, const char* key)
{
    if (dict->head == NULL)
        return false;
    DictElement* currentElement = dict->head;
    while (currentElement != NULL) {
        if (strcmp(currentElement->key, key) == 0)
            return true;
        currentElement = currentElement->nextElement;
    }
    return false;
}

void deleteDictionary(Dictionary* dict)
{
    DictElement* currentElement = dict->head;
    DictElement* nextElement = NULL;
    while (currentElement) {
        nextElement = currentElement->nextElement;
        free(currentElement);
        currentElement = nextElement;
    }
    free(dict);
}