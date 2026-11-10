#include "fakultet.h"
#include <iostream>

// Канструктар базавага класа.
Fakultet::Fakultet(const std::string& name)
    : faculty_name(name)
{
}

// Віртуальны дэструктар базавага класа.
Fakultet::~Fakultet()
{
}

// Атрыманне назвы факультэта.
const std::string& Fakultet::get_faculty_name() const
{
    return this->faculty_name;
}

// Змяненне назвы факультэта.
void Fakultet::set_faculty_name(const std::string& name)
{
    this->faculty_name = name;
}

// Вывад дадзеных факультэта.
void Fakultet::print() const
{
    std::cout << "Faculty: " << this->faculty_name << "\n";
}
