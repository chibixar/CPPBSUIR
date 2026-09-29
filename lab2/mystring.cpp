#include "mystring.h"
#include <cstring>
#include <stdexcept>

MyString::MyString() : length(0)
{
    data = new char[1];                                                     // Выдзяленне памяці для нуль-тэрмінатара.
    data[0] = '\0';
}

MyString::MyString(const char* str)
{
    if (str)
    {
        length = std::strlen(str);
        data = new char[length + 1];                                        // +1 для захавання сімвала '\0'.
        std::strcpy(data, str);
    }
    else
    {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
}

MyString::MyString(const MyString& other)
{
    length = other.length;
    data = new char[length + 1];                                            // Глыбокае капіяванне памяці.
    std::strcpy(data, other.data);
}

MyString::~MyString()
{
    delete[] data;                                                          // Прадухіленне ўцечкі памяці.
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)                                                     // Праверка на самапрысвойванне.
    {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        std::strcpy(data, other.data);
    }
    return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
    size_t newLength = length + other.length;
    char* newData = new char[newLength + 1];
    std::strcpy(newData, data);
    std::strcat(newData, other.data);
    
    delete[] data;                                                          // Вызваленне памяці перад прызначэннем новай.
    data = newData;
    length = newLength;
    return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
    MyString result(lhs);
    result += rhs;
    return result;
}

MyString operator+(const char* lhs, const MyString& rhs)
{
    MyString result(lhs);                                                   // Яўнае стварэнне аб'екта, таму што канструктар explicit.
    result += rhs;
    return result;
}

MyString operator+(const MyString& lhs, const char* rhs)
{
    MyString result(lhs);
    MyString temp(rhs);
    result += temp;
    return result;
}

MyString operator-(const MyString& lhs, const MyString& rhs)
{
    const char* found = std::strstr(lhs.data, rhs.data);                    // Пошук пачатку падстарокі.
    if (!found || rhs.length == 0)
    {
        return MyString(lhs);
    }
    
    size_t newLength = lhs.length - rhs.length;
    char* newData = new char[newLength + 1];
    
    size_t prefixLen = found - lhs.data;                                    // Вылічэнне даўжыні радка да знойдзенай падстарокі.
    std::strncpy(newData, lhs.data, prefixLen);
    newData[prefixLen] = '\0';
    std::strcat(newData, found + rhs.length);                               // Злучэнне пачатку з хвастом пасля выдаленай часткі.
    
    MyString result(newData);
    delete[] newData;
    return result;
}

MyString& MyString::operator++()
{
    for (size_t i = 0; i < length; ++i) data[i]++;                          // Зрух ASCII кодаў кожнага сімвала.
    return *this;
}

MyString MyString::operator++(int)
{
    MyString temp(*this);                                                   // Захаванне старога стану для постфікснай аперацыі.
    ++(*this);
    return temp;
}

MyString& MyString::operator--()
{
    for (size_t i = 0; i < length; ++i) data[i]--;
    return *this;
}

MyString MyString::operator--(int)
{
    MyString temp(*this);
    --(*this);
    return temp;
}

char& MyString::operator[](int index)
{
    if (index < 0 || index >= (int)length)
    {
        throw std::out_of_range("Index out of bounds!");
    }
    return data[index];
}

MyString MyString::operator()(int start, int len) const
{
    if (start < 0 || start >= (int)length || len <= 0)
    {
        return MyString();
    }
    
    int actualLen = (start + len > (int)length) ? (length - start) : len;   // Абарона ад выхаду за межы даўжыні радка.
    char* sub = new char[actualLen + 1];
    std::strncpy(sub, data + start, actualLen);
    sub[actualLen] = '\0';
    
    MyString result(sub);
    delete[] sub;
    return result;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.data, rhs.data) < 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.data, rhs.data) > 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.data, rhs.data) <= 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return std::strcmp(lhs.data, rhs.data) >= 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    os << str.data;
    return os;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
    char buffer[MyString::MAX_INPUT + 1];
    is.getline(buffer, MyString::MAX_INPUT);                                // Чытанне радка з абмежаваннем памеру буфера (80).
    str = MyString(buffer);
    return is;
}