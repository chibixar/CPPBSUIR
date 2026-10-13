#include "student.h"
#include <iostream>
#include <string>

int main()
{
    char choice;

    do
    {
        std::string faculty;
        int count, exams;

        std::cout << "Enter faculty name: ";
        std::getline(std::cin >> std::ws, faculty);

        std::cout << "Enter number of students: ";
        std::cin >> count;

        std::cout << "Enter number of exams in the last session: ";
        std::cin >> exams;

        if (count <= 0 || exams < 0)                            // Праверка карэктнасці ўведзеных лікаў.
        {
            std::cout << "Error: Invalid number of students or exams.\n";
        }
        else
        {
            Student** students = new Student*[count];           // Масіў указальнікаў на студэнтаў.

            for (int i = 0; i < count; i++)
            {
                std::cout << "\nStudent " << i + 1 << ":\n";

                students[i] = new Student(faculty, exams);
                students[i]->input();
            }

            std::cout << "\nStudents list:\n";

            for (int i = 0; i < count; i++)
            {
                std::cout << "\n";
                students[i]->print();
            }

            Student copy(*students[0]);                         // Праверка канструктара капіявання.

            std::cout << "\nCopy of the first student:\n";
            copy.print();

            for (int i = 0; i < count; i++)
            {
                delete students[i];
            }

            delete[] students;
        }

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
