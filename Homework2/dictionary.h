#pragma once
#ifndef HOMEWORK2_DICTIONARY_H
#define HOMEWORK2_DICTIONARY_H

#include <stdbool.h>

typedef struct Dictionary Dictionary;
typedef struct DictElement DictElement;

struct DictElement {
    char* key;
    int value;
    DictElement* nextElement;
};

struct Dictionary {
    DictElement* head;
    DictElement* tail;
    int dictSize;
};

Dictionary* makeNewDictionary();
void deleteDictionary(Dictionary* dict);
void put(Dictionary* dict, const char* key, int value);
int get(Dictionary* dict, const char* key);
bool hasKey(Dictionary* dict, const char* key);

#endif // HOMEWORK2_DICTIONARY_H
