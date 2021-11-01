#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Tree Tree;

int size = 0;

struct Tree {
    int key;
    int height;
    Tree* left;
    Tree* right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(Tree* tree)
{
    return (tree) ? tree->height : 0;
}

int balanceFactor(Tree* tree)
{
    return getHeight(tree->right) - getHeight(tree->left);
}

void fixHeight(Tree* tree)
{
    int heightLeft = getHeight(tree->left);
    int heightRight = getHeight(tree->right);
    tree->height = max(heightLeft, heightRight) + 1;
}

Tree* rotateRight(Tree* tree)
{
    Tree* newRoot = tree->left;
    tree->left = newRoot->right;
    newRoot->right = tree;
    fixHeight(tree);
    fixHeight(newRoot);
    return newRoot;
}

Tree* rotateLeft(Tree* tree)
{
    Tree* newRoot = tree->right;
    tree->right = newRoot->left;
    newRoot->left = tree;
    fixHeight(tree);
    fixHeight(newRoot);
    return newRoot;
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

Tree* createTree(int key)
{
    Tree* tree = malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    tree->key = key;
    size++;
    return tree;
}

void deleteTree(Tree* tree)
{
    if (tree->left)
        deleteTree(tree->left);
    if (tree->right)
        deleteTree(tree->right);
    free(tree);
}

void put(Tree* tree, int key)
{
    if (key >= tree->key) {
        if (!tree->right)
            tree->right = createTree(key);
        else
            put(tree->right, key);
    } else {
        if (!tree->left)
            tree->left = createTree(key);
        else
            put(tree->left, key);
    }
    balance(tree);
}

int main()
{
    Tree* root = createTree(rand());
    double max1 = 0;
    for (int i = 0; i < 1000; i++) {
        put(root, rand());
        if (i > 100) {
            double d = getHeight(root) / log2(size);
            max1 = (d > max1) ? d : max1;
        }
    }
    printf("%lf\n", max1);
    deleteTree(root);

    size = 0;
    root = createTree(0);
    double max2 = 0;
    for (int i = 0; i < 1000; ++i) {
        put(root, i + 1);
        if (i > 100) {
            double d = getHeight(root) / log2(size);
            max2 = (d > max2) ? d : max2;
        }
    }
    printf("%lf", max2);
    deleteTree(root);
    return 0;
}