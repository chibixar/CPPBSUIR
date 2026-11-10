# Лабораторная №4. Шаблоны. Полная подготовка к защите

Вариант 5: шаблон класса «бинарное дерево» (`BinaryTree<T>`), в который вписаны объекты `Student` из лабораторной №3.

> Как пользоваться. Классы `Fakultet` и `Student` подробно разобраны в `defense_lab3.md`; здесь то, что нового: шаблоны, дерево, изменения в `Student`. Раздел 6: теория. Раздел 7: построчный разбор. Раздел 8: трассировки на примерах (их просят показать у доски). Раздел 9: слабые места. Раздел 10: правки кода «на лету». Раздел 11: вопросы с ответами.

## Содержание

1. Условие задачи
2. Что делает программа и пример запуска
3. Структура проекта и сборка
4. Стиль кода и отличия от лабы №3
5. Диаграммы
6. Теория: шаблоны, бинарное дерево поиска
7. Построчный разбор кода
8. Трассировки на примерах
9. Слабые места и честные ответы
10. Правки кода на защите (готовые сниппеты)
11. Вопросы и ответы
12. Шпаргалка
13. Глоссарий

---

## 1. Условие задачи

> Реализовать шаблон класса (по варианту) для представления элементов, использовать шаблон класса. Объекты из лабораторной работы №3 вписывать в шаблон по варианту. Реализовать методы: добавление элемента, удаление элемента, вывод шаблона на экран, поиск какого-либо объекта (элемента), зацикливание программы.
> Вариант 5: бинарное дерево.

| Требование | Где выполнено |
|---|---|
| Шаблон класса | `template <typename T> class BinaryTree` в `tree.h` / `tree.tpp` |
| Объекты из лабы №3 в шаблоне | `BinaryTree<Student>` в `main.cpp` |
| Добавление | `add` (пункт меню 1) |
| Удаление | `remove` (пункт 2) |
| Вывод | `print` (пункт 3) |
| Поиск | `find` (пункт 4) |
| Зацикливание | внутренний цикл меню + внешний `Continue? (y/n)` |
| Показать, что шаблон универсален | `BinaryTree<int>` в `demo_int` (пункт 6) |
| Дерево самостоятельно управляет памятью | деструктор, конструктор копирования, `operator=` (пункт 5 проверяет копию) |

---

## 2. Что делает программа и пример запуска

1. Пользователь вводит название факультета и количество экзаменов.
2. Открывается меню. Все студенты хранятся в бинарном дереве `BinaryTree<Student>`, упорядоченном по Ф.И.О.
3. Пункты: добавить, удалить по Ф.И.О., вывести дерево, найти по Ф.И.О., проверить копирование дерева, продемонстрировать шаблон с `int`, выход.
4. После выхода из меню (0) программа спрашивает `Continue? (y/n)` и при `y` начинает заново с пустым деревом.

Реальный прогон (добавлены Petrov, Ivanov, Sidorov, Antonov; дубликат Petrov отклонён; затем вывод, удаление Petrov, поиск, копия):

```
MENU (students in tree: 4):
Select operation: Error: Student with this name already exists.     <- повторный Petrov

--- пункт 3 (print) ---
Tree structure (root on the left, right branch on top):
    Sidorov (2002, avg 5.50)
Petrov (2000, avg 8.50)
    Ivanov (2001, avg 8.50)
        Antonov (2003, avg 4.00)

Sorted order:
Antonov (2003, avg 4.00)
Ivanov (2001, avg 8.50)
Petrov (2000, avg 8.50)
Sidorov (2002, avg 5.50)

--- пункт 2 (remove Petrov) ---
Student removed.

--- пункт 3 (print) ---
Tree structure (root on the left, right branch on top):
Sidorov (2002, avg 5.50)
    Ivanov (2001, avg 8.50)
        Antonov (2003, avg 4.00)

Sorted order:
Antonov (2003, avg 4.00)
Ivanov (2001, avg 8.50)
Sidorov (2002, avg 5.50)

--- пункт 4 (find Ivanov) ---
Student found:
Faculty: FAMCS
Full name: Ivanov
Birth year: 2001
Session results: 7 10
Average mark: 8.50

--- пункт 4 (find Nobody) ---
Error: Student not found.
```

Демонстрация `int` (пункт 6):

```
Tree<int> after adding 50 30 70 20 40 60 80:
        80
    70
        60
50
        40
    30
        20
(Sorted order: 20 30 40 50 60 70 80)

After removing 30:
        80
    70
        60
50
    40
        20

Find 40: found
Find 99: not found
```

Если ввести не число в меню, `Invalid choice. Try again.`; если `exams < 0` — `Error: Invalid number of exams.`

---

## 3. Структура проекта и сборка

| Файл | Что внутри |
|------|-----------|
| `tree.h` | Условие, объявление шаблона `BinaryTree<T>`, в конце `#include "tree.tpp"` |
| `tree.tpp` | Определения всех методов шаблона |
| `fakultet.h`, `fakultet.cpp` | Класс `Fakultet` из лабы №3 без изменений |
| `student.h`, `student.cpp` | Класс `Student` из лабы №3 + `operator<` и `operator<<` |
| `main.cpp` | Меню, работа с `BinaryTree<Student>` и демо `BinaryTree<int>` |

Сборка (`.tpp` отдельно не компилируется, он часть заголовка):

```
g++ -std=c++20 -Wall -Wextra -o lab4 main.cpp fakultet.cpp student.cpp
```

**Почему методы шаблона не в `.cpp`, а в `.tpp`.** Шаблон не превращается в машинный код, пока не инстанцирован. Компилятор должен видеть полное определение методов в тот момент, когда встречает `BinaryTree<Student>`. Если положить определения в обычный `.cpp`, то при компиляции `main.cpp` компилятор не сможет сгенерировать код, а при компиляции `tree.cpp` он не знает, какие типы нужны, и получим ошибку линковки `undefined reference`. Расширение `.tpp` — просто соглашение: это не отдельная единица трансляции, а часть заголовка.

**Альтернатива (использована в лабе про транспорт):** определения в `.cpp` и в конце **явное инстанцирование** для нужных типов: `template class BinaryTree<DumpTruck>;`. Плюсы: код компилируется один раз, заголовок короткий. Минус: шаблон работает только с перечисленными типами. У нас шаблон должен принимать и `Student`, и `int`, поэтому выбран подход «определения в заголовке».

---

## 4. Стиль кода и отличия от лабы №3

Структура файлов та же, что в лабе №3: на каждый класс свой заголовок и свой файл методов (`fakultet.h/.cpp`, `student.h/.cpp`); шаблон — `tree.h` + `tree.tpp`.

Стиль единый с лабой №3 и лабой про транспорт:
- `snake_case`: `insert_node`, `print_in_order`, `is_empty`, `get_full_name`.
- `this->` при доступе к членам.
- Над каждой функцией комментарий на русском.
- Однострочные `if` / `for` без фигурных скобок; проверка `!node` вместо `node == nullptr`.
- Копирование и присваивание: сначала новое, потом освобождение старого.

Что добавлено к `Student` по сравнению с лабой №3 (в `student.h` и `student.cpp`; `Fakultet` не менялся):
- `bool operator<(const Student&) const` — сравнение по Ф.И.О. (ключ дерева);
- `std::ostream& operator<<(std::ostream&, const Student&)` — краткий вывод в одну строку для печати дерева.

---

## 5. Диаграммы

### 5.1 Структура шаблона

```
┌────────────────────────────────────────────┐
│  template <typename T> class BinaryTree    │
├────────────────────────────────────────────┤
│ private:                                   │
│   struct Node { T data; Node* left;        │
│                 Node* right; }             │
│   Node* root;   int count;                 │
│   copy_node, clear_node, insert_node,      │
│   remove_node, find_node,                  │
│   print_in_order, print_sideways           │
│ public:                                    │
│   BinaryTree(), BinaryTree(const&), ~..()  │
│   operator=                                │
│   add, remove, find, print, size, is_empty │
└────────────────────────────────────────────┘
        │ инстанцирование (компилятор подставляет T)
        ├──▶ BinaryTree<Student>   (T = Student)
        └──▶ BinaryTree<int>       (T = int)
```

`BinaryTree<Student>` и `BinaryTree<int>` — два разных, несвязанных класса.

### 5.2 Дерево в памяти (пример из прогона)

```
tree.root ──▶ ┌───────────────┐
              │ Node          │
              │ data: Petrov  │
              │ left  ────────┼──▶ Node(Ivanov) ──left──▶ Node(Antonov)
              │ right ────────┼──▶ Node(Sidorov)
              └───────────────┘
Каждый Node выделен через new; data внутри узла — копия Student
(со своим массивом results).
```

### 5.3 Публичный интерфейс и приватные помощники

| Публичный метод | Приватный помощник | Зачем разделение |
|---|---|---|
| `add(value)` | `insert_node(node, value, added)` | пользователю не нужно знать про `Node` и корень |
| `remove(value)` | `remove_node(node, value, removed)` | рекурсия удобна для узлов |
| `find(value)` | `find_node(node, value)` | то же |
| `print()` | `print_in_order`, `print_sideways` | два вида вывода |
| конструктор копирования, `operator=` | `copy_node` | глубокое копирование поддерева |
| деструктор, `operator=` | `clear_node` | освобождение поддерева |

---

## 6. Теория

### 6.1 Что такое шаблон

Шаблон — «чертёж» класса или функции, в котором тип (или значение) заменён параметром.

```cpp
template <typename T>
class BinaryTree { ... };
```

`T` — параметр шаблона. При использовании `BinaryTree<Student>` компилятор подставляет `Student` вместо `T` и **генерирует настоящий класс** (инстанцирование). Всё происходит на этапе компиляции.

Следствия:
- `BinaryTree<int>` и `BinaryTree<Student>` — разные, несвязанные классы.
- Шаблон проверяется дважды: синтаксис в момент объявления, а подставленный тип при инстанцировании. Поэтому ошибка «у `Student` нет `operator<`» появляется только при использовании.
- **Ленивое инстанцирование:** генерируются только те методы, которые реально вызваны. У нас `operator=` дерева в `main` не используется, поэтому его код для `Student` вообще не генерируется (и ошибка в нём не обнаружилась бы, пока кто-то не присвоит дерево).
- Статический полиморфизм (компиляция), в отличие от виртуальных функций (динамический, во время выполнения): нет vtable, нет общего базового класса, возможна полная оптимизация.

**Зачем шаблоны:** написать контейнер один раз и использовать для любого типа, без дублирования кода и без потери типобезопасности (в отличие от `void*`).

### 6.2 Виды шаблонов и параметров

- **Шаблон функции:** `template <typename T> T max_of(T a, T b)`. Тип обычно **выводится** из аргументов: `max_of(1, 2)`.
- **Шаблон класса:** `BinaryTree<Student>`. Тип нужно указывать явно (с C++17 для простых случаев есть вывод CTAD, но здесь не нужен).
- **`typename` и `class`** в параметре шаблона эквивалентны: `template <class T>` = `template <typename T>`.
- **Нетиповые параметры:** `template <typename T, int N> class Array` (значение известно при компиляции).
- **Параметры по умолчанию:** `template <typename T = int>`.
- **Специализация:** полная (`template <> class BinaryTree<char*> {...}`) — особая реализация для конкретного типа; частичная (только для классов) — для семейства типов (`BinaryTree<T*>`).
- **Вариативные шаблоны** (`template <typename... Args>`) — произвольное число параметров, в лабе не нужны.

### 6.3 Шаблоны против альтернатив

| Подход | Плюсы | Минусы |
|---|---|---|
| Шаблон | Типобезопасно, быстро, без наследования | Код в заголовке, длинные сообщения об ошибках, рост размера кода |
| `void*` (как в C) | Один код | Нет проверки типов, приведения вручную |
| Макросы | Подстановка текста | Нет типов, трудная отладка |
| Наследование + virtual | Один код, работает в run-time | Нужна общая база, косвенные вызовы, хранение указателей |
| Копирование кода для каждого типа | Просто | Дублирование |

**Рост размера кода (code bloat):** для каждого набора аргументов компилятор генерирует отдельную копию кода.

### 6.4 Зависимые имена и `typename`

```cpp
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::copy_node(const Node* node) const
```

Имя `BinaryTree<T>::Node` зависит от параметра `T`, и на момент разбора шаблона компилятор не знает, что такое `Node` (тип? статическое поле?). Ключевое слово `typename` говорит: «это тип». Внутри самого класса писать его не нужно. В параметрах (`const Node* node`) после имени класса `BinaryTree<T>::` оно уже не требуется: внутри определения метода контекст класса известен.

Для возвращаемого `const typename BinaryTree<T>::Node*` (в `find_node`) `typename` стоит после `const`.

### 6.5 Требования шаблона к типу `T`

Шаблон неявно требует, чтобы у типа были:
- конструктор копирования (в `Node(const T& value) : data(value)` и при копировании дерева);
- `operator=` (при удалении узла с двумя потомками `node->data = min_node->data`);
- `operator<` (упорядочивание);
- `operator<<` для `std::ostream` (вывод).

Не требуются: конструктор по умолчанию, `operator==`.

Для `int` всё это есть встроенно. Для `Student` мы **добавили** `operator<` и `operator<<`. Конструктор копирования и `operator=` `Student` из лабы №3 делают глубокое копирование массива оценок.

**Почему только `<`, а не `==`:** два элемента считаются **эквивалентными**, если ни один не меньше другого: `!(a < b) && !(b < a)`. Так работают `std::set` и `std::map`. Это называется «строгое слабое упорядочение» (strict weak ordering): `<` иррефлексивно (`a < a` ложно), асимметрично, транзитивно, и эквивалентность транзитивна. Сравнение строк `std::string` этому удовлетворяет.

**Следствие для `Student`:** в дереве два студента с одинаковым Ф.И.О. — «одно и то же», даже если год и оценки разные. Поэтому `add` отклоняет дубликаты по имени, а для поиска/удаления достаточно ключа с одним лишь заполненным Ф.И.О.

В C++20 такие требования можно записать явно через **концепты**: `template <typename T> requires std::totally_ordered<T> class BinaryTree`. Тогда при неподходящем типе будет короткое понятное сообщение. У нас не использовано.

### 6.6 Бинарное дерево поиска (BST)

Дерево, где у каждого узла не более двух потомков (левый и правый), выполняется **свойство упорядоченности**:
- всё в левом поддереве меньше значения узла;
- всё в правом больше.

Терминология: корень, лист (нет потомков), внутренний узел, родитель/потомок, поддерево, глубина узла (расстояние от корня), **высота дерева** (максимальная глубина).

Благодаря свойству поиск идёт как бинарный: на каждом шаге отбрасывается одно из поддеревьев.

**Сложность** (h — высота):

| Операция | В среднем (случайный порядок вставки) | В худшем (вырожденное дерево) |
|---|---|---|
| Поиск | O(log n) | O(n) |
| Вставка | O(log n) | O(n) |
| Удаление | O(log n) | O(n) |
| Вывод всех | O(n) | O(n) |
| Память | O(n) | O(n) |

Вырождение: при вставке уже отсортированных данных (1, 2, 3, ...) каждый новый узел идёт вправо, дерево превращается в связный список, h = n. Наше дерево **не самобалансирующееся** (AVL и красно-чёрные деревья поворотами поддерживают высоту O(log n)), поэтому вырождение возможно. Для лабораторной нормально.

**Обходы** (n узлов, O(n)):
- симметричный (in-order): левое, узел, правое. Для BST даёт элементы **по возрастанию** (`print_in_order`);
- прямой (pre-order): узел, левое, правое (удобен для копирования дерева, сериализации);
- обратный (post-order): левое, правое, узел (удобен для удаления: сначала потомки, потом сам узел; так работает `clear_node`);
- по уровням (level-order, BFS): через очередь.

Наш вывод «боком» `print_sideways` — это обратный симметричный обход (правое, узел, левое) с отступом по глубине: правое поддерево оказывается сверху, корень слева.

**Сравнение с STL:** `std::set<T>` и `std::map<K,V>` — тоже деревья поиска (обычно красно-чёрные, самобалансирующиеся), с итераторами, O(log n) гарантированно. Наше дерево — учебная упрощённая версия.

### 6.7 Рекурсия

Почти все приватные методы рекурсивны: обработка узла = обработка потомков + действие над узлом. **Базовый случай** — `node == nullptr` (пустое поддерево). Глубина рекурсии равна высоте дерева. Для вырожденного дерева из очень большого числа элементов (десятки и сотни тысяч, зависит от платформы и размера кадра) это может привести к переполнению стека. Итеративные версии (цикл вместо рекурсии) этого избегают: см. `find_iterative` в разделе 10.

**Приём «вернуть новый корень поддерева»:** `insert_node` и `remove_node` возвращают `Node*`, и вызывающий присваивает результат: `node->left = insert_node(node->left, ...)`. Благодаря этому не нужны указатели на указатели и особые случаи для корня: при вставке в пустое место возвращается новый узел, при удалении возвращается потомок, заменивший удалённый.

**Параметры-ссылки `bool& added` / `bool& removed`:** рекурсивная функция уже занята возвратом указателя, поэтому результат («удалось ли») сообщается через ссылочный параметр.

### 6.8 Динамическая память в шаблоне: правило трёх

Узлы создаются через `new`, поэтому дерево владеет ресурсами и требует:
- **деструктор** `~BinaryTree()` → `clear_node(root)`;
- **конструктор копирования** → `copy_node` (глубокая копия);
- **`operator=`** → копия + очистка старого.

Поверхностная копия (`root = other.root`) привела бы к тому, что два дерева делят узлы и удаляют их дважды.

Дополнительно (общие понятия из лабы №3): правило пяти (конструктор перемещения и перемещающее присваивание), правило нуля (использовать `std::unique_ptr<Node>` вместо сырых указателей: тогда деструктор и перемещение генерируются сами, но копирование всё равно писать вручную).

### 6.9 Что происходит с данными: хранение по значению

Узел хранит `T data` **по значению**, не указатель. Поэтому:
- `tree.add(student)` кладёт **копию**; локальный `student` в `main` можно уничтожить, дерево не пострадает;
- копия `Student` выполняется глубоко (его конструктором копирования из лабы №3);
- `find` возвращает указатель на `data` **внутри узла**, без копирования.

---

## 7. Построчный разбор кода

### 7.1 `tree.h`

```cpp
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
```

Разбор:
- `template <typename T> class BinaryTree`: шаблон класса.
- `struct Node` объявлена **внутри** класса в разделе `private`: деталь реализации, снаружи не видна. Конструктор `Node(const T&)` копирует значение в `data` и обнуляет потомков. Узлы создаются вручную через `new`.
- Поля дерева: `Node* root` (корень), `int count` (количество элементов для `size()`, чтобы не считать обходом).
- Приватные методы работают с узлами и рекурсивны.
- Публичный интерфейс работает со значениями `T`.
- `const T* find(...) const`: возвращает указатель на элемент внутри дерева или `nullptr`. `const T*` запрещает менять элемент снаружи (иначе можно было бы изменить Ф.И.О. и сломать упорядоченность). Второй `const` — метод не меняет дерево.
- В конце `#include "tree.tpp"`: определения шаблона должны быть видны в месте использования.

### 7.2 `tree.tpp`

```cpp
// Создание пустого дерева
template <typename T>
BinaryTree<T>::BinaryTree()
    : root(nullptr), count(0)
{
}

// Конструктор копирования (глубокая копия)
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& other)
    : root(this->copy_node(other.root)), count(other.count)
{
}

// Освобождение всех узлов
template <typename T>
BinaryTree<T>::~BinaryTree()
{
    this->clear_node(this->root);
}

// Оператор присваивания (сначала копия, потом удаление старого)
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

// Рекурсивное глубокое копирование поддерева
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

// Удаление поддерева: сначала потомки, потом сам узел
template <typename T>
void BinaryTree<T>::clear_node(Node* node)
{
    if (!node)
        return;

    this->clear_node(node->left);
    this->clear_node(node->right);

    delete node;
}

// Рекурсивная вставка узла
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

    // Ни меньше, ни больше: элемент уже есть в дереве
    return node;
}

// Рекурсивное удаление узла
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

    // Нет левого потомка (включая лист)
    if (!node->left)
    {
        Node* child = node->right;
        delete node;

        return child;
    }

    // Есть только левый потомок
    if (!node->right)
    {
        Node* child = node->left;
        delete node;

        return child;
    }

    // Два потомка: переносим минимум правого поддерева и удаляем его узел
    Node* min_node = node->right;
    while (min_node->left)
        min_node = min_node->left;

    node->data = min_node->data;

    bool min_removed = false;
    node->right = this->remove_node(node->right, node->data, min_removed);

    return node;
}

// Рекурсивный поиск узла
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

// Симметричный обход (элементы по возрастанию)
template <typename T>
void BinaryTree<T>::print_in_order(const Node* node) const
{
    if (!node)
        return;

    this->print_in_order(node->left);
    std::cout << node->data << "\n";
    this->print_in_order(node->right);
}

// Вывод дерева боком: отступ показывает глубину узла
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

// Добавление элемента (false, если такой уже есть)
template <typename T>
bool BinaryTree<T>::add(const T& value)
{
    bool added = false;

    this->root = this->insert_node(this->root, value, added);
    if (added)
        this->count++;

    return added;
}

// Удаление элемента (false, если не найден)
template <typename T>
bool BinaryTree<T>::remove(const T& value)
{
    bool removed = false;

    this->root = this->remove_node(this->root, value, removed);
    if (removed)
        this->count--;

    return removed;
}

// Поиск элемента (nullptr, если не найден)
template <typename T>
const T* BinaryTree<T>::find(const T& value) const
{
    const Node* node = this->find_node(this->root, value);

    return node ? &node->data : nullptr;
}

// Вывод структуры дерева и отсортированного списка
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

// Количество элементов
template <typename T>
int BinaryTree<T>::size() const
{
    return this->count;
}

// Проверка пустого дерева
template <typename T>
bool BinaryTree<T>::is_empty() const
{
    return this->root == nullptr;
}
```

Разбор по функциям:

**Конструктор:** `root(nullptr), count(0)` — пустое дерево.

**Конструктор копирования:** `root(this->copy_node(other.root)), count(other.count)`: рекурсивно создаёт новые узлы. Глубокая копия, независимая от оригинала.

**Деструктор:** `clear_node(root)`: рекурсивно удаляет весь граф узлов.

**`operator=`:** защита от `a = a`; **сначала** `copy_node` (создаём новую копию), **потом** `clear_node` (освобождаем старое) и подмена корня. Если `new` в копировании бросит исключение, старое дерево осталось нетронутым (строгая гарантия).

**`copy_node`:** базовый случай `!node` → `nullptr`. Иначе создать копию узла (`new Node(node->data)` — здесь вызывается конструктор копирования `T`), рекурсивно скопировать левое и правое поддеревья. Это прямой (pre-order) обход.

**`clear_node`:** `!node` → выход. Сначала левое, потом правое, потом `delete node`. Обратный (post-order) обход: если удалить узел раньше потомков, указатели на них будут потеряны (утечка). `delete node` вызывает деструктор `T` (для `Student` освобождает массив оценок).

**`insert_node`:**
- пустое место → `added = true`, вернуть новый узел;
- `value < node->data` → идём влево, результат присваиваем `node->left`;
- `node->data < value` → вправо;
- иначе значения эквивалентны → ничего не делаем (дубликат), `added` остаётся `false`;
- возвращаем `node` (корень поддерева без изменений).

**`remove_node`:** три шага.
1. Поиск узла: меньше → влево, больше → вправо (и сразу `return node`, чтобы не проваливаться в код удаления).
2. Нашли (`removed = true`):
   - нет левого потомка (включая лист): вернуть правого потомка (для листа это `nullptr`), `delete node`;
   - нет правого: вернуть левого, `delete node`;
   - два потомка: найти минимум правого поддерева (идём влево до упора), скопировать его данные в текущий узел `node->data = min_node->data`, рекурсивно удалить из правого поддерева узел с этим значением. Вызываем с `node->data` (уже скопированное значение), а не с `min_node->data`, чтобы не передавать ссылку на данные узла, который сейчас будет удалён.
3. Вернуть `node`.

**`find_node`:** `!node` → `nullptr` (не найден); меньше → влево; больше → вправо; иначе нашли, вернуть узел.

**`print_in_order`:** левое, вывод `node->data` через `operator<<` типа `T`, правое. Выводит по возрастанию.

**`print_sideways`:** правое поддерево (level + 1), затем `level` раз по 4 пробела (отступ глубины), затем данные, затем левое поддерево.

**`add`:** `bool added = false;` `root = insert_node(root, value, added);` `if (added) count++;` возвращает `added`.

**`remove`:** то же, `count--`.

**`find`:** вызывает `find_node`, возвращает `&node->data` (адрес данных в узле) или `nullptr`.

**`print`:** пустое дерево → `Tree is empty.`; иначе структура боком и отсортированный список.

**`size`, `is_empty`:** тривиальные.

### 7.3 Добавления в `student.h` / `student.cpp`

В `student.h` добавлен `#include <iostream>` (в объявлении `operator<<` есть `std::ostream`) и два объявления; реализации в `student.cpp`:

```cpp
// Сравнение по Ф.И.О. (ключ дерева)
bool Student::operator<(const Student& other) const
{
    return this->full_name < other.full_name;
}

// Краткий вывод студента в одну строку
std::ostream& operator<<(std::ostream& stream, const Student& student)
{
    stream << student.get_full_name() << " (" << student.get_birth_year()
           << ", avg " << std::format("{:.2f}", student.average()) << ")";

    return stream;
}
```

- `operator<` — метод класса: сравнивает `full_name` как строки (лексикографически, по алфавиту, с учётом регистра и кодов символов). Это **ключ дерева**.
- `operator<<` — **свободная функция**, не метод: левый операнд — `std::ostream`, а не `Student`. Возвращает ссылку на поток для цепочек `std::cout << a << b`. Дружественной не нужно быть: использует публичные геттеры.
- Вывод `Ivanov (2001, avg 8.50)`: в одну строку, годится для узла дерева.

### 7.4 `main.cpp`

```cpp
#include "tree.h"
#include "student.h"
#include <iostream>
#include <string>

// Демонстрация того, что шаблон работает и с другим типом
void demo_int()
{
    BinaryTree<int> numbers;
    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int value : values)
        numbers.add(value);

    std::cout << "\nTree<int> after adding 50 30 70 20 40 60 80:\n";
    numbers.print();

    numbers.remove(30);

    std::cout << "\nAfter removing 30:\n";
    numbers.print();

    std::cout << "\nFind 40: " << (numbers.find(40) ? "found" : "not found") << "\n";
    std::cout << "Find 99: " << (numbers.find(99) ? "found" : "not found") << "\n";
}

// Ключ поиска и удаления: студент с нужным Ф.И.О.
void read_key(Student& key)
{
    std::string name;

    std::cout << "Enter full name: ";
    std::getline(std::cin >> std::ws, name);

    key.set_full_name(name);
}

int main()
{
    char choice;

    do
    {
        std::string faculty;
        int exams;

        std::cout << "Enter faculty name: ";
        std::getline(std::cin >> std::ws, faculty);

        std::cout << "Enter number of exams in the last session: ";
        std::cin >> exams;

        // Количество экзаменов не может быть отрицательным
        if (exams < 0)
        {
            std::cout << "Error: Invalid number of exams.\n";
        }
        else
        {
            BinaryTree<Student> tree;
            int menu;

            do
            {
                std::cout << "\nMENU (students in tree: " << tree.size() << "):\n";
                std::cout << "1. Add student\n";
                std::cout << "2. Remove student\n";
                std::cout << "3. Print tree\n";
                std::cout << "4. Find student\n";
                std::cout << "5. Test copy of the tree\n";
                std::cout << "6. Test template with int\n";
                std::cout << "0. Exit\n";
                std::cout << "Select operation: ";

                // Защита от ввода не-числа
                if (!(std::cin >> menu))
                {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    menu = -1;
                }

                switch (menu)
                {
                case 1:
                {
                    Student student(faculty, exams);
                    student.input();

                    if (tree.add(student))
                        std::cout << "Student added.\n";
                    else
                        std::cout << "Error: Student with this name already exists.\n";

                    break;
                }

                case 2:
                {
                    Student key(faculty, exams);
                    read_key(key);

                    if (tree.remove(key))
                        std::cout << "Student removed.\n";
                    else
                        std::cout << "Error: Student not found.\n";

                    break;
                }

                case 3:
                    tree.print();
                    break;

                case 4:
                {
                    Student key(faculty, exams);
                    read_key(key);

                    const Student* found = tree.find(key);
                    if (found)
                    {
                        std::cout << "Student found:\n";
                        found->print();
                    }
                    else
                        std::cout << "Error: Student not found.\n";

                    break;
                }

                case 5:
                {
                    // Проверка конструктора копирования
                    BinaryTree<Student> copy(tree);

                    std::cout << "Copy of the tree (" << copy.size() << " students):\n";
                    copy.print();
                    break;
                }

                case 6:
                    demo_int();
                    break;

                case 0:
                    std::cout << "Exiting menu...\n";
                    break;

                default:
                    std::cout << "Invalid choice. Try again.\n";
                }

            } while (menu != 0);
        }

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
```

Разбор:
- `demo_int`: показывает, что тот же шаблон работает с `int`: добавляет 7 чисел, удаляет 30, ищет 40 и 99.
- `read_key`: поиск и удаление принимают объект `T`. Поэтому для ключа создаём временного `Student` и задаём только Ф.И.О. (`set_full_name`): остальное не важно, т. к. сравнение идёт по имени.
- Внешний `do-while` — зацикливание программы; внутренний — меню.
- Защита от не-числа в меню: `cin.clear()` + `cin.ignore(1000, '\n')`, затем `menu = -1` → `default`.
- В `case`-ах с объявлением переменных фигурные скобки обязательны (иначе «jump to case label crosses initialization»).
- `case 4`: `found->print()` вызывается через `const Student*`, поэтому `print` должен быть `const`.
- `case 5`: `BinaryTree<Student> copy(tree)` — конструктор копирования дерева; вывод копии доказывает, что копия полная.
- Дерево — локальный объект блока `else`: при выходе из блока деструктор автоматически освободит все узлы.

---

## 8. Трассировки на примерах

### 8.1 Вставка

Вставляем Petrov, Ivanov, Sidorov, Antonov.

1. `add(Petrov)`: `root == nullptr` → создаём узел → он корень.
2. `add(Ivanov)`: `Ivanov < Petrov`? да → влево от корня, там пусто → узел.
3. `add(Sidorov)`: `Sidorov < Petrov`? нет; `Petrov < Sidorov`? да → вправо, пусто → узел.
4. `add(Antonov)`: меньше Petrov → влево к Ivanov; меньше Ivanov → влево, пусто → узел.
5. `add(Petrov)` ещё раз: ни `<`, ни `>`: `added` остаётся `false`, дерево не меняется.

```
        Petrov
       /      \
   Ivanov    Sidorov
     /
 Antonov
```

Как работают указатели: на каждом уровне рекурсии `node->left = insert_node(node->left, ...)` перезаписывает указатель на потомка (чаще тем же значением), поэтому после возврата дерево связано правильно.

### 8.2 Поиск

`find(Antonov)`: сравнение с Petrov (меньше → влево), с Ivanov (меньше → влево), с Antonov (не меньше и не больше → нашли). 3 сравнения (высота 3).
`find(Nobody)`: «Nobody» < «Petrov»? (`N` < `P`) да → влево; Ivanov < Nobody → вправо у Ivanov, пусто → `nullptr`.

### 8.3 Три случая удаления

**Случай 1. Лист** (удаляем Antonov):
```
   Ivanov            Ivanov
     /       ──▶
 Antonov           (пусто слева)
```
`node->left == nullptr` → `child = node->right` (это `nullptr`), `delete node`, вернуть `nullptr`; родитель записал `nullptr` в `left`.

**Случай 2. Один потомок** (удаляем Ivanov, у которого только левый Antonov):
```
 Petrov               Petrov
   /                    /
Ivanov      ──▶      Antonov
  /
Antonov
```
`node->left != nullptr`, `node->right == nullptr` → `child = node->left`, `delete node`, вернуть `child`; родитель подцепил потомка к себе.

**Случай 3. Два потомка** (удаляем Petrov):
1. Минимум правого поддерева: правый потомок Sidorov, у него нет левого → минимум = Sidorov.
2. Копируем данные Sidorov в корень: корень теперь Sidorov.
3. Рекурсивно удаляем «Sidorov» из правого поддерева (там он лист/узел без левого потомка → простой случай).

```
        Petrov                         Sidorov
       /      \          ──▶          /
   Ivanov    Sidorov               Ivanov
     /                              /
 Antonov                        Antonov
```

Упорядоченность сохраняется: преемник (следующий по величине) больше всего слева и меньше всего справа. Можно симметрично брать максимум левого поддерева.

**Удаление корня** — тот же алгоритм (отдельного случая нет благодаря приёму «вернуть новый корень»): `root = remove_node(root, ...)`.

**Пример на `int`** (удаляем 30 в дереве 50/30,70/20,40,60,80): у 30 два потомка (20 и 40). Минимум правого поддерева: 40 (у него нет левого). Узел 30 получает значение 40, старый узел 40 удалён. В выводе: корень 50, слева 40, у 40 слева 20.

### 8.4 Вывод боком

Для дерева Petrov/Ivanov/Sidorov/Antonov `print_sideways(root, 0)`:

1. `print_sideways(Sidorov, 1)`: (его потомков нет) печатает 4 пробела + Sidorov.
2. печатает 0 пробелов + Petrov.
3. `print_sideways(Ivanov, 1)`: сначала правое (нет), печатает 4 пробела + Ivanov, потом левое: `print_sideways(Antonov, 2)` → 8 пробелов + Antonov.

Итог совпадает с выводом программы: корень слева, правая ветка сверху, глубина = отступ.

### 8.5 Копирование дерева (`BinaryTree<Student> copy(tree)`)

`copy_node(root)`: создаёт узел-копию (вызывается `Student(const Student&)` — глубокая копия оценок), рекурсивно левое и правое поддеревья, связывает их. Копия имеет столько же узлов и **ни одной общей** области памяти с оригиналом. При выходе из блока `case 5` копия уничтожается деструктором дерева, оригинал не затрагивается.

### 8.6 Уничтожение дерева

`~BinaryTree` → `clear_node(root)`: для каждого узла: сначала левое поддерево, затем правое, затем `delete node` (вызывается `~Student`, освобождающий `results`). Порядок post-order гарантирует, что указатели на потомков живы до удаления.

---

## 9. Слабые места и честные ответы

| Слабое место | Объяснение | Как улучшить |
|---|---|---|
| Нет балансировки | Учебная реализация | AVL/красно-чёрное дерево или `std::set` |
| Рекурсия: глубина = высота | Для вырожденного дерева очень большой размер переполнит стек | Итеративные алгоритмы, балансировка |
| Нет итераторов | Обход только внутри `print` | Класс-итератор (in-order со стеком) |
| Указатель из `find` может устареть | Он указывает на данные внутри узла. После `remove` узла с двумя потомками **данные в узле заменяются** данными преемника, а узел-преемник удаляется. После `add`/`remove` указатели лучше не хранить | Возвращать копию или использовать идентификаторы |
| Ключ — только Ф.И.О. | Два разных студента с одинаковым именем считаются дубликатом | Составной ключ (Ф.И.О. + год), либо `std::multiset` |
| Для поиска создаётся полноценный `Student` | Нужен ключ типа `T`; выделяется массив оценок | Шаблонные методы поиска по ключу другого типа (прозрачные компараторы) |
| Конструктор копирования дерева при исключении на середине копирования теряет уже созданные узлы | Деструктор не вызывается, если конструктор не завершился | `try/catch` с очисткой или умные указатели |
| `operator=` дерева в `main` не используется | Из-за ленивого инстанцирования он не проверяется компилятором для `Student` | Добавить тест присваивания |
| Бесконечный цикл меню при конце ввода (EOF) | При закрытом потоке `cin >> menu` всегда не удаётся | Выход при `cin.eof()` |
| Ввод `exams` или `Continue?` не защищён от не-числа | В `main` проверен только пункт меню | Единая функция безопасного ввода |
| Нет конструктора перемещения/присваивания перемещением у дерева | Не требовалось | Правило пяти |
| Шаблон требует `<` и `<<` | Неявные требования | Концепты C++20 (`requires`) |
| Сообщения на английском, исключения (из лабы №3) на русском | Смешение | Один язык |

---

## 10. Правки кода на защите (готовые сниппеты)

Фрагменты 10.1–10.5 проверены сборкой с `-fsanitize=address,undefined` на дереве из 8 элементов (результат для 50, 30, 70, 20, 40, 60, 80, 10: высота 4, листьев 4, минимум 10, максимум 80, прямой обход `50 30 20 10 40 70 60 80`).

В `tree.h` (раздел `private`): `int height_node(const Node* node) const;`, `int leaves_node(const Node* node) const;`, `void print_pre_order(const Node* node) const;`. В `public`: `int height() const; int count_leaves() const; const T* find_min() const; const T* find_max() const; bool find_iterative(const T& value) const; void print_pre_order() const;`. Для `std::max` нужен `#include <algorithm>`.

**10.1 Высота дерева:**

```cpp
// Высота поддерева
template <typename T>
int BinaryTree<T>::height_node(const Node* node) const
{
    if (!node)
        return 0;

    return 1 + std::max(this->height_node(node->left), this->height_node(node->right));
}

// Высота дерева
template <typename T>
int BinaryTree<T>::height() const
{
    return this->height_node(this->root);
}
```

**10.2 Количество листьев:**

```cpp
// Количество листьев в поддереве
template <typename T>
int BinaryTree<T>::leaves_node(const Node* node) const
{
    if (!node)
        return 0;

    if (!node->left && !node->right)
        return 1;

    return this->leaves_node(node->left) + this->leaves_node(node->right);
}

// Количество листьев дерева
template <typename T>
int BinaryTree<T>::count_leaves() const
{
    return this->leaves_node(this->root);
}
```

**10.3 Минимум и максимум (без рекурсии):**

```cpp
// Наименьший элемент (nullptr для пустого дерева)
template <typename T>
const T* BinaryTree<T>::find_min() const
{
    if (!this->root)
        return nullptr;

    const Node* node = this->root;
    while (node->left)
        node = node->left;

    return &node->data;
}

// Наибольший элемент (nullptr для пустого дерева)
template <typename T>
const T* BinaryTree<T>::find_max() const
{
    if (!this->root)
        return nullptr;

    const Node* node = this->root;
    while (node->right)
        node = node->right;

    return &node->data;
}
```

**10.4 Итеративный поиск (без риска переполнения стека):**

```cpp
// Поиск циклом
template <typename T>
bool BinaryTree<T>::find_iterative(const T& value) const
{
    const Node* node = this->root;
    while (node)
    {
        if (value < node->data)
            node = node->left;
        else if (node->data < value)
            node = node->right;
        else
            return true;
    }

    return false;
}
```

**10.5 Прямой обход (pre-order):**

```cpp
// Прямой обход: узел, левое, правое
template <typename T>
void BinaryTree<T>::print_pre_order(const Node* node) const
{
    if (!node)
        return;

    std::cout << node->data << " ";
    this->print_pre_order(node->left);
    this->print_pre_order(node->right);
}

// Вывод прямого обхода
template <typename T>
void BinaryTree<T>::print_pre_order() const
{
    this->print_pre_order(this->root);
    std::cout << "\n";
}
```

Обратный обход (post-order): вывод ставим **после** обоих рекурсивных вызовов. Обход по убыванию: правое, узел, левое.

**10.6 Присваивание дерева (проверка `operator=`):** в `main`:

```cpp
BinaryTree<Student> other;
other = tree;        // инстанцируется operator= для Student
other.print();
```
(10.6 проверено на `BinaryTree<int>`: `c = t; c = c;` — самоприсваивание безопасно, размер 8.)

**10.7 Удалять по номеру в отсортированном списке / вывести число элементов:** число элементов уже есть: `tree.size()`. «К-й по порядку» делается in-order обходом со счётчиком.

**10.8 Сменить ключ сравнения:** изменить `Student::operator<`, например, на год рождения: `return this->birth_year < other.birth_year;`. Тогда дубликатом будет студент с тем же годом. Это показывает, что дерево зависит только от `operator<` типа `T`.

**10.9 Сделать `Node` не вложенным:** вынести struct за пределы класса как шаблон `template <typename T> struct TreeNode`. Менее инкапсулировано; на защите аргумент в пользу вложенного: деталь реализации скрыта.

---

## 11. Вопросы и ответы

### А. Шаблоны

**1. Что такое шаблон класса? Зачем он нужен?**
Параметризованное описание класса, где тип данных передаётся параметром. Позволяет написать контейнер один раз и использовать с любыми типами без дублирования кода и потери типобезопасности.

**2. Что такое инстанцирование?**
Создание компилятором конкретного класса или функции из шаблона при подстановке аргументов (`BinaryTree<Student>`). Для каждого набора аргументов получается отдельный класс.

**3. Почему определения методов шаблона находятся в заголовке (`.tpp`)?**
Компилятору нужен полный код при инстанцировании. Если определения в обычном `.cpp`, для конкретного типа код не будет сгенерирован, линковщик выдаст неразрешённые символы.

**4. Есть ли способ держать определения в `.cpp`?**
Да, явное инстанцирование: в конце `.cpp` `template class BinaryTree<Student>;`. Но тогда шаблон работает только для перечисленных типов (так сделано в лабе про транспорт).

**5. Чем шаблоны отличаются от виртуальных функций?**
Шаблоны: выбор на этапе компиляции, нет накладных расходов, не нужен общий базовый класс. Виртуальные функции: выбор в run-time через vtable, нужна иерархия наследования.

**6. Какие требования `BinaryTree<T>` предъявляет к `T`?**
Конструктор копирования, `operator=`, `operator<`, `operator<<`. Не нужны: конструктор по умолчанию, `operator==`.

**7. Что такое ленивое инстанцирование?**
Из шаблона класса компилятор генерирует только реально используемые методы. Поэтому неиспользуемый метод с ошибкой для данного типа может не обнаружиться.

**8. Чем `typename` отличается от `class` в `template <typename T>`?**
В параметре шаблона ничем.

**9. Зачем `typename` перед `BinaryTree<T>::Node*`?**
`Node` зависит от параметра шаблона, и компилятор без подсказки не знает, тип это или статическое поле. `typename` говорит, что это тип.

**10. Что такое специализация шаблона?**
Особая реализация шаблона для конкретного набора аргументов. Полная (`template <> ...`) и частичная (для классов, `BinaryTree<T*>`).

**11. Что такое нетиповой параметр шаблона?**
Значение (число), известное при компиляции: `template <typename T, int N>`.

**12. Чем `BinaryTree<int>` отличается от `BinaryTree<Student>`?**
Это два разных несвязанных класса, сгенерированных из одного шаблона. Код методов одинаков, но типы данных в узлах, сравнение и вывод разные.

**13. Почему ошибки шаблонов такие длинные?**
Компилятор показывает цепочку инстанцирований. Концепты C++20 делают сообщения короче.

**14. Что такое концепты?**
Именованные ограничения на параметры шаблона (C++20): `requires std::totally_ordered<T>`. Проверяются при подстановке и дают понятные ошибки.

**15. Что такое code bloat?**
Рост размера исполняемого файла из-за отдельных копий кода шаблона для каждого набора аргументов.

**16. Можно ли шаблонную функцию-член сделать виртуальной?**
Нет, виртуальная функция не может быть шаблоном (таблица виртуальных функций должна быть известна заранее). Класс-шаблон с виртуальными функциями допустим.

**17. Где нужно ставить `template <typename T>` при определении метода вне класса?**
Перед каждым методом, имя класса пишется с параметром: `BinaryTree<T>::add`.

**18. Может ли шаблон быть наследником/базой?**
Да, шаблон может наследоваться от обычного класса, обычный класс — от конкретного инстанцирования шаблона, шаблон — от шаблона.

### Б. Бинарное дерево поиска

**19. Что такое бинарное дерево поиска? Какое у него свойство?**
Дерево, где у узла не более двух потомков, левое поддерево содержит меньшие значения, правое большие.

**20. Какая сложность операций?**
O(h), где h — высота. В среднем O(log n), в худшем (вырожденное дерево, например при вставке отсортированных данных) O(n).

**21. Когда дерево вырождается?**
При вставке упорядоченной последовательности: каждый новый узел идёт в одну сторону, дерево превращается в список.

**22. Как решается вырождение?**
Самобалансирующиеся деревья: AVL (повороты при нарушении баланса высот ≤ 1), красно-чёрные (используются в `std::set`/`std::map`).

**23. Как удалить узел с двумя потомками?**
Найти минимум правого поддерева, скопировать его данные в удаляемый узел и удалить минимальный узел (у него не больше одного потомка). Можно симметрично брать максимум левого поддерева.

**24. Почему вывод in-order отсортирован?**
Сначала всё левое (меньшее), потом узел, потом правое (большее), рекурсивно в каждом поддереве.

**25. Какие бывают обходы?**
In-order, pre-order, post-order (глубина), level-order (ширина, очередь).

**26. Как найти минимум и максимум?**
Минимум: идти влево до конца. Максимум: идти вправо до конца.

**27. Чем наш обход «боком» отличается от in-order?**
Это обратный in-order (правое, узел, левое) с отступом по глубине.

**28. Как посчитать высоту дерева?**
`1 + max(высота левого, высота правого)`, у пустого 0 (см. 10.1).

**29. Какое максимально число узлов в дереве высоты h?**
2^h − 1.

**30. Что такое лист? Корень? Внутренний узел?**
Лист: нет потомков. Корень: узел без родителя. Внутренний: есть хотя бы один потомок.

**31. Чем BST отличается от кучи (heap)?**
В куче родитель не меньше (или не больше) обоих потомков, но порядок слева/справа не определён; BST упорядочен «влево меньше, вправо больше».

**32. Что быстрее: поиск в BST или в отсортированном массиве?**
Массив: бинарный поиск O(log n), но вставка/удаление O(n). BST: все операции O(log n) в среднем, вставка/удаление дешёвые.

**33. Почему не `std::set`?**
Лабораторная требует собственный шаблон; `std::set` — готовое решение с балансировкой и итераторами.

### В. Код

**34. Почему рекурсивные функции возвращают `Node*`?**
Чтобы после вставки или удаления родитель мог обновить свой указатель на поддерево (при вставке в пустое место создаётся новый узел, при удалении на место узла встаёт потомок). Это позволяет не писать особый случай для корня.

**35. Зачем `bool& added` / `bool& removed`?**
Рекурсивная функция возвращает указатель, а результат («удалось ли») передаём через ссылочный параметр.

**36. Почему `find` возвращает `const T*`, а не `T` или `bool`?**
Указатель даёт сам найденный элемент без копирования и позволяет отличить «не найден» (`nullptr`). `const` не позволяет изменить ключ и сломать порядок.

**37. Почему `Node` вложен и `private`?**
Деталь реализации. Пользователю достаточно значений `T`; можно менять устройство узла, не затрагивая внешний код.

**38. Что произойдёт при добавлении элемента с уже существующим Ф.И.О.?**
Дерево не изменится, `add` вернёт `false`, программа выведет сообщение об ошибке.

**39. Почему равенство определено через `<`?**
`a` и `b` эквивалентны, если `!(a < b) && !(b < a)`. Это избавляет от требования `operator==`, согласуется со стандартными упорядоченными контейнерами.

**40. Как работает поиск студента по Ф.И.О., если дерево хранит `Student`?**
Создаётся временный `Student` с нужным Ф.И.О. (ключ). Сравнение только по Ф.И.О., остальные поля не важны.

**41. Почему `operator<<` не метод класса?**
Левый операнд — `std::ostream`, а не наш класс. Метод вызывается у объекта слева от оператора, поэтому такую перегрузку делают свободной функцией (или `friend`).

**42. Почему `operator<<` возвращает `std::ostream&`?**
Чтобы работали цепочки `std::cout << a << b`.

**43. Что делает `std::cout << node->data` в шаблоне, если `T` — `int`?**
Вызывается встроенный вывод. Для `Student` — наш `operator<<`. Выбор происходит при инстанцировании.

**44. Почему в деструкторе обход post-order?**
Нельзя удалять узел до потомков, иначе потеряем указатели и получим утечку.

**45. Что произойдёт без деструктора у дерева?**
Утечка памяти: все узлы, созданные через `new`, останутся не освобождены (и динамические массивы оценок внутри `Student`).

**46. Что такое глубокая копия и где она у вас?**
Создание для копии собственных узлов и собственных данных. У нас: `copy_node` для дерева и конструктор копирования `Student` для массива оценок.

**47. Зачем `operator=` у дерева?**
Без него присваивание копировало бы указатель на корень, два дерева делили бы узлы и удаляли дважды. Наш `operator=` копирует глубоко.

**48. Зачем в `operator=` сначала `copy_node`, а потом `clear_node`?**
Безопасность относительно исключений: если копирование бросит исключение, старое дерево ещё цело.

**49. Зачем `this != &other` в `operator=`?**
Защита от `a = a`. Здесь без проверки при самоприсваивании вышла бы лишняя работа; при неправильном порядке (сначала очистка) — потеря данных.

**50. Почему в `remove_node` после `node->data = min_node->data` вызывается удаление по `node->data`, а не по `min_node->data`?**
`min_node` будет удалён внутри рекурсивного вызова; передавать ссылку на его данные опасно. `node->data` уже содержит то же значение и живёт до конца вызова.

**51. Что будет, если удалить из пустого дерева?**
`remove_node(nullptr, ...)` → `nullptr`, `removed` остаётся `false`, `remove` возвращает `false`, счётчик не меняется.

**52. Для чего поле `count`?**
`size()` за O(1), без обхода. Должно обновляться только при реальном добавлении/удалении.

**53. Как узнать, что элемент добавлен, а не отброшен как дубликат?**
`add` возвращает `bool`.

**54. Зачем `is_empty()`, если можно `size() == 0`?**
Читаемость и независимость от `count`. В `main` не используется.

**55. Чем отличается `print_in_order` от `print_sideways`?**
Первый показывает отсортированный список, второй — форму дерева.

**56. Почему в `case` в `main` есть фигурные скобки?**
Объявление переменных внутри `case` без отдельной области видимости приводит к ошибке «переход через инициализацию».

**57. Что делает `std::cin.clear()` и `std::cin.ignore(1000, '\n')`?**
`clear` сбрасывает флаги ошибки потока; `ignore` выбрасывает до 1000 символов или до символа новой строки, то есть остаток некорректного ввода.

**58. Почему деструктор освобождает память автоматически в `main`?**
Дерево — локальный объект блока; при выходе из блока вызывается его деструктор.

**59. Как избавиться от создания временного `Student` для поиска?**
Добавить шаблонный метод поиска по ключу другого типа (с компаратором), либо хранить в дереве пары «ключ-значение» (как `std::map`).

**60. Как сделать так, чтобы дерево хранило указатели на `Student`?**
`BinaryTree<Student*>` не подойдёт (сравнение указателей — по адресам). Нужен компаратор, разыменовывающий указатели, или умные указатели с компаратором.

### Г. Общие вопросы курса (на всякий случай)

**61. Зачем разделять `.h` и `.cpp`?**
Заголовок — интерфейс, `.cpp` — реализация; ускоряет компиляцию и скрывает детали. Для шаблонов определения приходится держать в заголовке.

**62. Что такое `#pragma once`?**
Защита от повторного включения заголовка.

**63. Что такое RAII?**
Захват ресурса в конструкторе, освобождение в деструкторе. Дерево освобождает узлы в деструкторе.

**64. Чем `nullptr` лучше `NULL`?**
Типобезопасный нулевой указатель C++11.

**65. Что такое правило трёх?**
Если нужен один из деструктора, конструктора копирования, оператора присваивания, то нужны все три. У дерева и у `Student` реализованы все три.

**66. Какие проблемы у рекурсивной реализации?**
Глубина = высота дерева, при вырожденном дереве возможно переполнение стека. Решение: итеративная версия или балансировка.

**67. Как проверить, что в программе нет утечек?**
Сборка с `-fsanitize=address,undefined -g`; после запуска при утечке будет отчёт. Либо Valgrind.

**68. Что будет, если у `Student` убрать `operator<`?**
Ошибка компиляции при инстанцировании `BinaryTree<Student>` (в `insert_node`: `value < node->data`).

**69. Можно ли использовать `BinaryTree<Fakultet>`?**
Только если у `Fakultet` есть `<`, `<<` и копирование; тогда можно, но срезка не даст хранить `Student`. Для полиморфных объектов хранят указатели.

**70. Что такое срезка и при чём она здесь?**
Копирование производного объекта в базовый по значению отрезает часть потомка. Дерево хранит `T` по значению, значит `BinaryTree<Fakultet>` отрежет данные `Student` при добавлении.

**71. Как бы вы расширили дерево, чтобы поддерживать несколько ключей (по имени и по среднему баллу)?**
Параметр шаблона-компаратор: `template <typename T, typename Compare = std::less<T>>`; для других ключей — другой компаратор. Либо несколько деревьев.

**72. Что такое прозрачный компаратор?**
Компаратор, позволяющий искать по ключу другого типа без создания полного объекта (`std::less<>` в C++14).

**73. Почему у шаблона нет `.cpp`, а у `Student` и `Fakultet` есть?**
Обычные классы компилируются отдельно, их определения могут жить в `.cpp`. Определения шаблона должны быть видны при инстанцировании, поэтому они в `tree.tpp`, подключаемом из `tree.h`.

---

## 12. Шпаргалка

- `template <typename T> class BinaryTree` — чертёж; `BinaryTree<Student>` — настоящий класс (инстанцирование).
- Код шаблона должен быть виден в месте использования: `tree.h` подключает `tree.tpp`.
- Методы шаблона инстанцируются лениво (только используемые).
- Тип `T` должен иметь: копирование, `operator=`, `operator<`, `operator<<`.
- Равенство через `<`: `!(a < b) && !(b < a)`.
- BST: левое меньше, правое больше. Поиск/вставка/удаление: O(h) (O(log n) в среднем, O(n) в худшем).
- Удаление: лист или один потомок → заменить потомком; два потомка → перенести минимум правого поддерева и удалить его узел.
- Вывод in-order отсортирован. «Боком» — обратный in-order с отступами.
- Рекурсия возвращает `Node*` (новый корень поддерева); результат действия — через `bool&`.
- Узлы через `new` → деструктор (post-order) + глубокий конструктор копирования (pre-order) + `operator=` (сначала копия, потом очистка).
- `find` возвращает `const T*`: не копируем и не даём сломать порядок.
- Меню в цикле, внешний цикл `Continue? (y/n)`.
- Стиль как в лабе №3: `snake_case`, `this->`, комментарии над функциями, без скобок у однострочных `if`.
- Один класс — один заголовок + один `.cpp`; шаблон — `tree.h` + `tree.tpp`.
- Сборка: `g++ -std=c++20 -Wall -Wextra main.cpp fakultet.cpp student.cpp`; проверка памяти: `-fsanitize=address,undefined`.

---

## 13. Глоссарий

| Термин | Значение |
|---|---|
| Шаблон | Параметризованное описание класса/функции |
| Инстанцирование | Генерация конкретного класса из шаблона |
| Специализация | Особая реализация шаблона для конкретных аргументов |
| Зависимое имя | Имя, зависящее от параметра шаблона (нужен `typename`) |
| Концепт | Именованное ограничение на параметры шаблона (C++20) |
| BST | Бинарное дерево поиска |
| Корень / лист | Верхний узел / узел без потомков |
| Высота | Длина самого длинного пути от корня до листа (в узлах) |
| In-order / pre-order / post-order | Симметричный / прямой / обратный обход |
| Преемник | Минимум правого поддерева; следующее по величине значение |
| Вырожденное дерево | Дерево, похожее на список (h = n) |
| Балансировка | Поддержание высоты O(log n) (AVL, красно-чёрные) |
| Строгое слабое упорядочение | Требования к `<`: иррефлексивность, асимметричность, транзитивность |
| Эквивалентность | `!(a < b) && !(b < a)` |
| Глубокая копия | Копия данных в новой памяти |
| RAII | Захват в конструкторе, освобождение в деструкторе |
| Ленивое инстанцирование | Генерация только используемых методов |
