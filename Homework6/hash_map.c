#include "hash_map.h"
#include "list.h"
#include "values.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASH_POLYNOMIAL_PARAMETER 239
#define MOD 7537

int power(int a, int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return a;
    if (n % 2 == 0)
        return power(a, n / 2) * power(a, n / 2);
    else
        return a * power(a, n - 1);
}

uint32_t hashInt(int x)
{
    return x % MOD;
}

uint32_t hashDouble(double x)
{
    uint32_t h = 0;
    memcpy(&x, &h, sizeof(x));
    return h % MOD;
}

uint32_t hashString(char* string)
{
    uint32_t hash = 0;
    int length = strlen(string);
    for (int i = 0; i < length; ++i)
        hash += (string[i] * power(HASH_POLYNOMIAL_PARAMETER, length - i)) % MOD;
    return hash % MOD;
}

uint32_t hashPair(Pair* pair)
{
    return (hash(pair->first) + hash(pair->second)) % MOD;
}

uint32_t hashList(Value pointer)
{
    List* list = getPointer(pointer);
    uint32_t listHash = 0;
    for (int i = 0; i < getListSize(list); ++i) {
        Value key = getListElement(list, i)->key;
        Value value = getListElement(list, i)->value;
        listHash += ((hash(key) + hash(value)) % MOD) * power(HASH_POLYNOMIAL_PARAMETER, getListSize(list) - i) % MOD;
    }
    return listHash % MOD;
}

uint32_t hash(Value x)
{
    switch (x.type) {
    case INT_TYPE:
        return hashInt(getInt(x));
    case DOUBLE_TYPE:
        return hashDouble(getDouble(x));
    case STRING_TYPE:
        return hashString(getString(x));
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

HashMap* createHashMap(HashFunction hashFunction)
{
    HashMap* map = malloc(sizeof(HashMap));
    map->hashMapSize = MOD;
    map->hashTable = malloc(MOD * sizeof(HashMapElement*));
    for (int i = 0; i < map->hashMapSize; ++i)
        map->hashTable[i] = makeNewHashMapElement();
    map->hashFunction = hashFunction;
    return map;
}

void deleteHashMap(HashMap* map)
{
    for (int i = 0; i < map->hashMapSize; ++i)
        free(map->hashTable[i]);
    free(map);
}

void putToHashMap(HashMap* map, Value key, Value value)
{
    uint32_t hashElement = map->hashFunction(key);
    map->hashTable[hashElement]->hash = hashElement;
    addListElement(map->hashTable[hashElement]->list, key, value, map->hashTable[hashElement]->list->listSize);
}

List* getHashMapElements(HashMap* map, Value key)
{
    List* list = makeNewList();
    uint32_t hashElement = map->hashFunction(key);
    for (ListElement* current = map->hashTable[hashElement]->list->head; current; current = current->next) {
        if (key.type == POINTER_TYPE) {
            if (map->hashFunction(key) == map->hashFunction(current->key))
                addListElement(list, current->key, current->value, getListSize(list));
        } else {
            if (equals(key, current->key))
                addListElement(list, current->key, current->value, getListSize(list));
        }
    }
    return list;
}

bool hasKey(HashMap* map, Value key)
{
    uint32_t hashElement = map->hashFunction(key);
    for (int i = 0; i < getListSize(map->hashTable[hashElement]->list); ++i)
        if (equals(key, getListElement(map->hashTable[hashElement]->list, i)->key))
            return true;
    return false;
}

void removeKey(HashMap* map, Value key)
{
    if (!hasKey(map, key))
        return;
    uint32_t hashElement = map->hashFunction(key);
    for (int i = getListSize(map->hashTable[hashElement]->list) - 1; i >= 0; --i)
        if (equals(key, getListElement(map->hashTable[hashElement]->list, i)->key))
            deleteListElement(map->hashTable[hashElement]->list, i);
}