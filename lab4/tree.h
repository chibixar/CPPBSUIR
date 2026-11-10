/*Лабараторная праца №4. Шаблоны.
Варыянт 5: бінарнае дрэва.

Умова: рэалізаваць шаблон класа (па варыянце) для прадстаўлення
элементаў, выкарыстоўваць шаблон класа. Аб'екты з лабараторнай працы
№3 упісваць у шаблон па варыянце.
Рэалізаваць метады:
- даданне элемента
- выдаленне элемента
- вывад шаблона на экран
- пошук якога-небудзь аб'екта (элемента)
- зацыкленне праграмы
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
