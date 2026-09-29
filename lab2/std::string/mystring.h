#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <string>

class MyString
{
private:
    std::string data;                                                       // Выкарыстанне стандартнага класа радка.
    static const int MAX_INPUT = 80;                                        // Абмежаванне ўводу з клавіятуры (па ТЗ).

public:
    MyString();
    explicit MyString(const char* str);                                     // explicit забараняе няяўнае пераўтварэнне.
    MyString(const MyString& other);                                        // Канструктар капіявання.
    ~MyString();

    MyString& operator=(const MyString& other);

    MyString& operator+=(const MyString& other);
    
    MyString& operator++();                                                 // Прэфіксны інкрэмент.
    MyString operator++(int);                                               // Постфіксны інкрэмент.
    MyString& operator--();
    MyString operator--(int);

    char& operator[](int index);
    MyString operator()(int start, int len) const;                          // Выдзяленне падстарокі.

    friend MyString operator+(const MyString& lhs, const MyString& rhs);
    friend MyString operator+(const char* lhs, const MyString& rhs);        // friend патрэбен для аперацый "const" + obj.
    friend MyString operator+(const MyString& lhs, const char* rhs);

    friend MyString operator-(const MyString& lhs, const MyString& rhs);    // Выдаленне першага ўваходжання падстарокі.

    friend bool operator<(const MyString& lhs, const MyString& rhs);
    friend bool operator>(const MyString& lhs, const MyString& rhs);
    friend bool operator<=(const MyString& lhs, const MyString& rhs);
    friend bool operator>=(const MyString& lhs, const MyString& rhs);

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend std::istream& operator>>(std::istream& is, MyString& str);       // Увод са струменя з абаронай ад перапаўнення.
};

#endif