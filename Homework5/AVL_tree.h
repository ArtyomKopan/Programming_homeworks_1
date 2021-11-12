#pragma once
#ifndef HOMEWORK5_AVL_TREE_H
#define HOMEWORK5_AVL_TREE_H

#include "values.h"
#include <stdbool.h>

typedef struct Tree Tree;

struct Tree {
    Value key;
    Value value;
    int height;
    Tree* left;
    Tree* right;
};

/**
 * Создаёт экземпляр структуры данных
 */
// Tree* createTree(Comparator comparator);
Tree* createTree(Value key, Value value);

/**
 * Уничтожает экземпляр структуры данных. Очистка памяти
 * из-под хранящихся в структуре элементов – зона
 * ответственности пользователя структуры данных.
 */
void deleteTree(Tree* tree);

/**
 * Ассоциирует с ключом key значение value.
 * Если ключ уже присутствовал в структуре данных,
 * то прошлое значение перезаписывается
 */
Tree* put(Tree* tree, Value key, Value value);

/**
 * Удаляет ключ и ассоциированное с ним значение
 * из структуры данных.
 * Если ключ не присутствовал в структуре, то ничего не делает
 */
Tree* removeKey(Tree* tree, Value key);

/**
 * Возвращает ассоциированное с ключом key значение.
 * Если ключ не присутствовал в структуре, то возвращает
 * значение Value с указанным типом NONE_TYPE
 */
Value get(Tree* tree, Value key);

/**
 * Проверяет наличие ключа key в структуре данных
 */
bool hasKey(Tree* tree, Value key);

/**
 * Возвращает наименьший находящийся в структуре ключ,
 * который больше либо равен указанному значению
 */
Value getLowerBound(Tree* tree, Value key);

/**
 * Возвращает наименьший находящийся в структуре ключ,
 * который строго больше указанного значения
 */
Value getUpperBound(Tree* tree, Value key);

/**
 * Возвращает наибольший находящийся в структуре ключ
 */
Value getMaximum(Tree* tree);

/**
 * Возвращает наименьший находящийся в структуре ключ
 */
Value getMinimum(Tree* tree);

/*
 * Iterator - своего рода “указатель” на элементы
 * в структуре данных. В каждый момент времени он внутри
 * себя хранит указатель на какой-то элемент структуры.
 * Функции getKey и getValue позволяют получить ключ
 * и значение элемента, на который указывает итератор.
 */
// TreeIterator getIterator(Tree* tree);
// Value getKey(TreeIterator* iterator);
// Value getValue(TreeIterator* iterator);

/**
 * Метод next заставляет итератор перейти к следующему
 * элементу структуры.
 * Если такого элемента не существует, то считайте, что
 * итератор указывает на NULL.
 */
// void next(TreeIterator* iterator);

/**
 * Метод hasElement проверяет, что итератор сейчас
 * указывает на корректный элемент структуры данных,
 * а не на NULL.
 */
// bool hasElement(TreeIterator* iterator);

#endif