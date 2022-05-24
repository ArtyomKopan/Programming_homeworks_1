#pragma once
#ifndef HOMEWORK6_HASH_MAP_H
#define HOMEWORK6_HASH_MAP_H

#include "list.h"
#include "values.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t (*HashFunction)(Value, int);
typedef int (*Comparator)(Value, Value);

typedef struct Pair {
    Value first;
    Value second;
} Pair;

typedef struct HashMapElement {
    uint32_t hash;
    List* list;
} HashMapElement;

typedef struct HashMap {
    HashMapElement** hashTable;
    HashFunction hashFunction;
    Comparator comparator;
    int hashMapSize;
    int countFilledBuckets;
} HashMap;

HashMap* createHashMap(HashFunction hashFunction, Comparator comparator);

void deleteHashMap(HashMap* map);

Value getHashMapElement(HashMap* map, Value key);

List* getHashMapElements(HashMap* map, Value key);

void putToHashMap(HashMap* map, Value key, Value value);

bool hasKey(HashMap* map, Value key);

void removeKey(HashMap* map, Value key);

int getHashMapSize(HashMap* map);

uint32_t hash(Value x, int mod);
uint32_t hashList(Value pointer, int mod);

#endif
