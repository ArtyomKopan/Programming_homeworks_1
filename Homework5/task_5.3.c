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

Tree* createTree(int key)
{
    Tree* tree = malloc(sizeof(Tree));
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    tree->key = key;
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

Tree* put(Tree* tree, int key)
{
    if (key >= tree->key) {
        if (!tree->right)
            tree->right = createTree(key);
        else
            tree->right = put(tree->right, key);
    } else {
        if (!tree->left)
            tree->left = createTree(key);
        else
            tree->left = put(tree->left, key);
    }
    return balance(tree);
}

int main()
{
    // при добавлении случайных чисел усредним полученные значения максимумов
    double sum = 0;
    for (int k = 0; k < 100; ++k) {
        size = 1;
        Tree* root = createTree(rand());
        double max1 = 0;
        for (int i = 0; i < 1000; i++) {
            root = put(root, rand());
            size++;
            if (i > 100) {
                double d = getHeight(root) / log2(size);
                max1 = (d > max1) ? d : max1;
            }
        }
        sum += max1;
        deleteTree(root);
    }
    printf("%lf\n", sum / 100);

    size = 1;
    Tree* root = createTree(0);
    double max2 = 0;
    for (int i = 0; i < 1000; ++i) {
        root = put(root, i + 1);
        size++;
        if (i > 100) {
            double d = getHeight(root) / log2(size);
            max2 = (d > max2) ? d : max2;
        }
    }
    printf("%lf", max2);
    deleteTree(root);
    return 0;
}