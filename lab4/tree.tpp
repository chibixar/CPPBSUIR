template <typename T>
BinaryTree<T>::BinaryTree()
    : root(nullptr), count(0)
{
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
    : root(copyNode(other.root)), count(other.count)
{
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
    clearNode(root);
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& other)
{
    if (this != &other)                                     // Абарона ад прысвойвання самому сабе.
    {
        clearNode(root);

        root = copyNode(other.root);
        count = other.count;
    }

    return *this;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copyNode(const Node* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    Node* copy = new Node(node->data);
    copy->left = copyNode(node->left);
    copy->right = copyNode(node->right);

    return copy;
}

template <typename T>
void BinaryTree<T>::clearNode(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    clearNode(node->left);                                  // Спачатку вызваляюцца нашчадкі, потым сам вузел.
    clearNode(node->right);

    delete node;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::insertNode(Node* node, const T& value, bool& added)
{
    if (node == nullptr)
    {
        added = true;
        return new Node(value);
    }

    if (value < node->data)
    {
        node->left = insertNode(node->left, value, added);
    }
    else if (node->data < value)
    {
        node->right = insertNode(node->right, value, added);
    }

    return node;                                            // Калі ні меней, ні болей, элемент ужо ёсць у дрэве.
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::removeNode(Node* node, const T& value, bool& removed)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value < node->data)
    {
        node->left = removeNode(node->left, value, removed);
    }
    else if (node->data < value)
    {
        node->right = removeNode(node->right, value, removed);
    }
    else
    {
        removed = true;

        if (node->left == nullptr)                          // Выпадак без левага нашчадка (уключаючы ліст).
        {
            Node* child = node->right;
            delete node;
            return child;
        }

        if (node->right == nullptr)                         // Выпадак толькі з левым нашчадкам.
        {
            Node* child = node->left;
            delete node;
            return child;
        }

        Node* minNode = node->right;                        // Два нашчадкі: шукаем найменшы вузел у правым паддрэве.

        while (minNode->left != nullptr)
        {
            minNode = minNode->left;
        }

        node->data = minNode->data;

        bool minRemoved = false;
        node->right = removeNode(node->right, minNode->data, minRemoved); // Выдаляем вузел, дадзеныя якога перанесены ўверх.
    }

    return node;
}

template <typename T>
const typename BinaryTree<T>::Node* BinaryTree<T>::findNode(const Node* node, const T& value) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value < node->data)
    {
        return findNode(node->left, value);
    }

    if (node->data < value)
    {
        return findNode(node->right, value);
    }

    return node;
}

template <typename T>
void BinaryTree<T>::printInOrder(const Node* node) const
{
    if (node == nullptr)
    {
        return;
    }

    printInOrder(node->left);                               // Сіметрычны абход дае адсартаваны парадак.
    std::cout << node->data << "\n";
    printInOrder(node->right);
}

template <typename T>
void BinaryTree<T>::printSideways(const Node* node, int level) const
{
    if (node == nullptr)
    {
        return;
    }

    printSideways(node->right, level + 1);

    for (int i = 0; i < level; i++)
    {
        std::cout << "    ";                                // Водступ паказвае глыбіню вузла.
    }

    std::cout << node->data << "\n";

    printSideways(node->left, level + 1);
}

template <typename T>
bool BinaryTree<T>::add(const T& value)
{
    bool added = false;

    root = insertNode(root, value, added);

    if (added)
    {
        count++;
    }

    return added;
}

template <typename T>
bool BinaryTree<T>::remove(const T& value)
{
    bool removed = false;

    root = removeNode(root, value, removed);

    if (removed)
    {
        count--;
    }

    return removed;
}

template <typename T>
const T* BinaryTree<T>::find(const T& value) const
{
    const Node* node = findNode(root, value);

    if (node == nullptr)
    {
        return nullptr;
    }

    return &node->data;
}

template <typename T>
void BinaryTree<T>::print() const
{
    if (root == nullptr)
    {
        std::cout << "Tree is empty.\n";
        return;
    }

    std::cout << "Tree structure (root on the left, right branch on top):\n";
    printSideways(root, 0);

    std::cout << "\nSorted order:\n";
    printInOrder(root);
}

template <typename T>
int BinaryTree<T>::size() const
{
    return count;
}

template <typename T>
bool BinaryTree<T>::isEmpty() const
{
    return root == nullptr;
}
