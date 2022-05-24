#include "AVL_tree.h"
#include "list.h"
#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Address {
    char* street;
    int house;
    int block;
} Address;

int compareAddresses(Address first, Address second)
{
    printf("%s %s\n", first.street, second.street);
    if (strcmp(first.street, second.street) == 0 && first.house == second.house && first.block == second.block)
        return 0;
    if (strcmp(first.street, second.street) == 0) {
        if (first.house == second.house)
            return first.block < second.block ? -1 : 1;
        return first.house < second.house ? -1 : 1;
    }
    return strcmp(first.street, second.street);
}

int compareAddressesValue(Value first, Value second)
{
    return compareAddresses(*(Address*)getPointer(first), *(Address*)getPointer(second));
}

int getIndex(Tree* dataBase, Address address)
{
    Value index = get(dataBase, wrapPointer(&address));
    return index.type != NONE_TYPE ? getInt(index) : -1;
}

Tree* deleteBlock(Tree* dataBase, Address address)
{
    if (!dataBase)
        return NULL;
    dataBase->left = deleteBlock(dataBase->left, address);
    dataBase->right = deleteBlock(dataBase->right, address);
    if (compareAddresses(*((Address*)getPointer(dataBase->key)), address) == 0)
        dataBase = removeKey(dataBase, dataBase->key);
    return dataBase;
}

Tree* deleteHouse(Tree* dataBase, Address address)
{
    if (!dataBase)
        return NULL;
    dataBase->left = deleteHouse(dataBase->left, address);
    dataBase->right = deleteHouse(dataBase->right, address);
    if (((Address*)getPointer(dataBase->key))->house == address.house && strcmp(((Address*)getPointer(dataBase->key))->street, address.street) == 0)
        dataBase = removeKey(dataBase, dataBase->key);
    return dataBase;
}

Tree* deleteStreet(Tree* dataBase, Address address)
{
    if (!dataBase)
        return NULL;
    dataBase->left = deleteStreet(dataBase->left, address);
    dataBase->right = deleteStreet(dataBase->right, address);
    if (strcmp(((Address*)getPointer(dataBase->key))->street, address.street) == 0)
        dataBase = removeKey(dataBase, dataBase->key);
    return dataBase;
}

void getList(Tree* dataBase, Address begin, Address end, List** addresses)
{
    if (!dataBase)
        return;
    if (compareAddresses(begin, *((Address*)getPointer(dataBase->key))) < 0 && compareAddresses(*((Address*)getPointer(dataBase->key)), end) < 0)
        addElement(*addresses, dataBase->key, getListSize(*addresses));
    getList(dataBase->left, begin, end, addresses);
    getList(dataBase->right, begin, end, addresses);
}

Tree* renameStreet(Tree* dataBase, char* oldStreetName, char* newStreetName)
{
    if (!dataBase)
        return NULL;
    dataBase->left = renameStreet(dataBase->left, oldStreetName, newStreetName);
    dataBase->right = renameStreet(dataBase->right, oldStreetName, newStreetName);
    Address newKey = { newStreetName, ((Address*)getPointer(dataBase->key))->house, ((Address*)getPointer(dataBase->key))->block };
    dataBase = changeKey(dataBase, dataBase->key, wrapPointer(&newKey));
    return dataBase;
}

int main(int argc, char* argv[])
{
    char mode[12];
    printf("Enter work mode: ");
    scanf("%s", mode);
    Tree* dataBase = NULL;
    int operationsCount = 0;
    if (strcmp(mode, "Interactive") == 0 || strcmp(mode, "interactive") == 0) {
        scanf("%i", &operationsCount);
        for (int k = 0; k < operationsCount; ++k) {
            char operation[14];
            scanf("%s", operation);
            if (strcmp(operation, "GET") == 0 || strcmp(operation, "get") == 0) {
                char street[64];
                int house = 0;
                int block = 0;
                scanf("%s %i %i", street, &house, &block);
                Address address = { street, house, block };
                int index = getIndex(dataBase, address);
                if (index == -1)
                    printf("None\n");
                else
                    printf("%i\n", index);
            } else if (strcmp(operation, "CREATE") == 0 || strcmp(operation, "create") == 0) {
                char* street = malloc(64 * sizeof(char));
                int house = 0;
                int block = 0;
                int index = 0;
                scanf("%s %i %i %i", street, &house, &block, &index);
                Address* address = malloc(sizeof(Address));
                address->street = street;
                address->house = house;
                address->block = block;
                dataBase = dataBase ? put(dataBase, wrapPointer(address), wrapInt(index)) : createTree(wrapPointer(&address), wrapInt(index), compareAddressesValue);
            } else if (strcmp(operation, "DELETE_BLOCK") == 0 || strcmp(operation, "delete_block") == 0) {
                char street[64];
                int house = 0;
                int block = 0;
                scanf("%s %i %i", street, &house, &block);
                Address address = { street, house, block };
                dataBase = deleteBlock(dataBase, address);
            } else if (strcmp(operation, "DELETE_HOUSE") == 0 || strcmp(operation, "delete_house") == 0) {
                char street[64];
                int house = 0;
                scanf("%s %i", street, &house);
                Address address = { street, house, 0 };
                dataBase = deleteHouse(dataBase, address);
            } else if (strcmp(operation, "DELETE_HOUSE") == 0 || strcmp(operation, "delete_house") == 0) {
                char street[64];
                scanf("%s", street);
                Address address = { street, 0, 0 };
                dataBase = deleteStreet(dataBase, address);
            } else if (strcmp(operation, "LIST") == 0 || strcmp(operation, "list") == 0) {
                char street1[64];
                char street2[64];
                int house1 = 0;
                int house2 = 0;
                int block1 = 0;
                int block2 = 0;
                scanf("%s %i %i", street1, &house1, &block1);
                scanf("%s %i %i", street2, &house2, &block2);
                Address address1 = { street1, house1, block1 };
                Address address2 = { street2, house2, block2 };
                List* list = makeNewList();
                getList(dataBase, address1, address2, &list);
                Address* addresses = malloc(getListSize(list) * sizeof(Address));
                int i = 0;
                for (ListElement* element = list->head; element; element = element->next, i++)
                    addresses[i] = *(Address*)getPointer(element->data);
                qsort(addresses, getListSize(list), sizeof(Address), compareAddresses);
                for (int j = 0; j < getListSize(list); ++j)
                    printf("%s %i %i\n", addresses[j].street, addresses[j].house, addresses[j].block);
                printf("\n");
                free(addresses);
            } else if (strcmp(operation, "RENAME") == 0 || strcmp(operation, "rename") == 0) {
                char* oldStreetName = malloc(64 * sizeof(char));
                char* newStreetName = malloc(64 * sizeof(char));
                scanf("%s %s", oldStreetName, newStreetName);
                dataBase = renameStreet(dataBase, oldStreetName, newStreetName);
            }
        }
    } else if (strcmp(mode, "Static") == 0 || strcmp(mode, "static") == 0) {
        FILE* streetsLogs = fopen(argv[1], "r");
        FILE* streetsResults = fopen(argv[2], "w");
        if (!streetsLogs && !streetsResults) {
            printf("Input and output file open error!");
            return 0;
        } else if (!streetsLogs) {
            fclose(streetsResults);
            printf("Input file open error!");
            return 0;
        } else if (!streetsResults) {
            fclose(streetsLogs);
            printf("Output file open error!");
            return 0;
        }

        fscanf(streetsLogs, "%i", &operationsCount);
        for (int k = 0; k < operationsCount; ++k) {
            char operation[14];
            fscanf(streetsLogs, "%s", operation);
            if (strcmp(operation, "GET") == 0 || strcmp(operation, "get") == 0) {
                char street[64];
                int house = 0;
                int block = 0;
                fscanf(streetsLogs, "%s %i %i", street, &house, &block);
                Address address = { street, house, block };
                int index = getIndex(dataBase, address);
                if (index == -1)
                    fprintf(streetsResults, "None\n");
                else
                    fprintf(streetsResults, "%i\n", index);
            } else if (strcmp(operation, "CREATE") == 0 || strcmp(operation, "create") == 0) {
                char* street = malloc(64 * sizeof(char));
                int house = 0;
                int block = 0;
                int index = 0;
                fscanf(streetsLogs, "%s %i %i %i", street, &house, &block, &index);
                Address* address = malloc(sizeof(Address));
                address->street = street;
                address->house = house;
                address->block = block;
                dataBase = dataBase ? put(dataBase, wrapPointer(address), wrapInt(index)) : createTree(wrapPointer(&address), wrapInt(index), compareAddressesValue);
            } else if (strcmp(operation, "DELETE_BLOCK") == 0 || strcmp(operation, "delete_block") == 0) {
                char street[64];
                int house = 0;
                int block = 0;
                fscanf(streetsLogs, "%s %i %i", street, &house, &block);
                Address address = { street, house, block };
                dataBase = deleteBlock(dataBase, address);
            } else if (strcmp(operation, "DELETE_HOUSE") == 0 || strcmp(operation, "delete_house") == 0) {
                char street[64];
                int house = 0;
                fscanf(streetsLogs, "%s %i", street, &house);
                Address address = { street, house, 0 };
                dataBase = deleteHouse(dataBase, address);
            } else if (strcmp(operation, "DELETE_HOUSE") == 0 || strcmp(operation, "delete_house") == 0) {
                char street[64];
                fscanf(streetsLogs, "%s", street);
                Address address = { street, 0, 0 };
                dataBase = deleteStreet(dataBase, address);
            } else if (strcmp(operation, "LIST") == 0 || strcmp(operation, "list") == 0) {
                char street1[64];
                char street2[64];
                int house1 = 0;
                int house2 = 0;
                int block1 = 0;
                int block2 = 0;
                fscanf(streetsLogs, "%s %i %i", street1, &house1, &block1);
                fscanf(streetsLogs, "%s %i %i", street2, &house2, &block2);
                Address address1 = { street1, house1, block1 };
                Address address2 = { street2, house2, block2 };
                List* list = makeNewList();
                getList(dataBase, address1, address2, &list);
                Address* addresses = malloc(getListSize(list) * sizeof(Address));
                int i = 0;
                for (ListElement* element = list->head; element; element = element->next, i++)
                    addresses[i] = *(Address*)getPointer(element->data);
                qsort(addresses, getListSize(list), sizeof(Address), compareAddresses);
                for (int j = 0; j < getListSize(list); ++j)
                    fprintf(streetsResults, "%s %i %i\n", addresses[j].street, addresses[j].house, addresses[j].block);
                fprintf(streetsResults, "\n");
                free(addresses);
            } else if (strcmp(operation, "RENAME") == 0 || strcmp(operation, "rename") == 0) {
                char* oldStreetName = malloc(64 * sizeof(char));
                char* newStreetName = malloc(64 * sizeof(char));
                fscanf(streetsLogs, "%s %s", oldStreetName, newStreetName);
                dataBase = renameStreet(dataBase, oldStreetName, newStreetName);
            }
        }
    } else {
        printf("You entered the operating mode incorrectly. Try again");
    }
    return 0;
}