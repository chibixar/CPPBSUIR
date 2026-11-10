#pragma once

#include <string>
#include "fakultet.h"

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
