#include "AVL_tree.h"
#include "dictionary.h"
#include "hash_map.h"
#include "list.h"
#include "values.h"
#include <stdio.h>
#include <time.h>

int compareIntValue(Value a, Value b)
{
    return getInt(a) == getInt(b);
}

int main(int argc, char* argv[])
{
    // структуры данных будут хранить пары (key=Int, value=String)
    FILE* inputFile = fopen(argv[1], "r");
    Dictionary* dictionary = makeNewDictionary();
    Tree* tree = createTree(wrapInt(0), wrapString("b"));

    HashMap* map = createHashMap(hash, compareIntValue);
    int number = 0;
    while (!feof(inputFile)) {
        number++;
        char word[256];
        fscanf(inputFile, "%s", word);
        putToHashMap(map, wrapInt(number), wrapString(word));
        // putToDictionary(dictionary, word, number);
        // putToTree(tree, wrapInt(number), wrapString(word));
    }
    deleteHashMap(map);

    deleteTree(tree);
    deleteDictionary(dictionary);
    fclose(inputFile);

    printf("%lf", (double)clock() / CLOCKS_PER_SEC); // время в секундах
    printf("\n%i", number);
    return 0;
}