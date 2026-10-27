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

    Node* copyNode(const Node* node) const;                 // Рэкурсіўнае глыбокае капіраванне паддрэва.
    void clearNode(Node* node);
    Node* insertNode(Node* node, const T& value, bool& added);
    Node* removeNode(Node* node, const T& value, bool& removed);
    const Node* findNode(const Node* node, const T& value) const;
    void printInOrder(const Node* node) const;
    void printSideways(const Node* node, int level) const;

public:
    BinaryTree();
    BinaryTree(const BinaryTree& other);                    // Глыбокая копія.
    ~BinaryTree();

    BinaryTree& operator=(const BinaryTree& other);

    bool add(const T& value);                               // Вяртае false, калі такі элемент ужо ёсць.
    bool remove(const T& value);
    const T* find(const T& value) const;                    // Вяртае nullptr, калі элемент не знойдзены.
    void print() const;

    int size() const;
    bool isEmpty() const;
};

#include "tree.tpp"                                         // Рэалізацыя шаблона павінна быць бачна пры інстанцыраванні.
