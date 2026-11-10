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
