/*Лабораторная работа №4. Шаблоны.
Вариант 5: бинарное дерево.

Условие: реализовать шаблон класса (по варианту) для представления
элементов, использовать шаблон класса. Объекты из лабораторной работы
№3 вписывать в шаблон по варианту.
Реализовать методы:
- добавление элемента
- удаление элемента
- вывод шаблона на экран
- поиск какого-либо объекта (элемента)
- зацикливание программы
*/

#pragma once

#include <iostream>

template <typename T>
class BinaryTree
{
private:
    struct Node
    {
        T data;
        Node* left;
        Node* right;

        Node(const T& value)
            : data(value), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;
    int count;

    Node* copy_node(const Node* node) const;
    void clear_node(Node* node);
    Node* insert_node(Node* node, const T& value, bool& added);
    Node* remove_node(Node* node, const T& value, bool& removed);
    const Node* find_node(const Node* node, const T& value) const;
    void print_in_order(const Node* node) const;
    void print_sideways(const Node* node, int level) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& other);

    bool add(const T& value);
    bool remove(const T& value);
    const T* find(const T& value) const;
    void print() const;

    int size() const;
    bool is_empty() const;
};

#include "tree.tpp"
