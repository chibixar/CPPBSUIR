#include "student.h"
#include <iostream>

Fakultet::Fakultet(const std::string& name)
    : facultyName(name)
{
}

Fakultet::~Fakultet()
{
}

std::string Fakultet::getFacultyName() const
{
    return facultyName;
}

void Fakultet::setFacultyName(const std::string& name)
{
    facultyName = name;
}

void Fakultet::print() const
{
    std::cout << "Faculty: " << facultyName << "\n";
}

Student::Student(const std::string& faculty, int exams)
    : Fakultet(faculty),                                        // Канструктар базавага класа выклікаецца першым.
      fullName(""), birthYear(0), examsCount(exams)
{
    results = new int[examsCount];

    for (int i = 0; i < examsCount; i++)
    {
        results[i] = 0;
    }
}

Student::Student(const std::string& faculty, const std::string& name,
                 int year, const int* marks, int exams)
    : Fakultet(faculty), fullName(name), birthYear(year), examsCount(exams)
{
    results = new int[examsCount];

    for (int i = 0; i < examsCount; i++)
    {
        results[i] = marks[i];
    }
}

Student::Student(const Student& other)
    : Fakultet(other), fullName(other.fullName),                // Копія часткі базавага класа.
      birthYear(other.birthYear), examsCount(other.examsCount)
{
    results = new int[examsCount];                              // Уласная памяць для копіі, не агульная з other.

    for (int i = 0; i < examsCount; i++)
    {
        results[i] = other.results[i];
    }
}

Student::~Student()
{
    delete[] results;
}

Student& Student::operator=(const Student& other)
{
    if (this != &other)                                         // Абарона ад прысвойвання самому сабе.
    {
        Fakultet::operator=(other);

        fullName = other.fullName;
        birthYear = other.birthYear;

        delete[] results;

        examsCount = other.examsCount;
        results = new int[examsCount];

        for (int i = 0; i < examsCount; i++)
        {
            results[i] = other.results[i];
        }
    }

    return *this;
}

std::string Student::getFullName() const
{
    return fullName;
}

int Student::getBirthYear() const
{
    return birthYear;
}

int Student::getExamsCount() const
{
    return examsCount;
}

int Student::getMark(int index) const
{
    if (index < 0 || index >= examsCount)                       // Праверка межаў масіва.
    {
        return 0;
    }

    return results[index];
}

void Student::setFullName(const std::string& name)
{
    fullName = name;
}

void Student::setBirthYear(int year)
{
    birthYear = year;
}

void Student::setMark(int index, int mark)
{
    if (index >= 0 && index < examsCount)
    {
        results[index] = mark;
    }
}

void Student::setResults(const int* marks, int exams)
{
    delete[] results;                                           // Вызваляем стары масіў перад выдзяленнем новага.

    examsCount = exams;
    results = new int[examsCount];

    for (int i = 0; i < examsCount; i++)
    {
        results[i] = marks[i];
    }
}

double Student::average() const
{
    if (examsCount == 0)                                        // Абарона ад дзялення на нуль.
    {
        return 0.0;
    }

    int sum = 0;

    for (int i = 0; i < examsCount; i++)
    {
        sum += results[i];
    }

    return static_cast<double>(sum) / examsCount;
}

void Student::input()
{
    std::cout << "Enter full name: ";
    std::getline(std::cin >> std::ws, fullName);                // std::ws прапускае застаўшыся сімвал новага радка.

    std::cout << "Enter birth year: ";
    std::cin >> birthYear;

    for (int i = 0; i < examsCount; i++)
    {
        std::cout << "Enter mark for exam " << i + 1 << ": ";
        std::cin >> results[i];
    }
}

void Student::print() const
{
    Fakultet::print();                                          // Вывад даных базавага класа.

    std::cout << "Full name: " << fullName << "\n";
    std::cout << "Birth year: " << birthYear << "\n";
    std::cout << "Session results: ";

    for (int i = 0; i < examsCount; i++)
    {
        std::cout << results[i] << " ";
    }

    std::cout << "\nAverage mark: " << average() << "\n";
}
