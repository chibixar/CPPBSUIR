#include "fakultet.h"
#include <iostream>

// Конструктор базового класса
Fakultet::Fakultet(const std::string& name)
    : faculty_name(name)
{
}

// Виртуальный деструктор базового класса
Fakultet::~Fakultet()
{
}

// Получение названия факультета
const std::string& Fakultet::get_faculty_name() const
{
    return this->faculty_name;
}

// Изменение названия факультета
void Fakultet::set_faculty_name(const std::string& name)
{
    this->faculty_name = name;
}

// Вывод данных факультета
void Fakultet::print() const
{
    std::cout << "Faculty: " << this->faculty_name << "\n";
}
