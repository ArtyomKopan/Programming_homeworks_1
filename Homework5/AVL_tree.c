#include "AVL_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(Tree* tree)
{
    return tree ? tree->height : 0;
}

int balanceFactor(Tree* tree)
{
    return tree ? getHeight(tree->right) - getHeight(tree->left) : 0;
}

void fixHeight(Tree* tree)
{
    if (tree)
        tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;
}

Tree* rotateRight(Tree* tree)
{
    Tree* newTree = tree->left;
    tree->left = newTree->right;
    newTree->right = tree;
    fixHeight(tree);
    fixHeight(newTree);
    return newTree;
}

Tree* rotateLeft(Tree* tree)
{
    Tree* newTree = tree->right;
    tree->right = newTree->left;
    newTree->left = tree;
    fixHeight(tree);
    fixHeight(newTree);
    return newTree;
}

Tree* balance(Tree* tree)
{
    fixHeight(tree);
    if (balanceFactor(tree) == 2) {
        if (balanceFactor(tree->right) < 0)
            tree->right = rotateRight(tree->right);
        return rotateLeft(tree);
    }
    if (balanceFactor(tree) == -2) {
        if (balanceFactor(tree->left) > 0)
            tree->left = rotateLeft(tree->left);
        return rotateRight(tree);
    }
    return tree;
}

Tree* createTree(int key, int value)
{
    Tree* tree = malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    tree->key = key;
    tree->value = value;
    return tree;
}

void deleteTree(Tree* tree)
{
    if (!tree)
        return;
    if (tree->left)
        deleteTree(tree->left);
    if (tree->right)
        deleteTree(tree->right);
    free(tree);
}

bool hasKey(Tree* tree, int key)
{
    if (!tree)
        return false;
    if (tree->key == key)
        return true;
    return hasKey(tree->left, key) || hasKey(tree->right, key);
}

Tree* put(Tree* tree, int key, int value)
{
    if (tree->key == key)
        tree->value = value;
    else if (key > tree->key) {
        if (!tree->right)
            tree->right = createTree(key, value);
        else
            tree->right = put(tree->right, key, value);
    } else {
        if (!tree->left)
            tree->left = createTree(key, value);
        else
            tree->left = put(tree->left, key, value);
    }
    return balance(tree);
}

int get(Tree* tree, int key)
{
    if (!tree)
        return 0;
    if (tree->key == key)
        return tree->value;
    if (key < tree->key)
        return get(tree->left, key);
    else
        return get(tree->right, key);
}

int getMinimum(Tree* tree)
{
    if (!tree)
        return 0;
    return (tree->left) ? getMinimum(tree->left) : tree->key;
}

int getMaximum(Tree* tree)
{
    if (!tree)
        return 0;
    return (tree->right) ? getMaximum(tree->right) : tree->key;
}

Tree* findMinimum(Tree* tree)
{
    return (tree && tree->left) ? findMinimum(tree->left) : tree;
}

Tree* removeMinimum(Tree* tree)
{
    if (!tree)
        return tree;
    if (!tree->left)
        return tree->right;
    tree->left = removeMinimum(tree->left);
    return balance(tree);
}

Tree* removeKey(Tree* tree, int key)
{
    if (key < tree->key) {
        tree->left = removeKey(tree->left, key);
        return balance(tree);
    } else if (key > tree->key) {
        tree->right = removeKey(tree->right, key);
        return balance(tree);
    } else {
        Tree* minRight = findMinimum(tree->right);
        if (!minRight) {
            Tree* treeLeft = tree->left;
            free(tree);
            return balance(treeLeft);
        }
        minRight->right = removeMinimum(tree->right);
        minRight->left = tree->left;
        free(tree);
        return balance(minRight);
    }
}

int getLowerBound(Tree* tree, int key)
{
    if (!tree)
        return 0;
    return (tree->key >= key) ? tree->key : getLowerBound(tree->right, key);
}

int getUpperBound(Tree* tree, int key)
{
    if (!tree)
        return 0;
    return (tree->key > key) ? tree->key : getUpperBound(tree->right, key);
}
