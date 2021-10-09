#pragma once
#ifndef HOMEWORK2_DICTIONARY_H
#define HOMEWORK2_DICTIONARY_H

#include <stdbool.h>

typedef struct Dictionary Dictionary;
typedef struct DictionaryElement DictionaryElement;

struct DictionaryElement {
    char* key;
    int value;
    DictionaryElement* nextElement;
};

struct Dictionary {
    DictionaryElement* head;
    DictionaryElement* tail;
    int dictSize;
};

Dictionary* makeNewDictionary();
void deleteDictionary(Dictionary* dict);
void put(Dictionary* dict, const char* key, int value);
int get(Dictionary* dict, const char* key);
bool hasKey(Dictionary* dict, const char* key);

#endif // HOMEWORK2_DICTIONARY_H
