#pragma once
#ifndef HOMEWORK6_HASH_MAP_H
#define HOMEWORK6_HASH_MAP_H

#include "list.h"
#include "values.h"
#include <stdbool.h>
#include <stdint.h>

typedef uint32_t (*HashFunction)(Value);

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
    int hashMapSize;
} HashMap;

HashMap* createHashMap(HashFunction hashFunction);

void deleteHashMap(HashMap* map);

List* getHashMapElements(HashMap* map, Value key);

void putToHashMap(HashMap* map, Value key, Value value);

bool hasKey(HashMap* map, Value key);

void removeKey(HashMap* map, Value key);

int getHashMapSize(HashMap* map);

uint32_t hash(Value x);
uint32_t hashList(Value pointer);

#endif
