// Стварэнне пустога дрэва.
template <typename T>
BinaryTree<T>::BinaryTree()
    : root(nullptr), count(0)
{
}

// Канструктар капіявання (глыбокая копія).
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
    : root(this->copy_node(other.root)), count(other.count)
{
}

// Вызваленне ўсіх вузлоў.
template <typename T>
BinaryTree<T>::~BinaryTree()
{
    this->clear_node(this->root);
}

// Аператар прысвойвання (спачатку копія, потым выдаленне старога).
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other)
{
    if (this != &other)
    {
        Node* new_root = this->copy_node(other.root);

        this->clear_node(this->root);
        this->root = new_root;
        this->count = other.count;
    }

    return *this;
}

// Рэкурсіўнае глыбокае капіяванне паддрэва.
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copy_node(const Node* node) const
{
    if (!node)
        return nullptr;

    Node* copy = new Node(node->data);
    copy->left = this->copy_node(node->left);
    copy->right = this->copy_node(node->right);

    return copy;
}

// Выдаленне паддрэва: спачатку нашчадкі, потым сам вузел.
template <typename T>
void BinaryTree<T>::clear_node(Node* node)
{
    if (!node)
        return;

    this->clear_node(node->left);
    this->clear_node(node->right);

    delete node;
}

// Рэкурсіўная ўстаўка вузла.
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insert_node(Node* node, const T& value, bool& added)
{
    if (!node)
    {
        added = true;
        return new Node(value);
    }

    if (value < node->data)
        node->left = this->insert_node(node->left, value, added);
    else if (node->data < value)
        node->right = this->insert_node(node->right, value, added);

    // Ні менш, ні больш: элемент ужо ёсць у дрэве.
    return node;
}

// Рэкурсіўнае выдаленне вузла.
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::remove_node(Node* node, const T& value, bool& removed)
{
    if (!node)
        return nullptr;

    if (value < node->data)
    {
        node->left = this->remove_node(node->left, value, removed);
        return node;
    }

    if (node->data < value)
    {
        node->right = this->remove_node(node->right, value, removed);
        return node;
    }

    removed = true;

    // Няма левага нашчадка (уключаючы ліст).
    if (!node->left)
    {
        Node* child = node->right;
        delete node;

        return child;
    }

    // Ёсць толькі левы нашчадак.
    if (!node->right)
    {
        Node* child = node->left;
        delete node;

        return child;
    }

    // Два нашчадкі: пераносім мінімум правага паддрэва і выдаляем яго вузел.
    Node* min_node = node->right;
    while (min_node->left)
        min_node = min_node->left;

    node->data = min_node->data;

    bool min_removed = false;
    node->right = this->remove_node(node->right, node->data, min_removed);

    return node;
}

// Рэкурсіўны пошук вузла.
template <typename T>
const typename BinaryTree<T>::Node* BinaryTree<T>::find_node(const Node* node, const T& value) const
{
    if (!node)
        return nullptr;

    if (value < node->data)
        return this->find_node(node->left, value);

    if (node->data < value)
        return this->find_node(node->right, value);

    return node;
}

// Сіметрычны абыход (элементы па павелічэнні).
template <typename T>
void BinaryTree<T>::print_in_order(const Node* node) const
{
    if (!node)
        return;

    this->print_in_order(node->left);
    std::cout << node->data << "\n";
    this->print_in_order(node->right);
}

// Вывад дрэва бокам: водступ паказвае глыбіню вузла.
template <typename T>
void BinaryTree<T>::print_sideways(const Node* node, int level) const
{
    if (!node)
        return;

    this->print_sideways(node->right, level + 1);

    for (int i = 0; i < level; i++)
        std::cout << "    ";

    std::cout << node->data << "\n";

    this->print_sideways(node->left, level + 1);
}

// Даданне элемента (false, калі такі ўжо ёсць).
template <typename T>
bool BinaryTree<T>::add(const T& value)
{
    bool added = false;

    this->root = this->insert_node(this->root, value, added);
    if (added)
        this->count++;

    return added;
}

// Выдаленне элемента (false, калі не знойдзены).
template <typename T>
bool BinaryTree<T>::remove(const T& value)
{
    bool removed = false;

    this->root = this->remove_node(this->root, value, removed);
    if (removed)
        this->count--;

    return removed;
}

// Пошук элемента (nullptr, калі не знойдзены).
template <typename T>
const T* BinaryTree<T>::find(const T& value) const
{
    const Node* node = this->find_node(this->root, value);

    return node ? &node->data : nullptr;
}

// Вывад структуры дрэва і адсартаванага спіса.
template <typename T>
void BinaryTree<T>::print() const
{
    if (!this->root)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::cout << "Tree structure (root on the left, right branch on top):\n";
    this->print_sideways(this->root, 0);

    std::cout << "\nSorted order:\n";
    this->print_in_order(this->root);
}

// Колькасць элементаў.
template <typename T>
int BinaryTree<T>::size() const
{
    return this->count;
}

// Праверка пустога дрэва.
template <typename T>
bool BinaryTree<T>::is_empty() const
{
    return this->root == nullptr;
}
