#include "student.h"
#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <stdexcept>

// Стварэнне студэнта з нулявымі адзнакамі.
Student::Student(const std::string& faculty, int exams)
    : Fakultet(faculty), full_name(""), birth_year(0), exams_count(0), results(nullptr)
{
    this->set_results(nullptr, exams);
}

// Стварэнне студэнта з усімі дадзенымі.
Student::Student(const std::string& faculty, const std::string& name,
                 int year, const int* marks, int exams)
    : Fakultet(faculty), full_name(name), birth_year(year), exams_count(0), results(nullptr)
{
    this->set_results(marks, exams);
}

// Канструктар капіявання (глыбокая копія).
Student::Student(const Student& other)
    : Fakultet(other), full_name(other.full_name), birth_year(other.birth_year), exams_count(0), results(nullptr)
{
    this->set_results(other.results, other.exams_count);
}

// Вызваленне масіва адзнак.
Student::~Student()
{
    delete[] this->results;
}

// Аператар прысвойвання.
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

// Параўнанне па Ф.І.Б. (ключ дрэва).
bool Student::operator<(const Student& other) const
{
    return this->full_name < other.full_name;
}

// Атрыманне Ф.І.Б.
const std::string& Student::get_full_name() const
{
    return this->full_name;
}

// Атрыманне года нараджэння.
int Student::get_birth_year() const
{
    return this->birth_year;
}

// Атрыманне колькасці экзаменаў.
int Student::get_exams_count() const
{
    return this->exams_count;
}

// Атрыманне адзнакі па індэксе.
int Student::get_mark(int index) const
{
    if (index < 0 || index >= this->exams_count)
        throw std::out_of_range("Няма адзнакі з такім нумарам.");

    return this->results[index];
}

// Змяненне Ф.І.Б.
void Student::set_full_name(const std::string& name)
{
    this->full_name = name;
}

// Змяненне года нараджэння.
void Student::set_birth_year(int year)
{
    this->birth_year = year;
}

// Змяненне адзнакі па індэксе.
void Student::set_mark(int index, int mark)
{
    if (index < 0 || index >= this->exams_count)
        throw std::out_of_range("Няма адзнакі з такім нумарам.");

    this->results[index] = mark;
}

// Замена ўсіх адзнак (marks == nullptr дае нулявыя адзнакі).
void Student::set_results(const int* marks, int exams)
{
    int* new_results = new int[exams]{};
    if (marks)
        std::copy_n(marks, exams, new_results);

    delete[] this->results;
    this->results = new_results;
    this->exams_count = exams;
}

// Вылічэнне сярэдняга бала.
double Student::average() const
{
    if (this->exams_count == 0)
        return 0.0;

    int sum = std::accumulate(this->results, this->results + this->exams_count, 0);

    return static_cast<double>(sum) / this->exams_count;
}

// Увод дадзеных студэнта.
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

// Вывад дадзеных студэнта.
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

// Кароткі вывад студэнта ў адзін радок.
std::ostream& operator<<(std::ostream& stream, const Student& student)
{
    stream << student.get_full_name() << " (" << student.get_birth_year()
           << ", avg " << std::format("{:.2f}", student.average()) << ")";

    return stream;
}
