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

        // Праверка карэктнасці ўведзеных лікаў.
        if (count <= 0 || exams < 0)
        {
            std::cout << "Error: Invalid number of students or exams.\n";
        }
        else
        {
            // Масіў указальнікаў на базавы клас: студэнтаў апрацоўваем паліморфна.
            Fakultet** students = new Fakultet*[count];

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

            // Праверка канструктара капіявання (прывядзенне базавага ўказальніка да Student).
            Student copy(*dynamic_cast<Student*>(students[0]));

            std::cout << "\nCopy of the first student:\n";
            copy.print();

            for (int i = 0; i < count; i++)
                delete students[i];

            delete[] students;
        }

        std::cout << "\nContinue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
