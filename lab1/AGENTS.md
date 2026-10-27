# AGENTS.md: C++ lab assignments (OOP course)

I will give you a lab PDF (in Russian) and a variant number. Implement **only that variant** in the style below. Reply to me in Russian.

## 0. Before writing code

1. Read the PDF and find the variant by its number. Quote the task text back in one line to confirm it is the right one. Do not guess or use a neighbouring variant.
2. If the task text is ambiguous (for example "class A generating class B"), choose the most natural reading, state it in one line, and build it. Do not ask unless the task cannot be done at all.
3. Implement exactly what the variant asks for, with no extra features.

## 1. File layout (always 3 files)

| File | Contents |
|------|----------|
| `<name>.h` | Class declarations. **The very first thing in the file is the task text** in a `/* ... */` block, copied from the PDF in Russian. Then a blank line, then `#pragma once`. **Never** add `#endif` after `#pragma once`. |
| `<name>.cpp` | All method and function definitions. |
| `main.cpp` | `main()` only, plus small helpers if needed. |

Name `<name>` after the subject (for example `matrix`, `student`, `shapes`).

## 2. Language rules

- **Console interface: English** ("Enter rows and cols...", "Error: ...", "Continue? (y/n): ").
- **Comments: Belarusian**, written only where they are needed and not excessive. Do not comment obvious lines.
- Every comment **starts with a capital letter and ends with a period**.
- Comments are trailing `//` comments, **all aligned in one column** (the `//` starts at column 61), so consecutive comments sit exactly under each other:

```cpp
    data = new int*[rows];                                      // Уласная памяць для копіі, не агульная з other.
    Matrix result(r1, c2);                                      // Памер выніку: r1 x c2.
```

- A standalone comment line above a block is allowed only for section labels, and it also has a capital and a period.

## 3. Code style

- Allman braces (opening brace on its own line), 4-space indent, no tabs.
- A blank line after a closing brace of a nested block, and between logical parts.
- Constructor initializer lists on a new line, starting with a colon:

```cpp
Matrix::Matrix(int r, int c)
    : rows(r), cols(c)
{
```

- `std::` prefix everywhere, **no** `using namespace std;`.
- Methods are camelCase. Typical names: `input()`, `print() const`, getters `getX() const`, setters `setX(...)`.
- Use `const` correctly. Pass objects as `const T&`. Use `override` on overridden virtuals, and a virtual destructor in base classes.
- Prefer `this->` only where it adds clarity.

## 4. Restrictions

- **No `std::vector` and no other STL containers.** Use raw dynamic arrays with `new` / `delete[]`, as in the Matrix example (`int** data`, `int* results`).
- `std::string` is allowed for text fields.
- Any class that owns dynamic memory gets:
  - a parameterized constructor;
  - a **copy constructor with a deep copy**;
  - a destructor that frees everything;
  - `operator=` (rule of three) with a self-assignment check.
- No `void main`, no `strcpy_s`, no `#include <windows.h>`. The code must compile with standard g++.

## 5. `main.cpp` template

```cpp
#include "<name>.h"
#include <iostream>

int main()
{
    char choice;

    do
    {
        // Read input, check it, and print "Error: ..." if it is invalid.
        // Create objects, show the results, and test the copy constructor
        // with something like: Matrix copy(m1);

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
```

- Free everything allocated with `new` before the end of each loop iteration.
- Validate input that could break the program (zero or negative sizes, impossible dimensions) and print an `Error: ...` message.
- For inheritance variants, show base-class data through the derived class, for example `Fakultet::print();` inside `Student::print()`.
- For polymorphism variants, demonstrate calls through base-class pointers.

## 6. Verification before delivery

```bash
g++ -std=c++11 -Wall -fsanitize=address main.cpp <name>.cpp -o /tmp/t
printf '<sample input>' | /tmp/t
```

- It must compile without warnings, and there must be no memory errors or leaks.
- Run at least one realistic sample input and check the output.

## 7. Delivery

- Put the three files in `/mnt/user-data/outputs/` and present them.
- Delete files left from previous variants in that folder.
- Final message in Russian, short: which variant was built, the class structure in 2-4 lines, and any assumptions. No long explanations.
