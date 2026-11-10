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

class Student : public Fakultet
{
private:
    std::string full_name;
    int birth_year;
    int exams_count;
    int* results;

public:
    Student(const std::string& faculty, int exams);
    Student(const std::string& faculty, const std::string& name,
            int year, const int* marks, int exams);
    Student(const Student& other);
    ~Student();

    Student& operator=(const Student& other);

    const std::string& get_full_name() const;
    int get_birth_year() const;
    int get_exams_count() const;
    int get_mark(int index) const;

    void set_full_name(const std::string& name);
    void set_birth_year(int year);
    void set_mark(int index, int mark);
    void set_results(const int* marks, int exams);

    double average() const;
    void input();
    void print() const override;
};
