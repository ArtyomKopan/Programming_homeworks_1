#include "AVL_tree.h"
#include "list.h"
#include "values.h"
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

Tree* createTree(Value key, Value value, Comparator comparator)
{
    Tree* tree = malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    tree->key = key;
    tree->value = value;
    tree->comparator = comparator;
    return tree;
}

void deleteTree(Tree* tree)
{
    if (!tree)
        return;
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
}

bool hasKey(Tree* tree, Value key)
{
    if (!tree)
        return false;
    if (tree->comparator(key, tree->key) == 0)
        return true;
    else if (tree->comparator(key, tree->key) < 0)
        return hasKey(tree->left, key);
    else
        return hasKey(tree->right, key);
}

Tree* put(Tree* tree, Value key, Value value)
{
    if (tree->comparator(tree->key, key) == 0)
        tree->value = value;
    else if (tree->comparator(key, tree->key) > 0) {
        if (!tree->right)
            tree->right = createTree(key, value, tree->comparator);
        else
            tree->right = put(tree->right, key, value);
    } else {
        if (!tree->left)
            tree->left = createTree(key, value, tree->comparator);
        else
            tree->left = put(tree->left, key, value);
    }
    return balance(tree);
}

Value get(Tree* tree, Value key)
{
    if (!tree)
        return wrapNone();
    if (tree->comparator(tree->key, key) == 0)
        return tree->value;
    if (tree->comparator(key, tree->key) < 0)
        return get(tree->left, key);
    else
        return get(tree->right, key);
}

Value getMinimum(Tree* tree)
{
    if (!tree)
        return wrapNone();
    return tree->left ? getMinimum(tree->left) : tree->key;
}

Value getMaximum(Tree* tree)
{
    if (!tree)
        return wrapNone();
    return tree->right ? getMaximum(tree->right) : tree->key;
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

Tree* removeKey(Tree* tree, Value key)
{
    if (!tree)
        return tree;
    if (tree->comparator(key, tree->key) < 0) {
        tree->left = removeKey(tree->left, key);
        return balance(tree);
    } else if (tree->comparator(key, tree->key) > 0) {
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

Value getLowerBound(Tree* tree, Value key)
{
    if (!tree)
        return wrapNone();
    if (tree->comparator(tree->key, key) == 0)
        return tree->key;
    else if (tree->comparator(tree->key, key) < 0)
        return getLowerBound(tree->right, key);
    else {
        Value foundValue = getLowerBound(tree->left, key);
        return !isNone(foundValue) ? foundValue : tree->key;
    }
}

Value getUpperBound(Tree* tree, Value key)
{
    if (!tree)
        return wrapNone();
    if (tree->comparator(tree->key, key) <= 0)
        return getUpperBound(tree->right, key);
    else {
        Value foundValue = getUpperBound(tree->left, key);
        return !isNone(foundValue) ? foundValue : tree->key;
    }
}

Tree* changeKey(Tree* tree, Value oldKey, Value newKey)
{
    if (!tree || !hasKey(tree, oldKey))
        return NULL;
    if (tree->comparator(tree->key, oldKey) == 0)
        tree->key = newKey;
    else if (tree->comparator(oldKey, tree->key) > 0)
        tree->right = changeKey(tree->right, oldKey, newKey);
    else
        tree->left = changeKey(tree->left, oldKey, newKey);
    return balance(tree);
}
