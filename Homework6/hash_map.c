#include "hash_map.h"
#include "list.h"
#include "values.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASH_POLYNOMIAL_PARAMETER 239
#define HASH_MAP_START_SIZE 256
#define HASH_MAP_LOAD_BORDER 0.8

int power(int a, int n, int mod)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return a;
    if (n % 2 == 0) {
        int temp = power(a, n / 2, mod) % mod;
        return (temp * temp) % mod;
    } else
        return (a * (power(a, n - 1, mod) % mod)) % mod;
}

uint32_t hashInt(int x, int mod)
{
    return x % mod;
}

uint32_t hashDouble(double x, int mod)
{
    uint_fast64_t temp = 0;
    memcpy(&temp, &x, sizeof(double));
    temp *= HASH_POLYNOMIAL_PARAMETER;
    int32_t older = (temp >> 32) % mod;
    int32_t younger = ((temp << 32) >> 32) % mod;
    return (older ^ younger) % mod;
}

uint32_t hashString(char* string, int mod)
{
    uint32_t hash = 0;
    int length = strlen(string);
    for (int i = 0; i < length; ++i)
        hash = (hash * HASH_POLYNOMIAL_PARAMETER + string[i]) % mod;
    return hash % mod;
}

uint32_t hashList(Value pointer, int mod)
{
    List* list = getPointer(pointer);
    uint32_t listHash = 0;
    int multiplayer = 1;
    for (int i = 0; i < getListSize(list); ++i) {
        Value key = getListElement(list, i)->key;
        Value value = getListElement(list, i)->value;
        listHash += (((hash(key, mod) + HASH_POLYNOMIAL_PARAMETER * hash(value, mod)) % mod) * multiplayer) % mod;
        multiplayer *= HASH_POLYNOMIAL_PARAMETER;
        multiplayer %= mod;
    }
    return listHash % mod;
}

uint32_t hash(Value x, int mod)
{
    switch (x.type) {
    case INT_TYPE:
        return hashInt(getInt(x), mod);
    case DOUBLE_TYPE:
        return hashDouble(getDouble(x), mod);
    case STRING_TYPE:
        return hashString(getString(x), mod);
    }
}

int getHashMapSize(HashMap* map)
{
    return map->hashMapSize;
}

HashMapElement* makeNewHashMapElement()
{
    HashMapElement* element = malloc(sizeof(HashMapElement));
    element->hash = 0;
    element->list = makeNewList();
    return element;
}

HashMap* createHashMap(HashFunction hashFunction, Comparator comparator)
{
    HashMap* map = malloc(sizeof(HashMap));
    map->hashMapSize = HASH_MAP_START_SIZE;
    map->hashTable = malloc(HASH_MAP_START_SIZE * sizeof(HashMapElement*));
    for (int i = 0; i < map->hashMapSize; ++i)
        map->hashTable[i] = makeNewHashMapElement();
    map->hashFunction = hashFunction;
    map->comparator = comparator;
    return map;
}

double getLoadFactor(HashMap* map)
{
    return (double)map->countFilledBuckets / map->hashMapSize;
}

void resizeHashMap(HashMap* map)
{
    map->hashTable = realloc(map->hashTable, 2 * map->hashMapSize * sizeof(HashMapElement*));
    for (int i = map->hashMapSize; i < 2 * map->hashMapSize; ++i)
        map->hashTable[i] = makeNewHashMapElement();
    map->hashMapSize *= 2;
    ListElement* next = NULL;
    for (int i = 0; i < map->hashMapSize / 2; ++i) {
        for (ListElement* current = map->hashTable[i]->list->head; current; current = next) {
            uint32_t newHash = map->hashFunction(current->key, map->hashMapSize);
            if (newHash != i) {
                // добавляем этот элемент в новую ячейку
                addListElement(map->hashTable[newHash]->list, current->key, current->value, map->hashTable[newHash]->list->listSize);
                if (getListSize(map->hashTable[newHash]->list) == 1)
                    map->countFilledBuckets++;
                // удаляем элемент из текущего списка
                if (current->next)
                    current->next->previous = current->previous;
                else
                    map->hashTable[i]->list->tail = current->previous;
                if (current->previous)
                    current->previous->next = current->next;
                else
                    map->hashTable[i]->list->head = current->next;
                next = current->next;
                free(current);
                map->hashTable[i]->list->listSize--;
                if (map->hashTable[i]->list->listSize == 0)
                    map->countFilledBuckets--;
            } else
                next = current->next;
        }
    }
}

void deleteHashMap(HashMap* map)
{
    for (int i = 0; i < map->hashMapSize; ++i) {
        ListElement* next = NULL;
        for (ListElement* current = map->hashTable[i]->list->head; current; current = next) {
            next = current->next;
            free(current);
        }
        free(map->hashTable[i]->list);
        free(map->hashTable[i]);
    }
    free(map);
}

void putToHashMap(HashMap* map, Value key, Value value)
{
    if (getLoadFactor(map) >= HASH_MAP_LOAD_BORDER)
        resizeHashMap(map);
    uint32_t hashElement = map->hashFunction(key, map->hashMapSize);
    map->hashTable[hashElement]->hash = hashElement;
    addListElement(map->hashTable[hashElement]->list, key, value, map->hashTable[hashElement]->list->listSize);
    if (getListSize(map->hashTable[hashElement]->list) == 1)
        map->countFilledBuckets++;
}

Value getHashMapElement(HashMap* map, Value key)
{
    uint32_t hash = map->hashFunction(key, map->hashMapSize);
    for (ListElement* current = map->hashTable[hash]->list->head; current; current = current->next)
        if (map->hashFunction(key, map->hashMapSize) == map->hashFunction(current->key, map->hashMapSize))
            return current->value;
    return wrapNone();
}

List* getHashMapElements(HashMap* map, Value key)
{
    List* list = makeNewList();
    uint32_t hashElement = map->hashFunction(key, map->hashMapSize);
    for (ListElement* current = map->hashTable[hashElement]->list->head; current; current = current->next) {
        if (key.type == POINTER_TYPE) {
            if (map->hashFunction(key, map->hashMapSize) == map->hashFunction(current->key, map->hashMapSize))
                addListElement(list, current->key, current->value, getListSize(list));
        } else {
            if (map->comparator(key, current->key) == 0)
                addListElement(list, current->key, current->value, getListSize(list));
        }
    }
    return list;
}

bool hasKey(HashMap* map, Value key)
{
    uint32_t hashElement = map->hashFunction(key, map->hashMapSize);
    for (int i = 0; i < getListSize(map->hashTable[hashElement]->list); ++i)
        if (map->comparator(key, getListElement(map->hashTable[hashElement]->list, i)->key) == 0)
            return true;
    return false;
}

void removeKey(HashMap* map, Value key)
{
    if (!hasKey(map, key))
        return;
    uint32_t hashElement = map->hashFunction(key, map->hashMapSize);
    for (int i = getListSize(map->hashTable[hashElement]->list) - 1; i >= 0; --i)
        if (map->comparator(key, getListElement(map->hashTable[hashElement]->list, i)->key) == 0) {
            deleteListElement(map->hashTable[hashElement]->list, i);
            return;
        }
}