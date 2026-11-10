#include "student.h"
#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <stdexcept>

// Создание студента с нулевыми оценками
Student::Student(const std::string& faculty, int exams)
    : Fakultet(faculty), full_name(""), birth_year(0), exams_count(0), results(nullptr)
{
    this->set_results(nullptr, exams);
}

// Создание студента со всеми данными
Student::Student(const std::string& faculty, const std::string& name,
                 int year, const int* marks, int exams)
    : Fakultet(faculty), full_name(name), birth_year(year), exams_count(0), results(nullptr)
{
    this->set_results(marks, exams);
}

// Конструктор копирования (глубокая копия)
Student::Student(const Student& other)
    : Fakultet(other), full_name(other.full_name), birth_year(other.birth_year), exams_count(0), results(nullptr)
{
    this->set_results(other.results, other.exams_count);
}

// Освобождение массива оценок
Student::~Student()
{
    delete[] this->results;
}

// Оператор присваивания
Student& Student::operator=(const Student& other)
{
    if (this != &other)
    {
        Fakultet::operator=(other);
        this->full_name = other.full_name;
        this->birth_year = other.birth_year;
        this->set_results(other.results, other.exams_count);
    }

    return *this;
}

// Получение Ф.И.О.
const std::string& Student::get_full_name() const
{
    return this->full_name;
}

// Получение года рождения
int Student::get_birth_year() const
{
    return this->birth_year;
}

// Получение количества экзаменов
int Student::get_exams_count() const
{
    return this->exams_count;
}

// Получение оценки по индексу
int Student::get_mark(int index) const
{
    if (index < 0 || index >= this->exams_count)
        throw std::out_of_range("Нет оценки с таким номером.");

    return this->results[index];
}

// Изменение Ф.И.О.
void Student::set_full_name(const std::string& name)
{
    this->full_name = name;
}

// Изменение года рождения
void Student::set_birth_year(int year)
{
    this->birth_year = year;
}

// Изменение оценки по индексу
void Student::set_mark(int index, int mark)
{
    if (index < 0 || index >= this->exams_count)
        throw std::out_of_range("Нет оценки с таким номером.");

    this->results[index] = mark;
}

// Замена всех оценок (marks == nullptr даёт нулевые оценки)
void Student::set_results(const int* marks, int exams)
{
    int* new_results = new int[exams]{};
    if (marks)
        std::copy_n(marks, exams, new_results);

    delete[] this->results;
    this->results = new_results;
    this->exams_count = exams;
}

// Вычисление среднего балла
double Student::average() const
{
    if (this->exams_count == 0)
        return 0.0;

    int sum = std::accumulate(this->results, this->results + this->exams_count, 0);

    return static_cast<double>(sum) / this->exams_count;
}

// Ввод данных студента
void Student::input()
{
    std::cout << "Enter full name: ";
    std::getline(std::cin >> std::ws, this->full_name);

    std::cout << "Enter birth year: ";
    std::cin >> this->birth_year;

    for (int i = 0; i < this->exams_count; i++)
    {
        std::cout << "Enter mark for exam " << i + 1 << ": ";
        std::cin >> this->results[i];
    }
}

// Вывод данных студента
void Student::print() const
{
    Fakultet::print();

    std::cout << "Full name: " << this->full_name << "\n";
    std::cout << "Birth year: " << this->birth_year << "\n";
    std::cout << "Session results: ";

    for (int i = 0; i < this->exams_count; i++)
        std::cout << this->results[i] << " ";

    std::cout << "\nAverage mark: " << std::format("{:.2f}", this->average()) << "\n";
}
