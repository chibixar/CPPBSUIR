/*5. Разработать класс Fakultet, порождающим класс Student. Класс
Fakultet включает компоненты данные: наименование факультета, Класс
Student, включает компоненты данные: Ф.И.О. студента, год рождения,
результаты сдачи последней сессии.
*/

#pragma once

#include <string>

class Fakultet
{
private:
    std::string faculty_name;

public:
    Fakultet(const std::string& name);
    virtual ~Fakultet();

    const std::string& get_faculty_name() const;
    void set_faculty_name(const std::string& name);

    virtual void print() const;
};
