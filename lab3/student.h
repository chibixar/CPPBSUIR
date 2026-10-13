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
    std::string facultyName;

public:
    Fakultet(const std::string& name);
    virtual ~Fakultet();                                        // Віртуальны дэструктар для базавага класа.

    std::string getFacultyName() const;
    void setFacultyName(const std::string& name);

    virtual void print() const;
};

class Student : public Fakultet
{
private:
    std::string fullName;
    int birthYear;
    int examsCount;
    int* results;                                               // Дынамічны масіў адзнак апошняй сесіі.

public:
    Student(const std::string& faculty, int exams);
    Student(const std::string& faculty, const std::string& name,
            int year, const int* marks, int exams);
    Student(const Student& other);                              // Глыбокая копія.
    ~Student();

    Student& operator=(const Student& other);

    std::string getFullName() const;
    int getBirthYear() const;
    int getExamsCount() const;
    int getMark(int index) const;

    void setFullName(const std::string& name);
    void setBirthYear(int year);
    void setMark(int index, int mark);
    void setResults(const int* marks, int exams);

    double average() const;
    void input();
    void print() const override;
};
