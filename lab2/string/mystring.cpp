#include "mystring.h"
#include <stdexcept>

MyString::MyString() : data("")
{
}

MyString::MyString(const char* str)
{
    if (str)
    {
        data = str;
    }
    else
    {
        data = "";
    }
}

MyString::MyString(const MyString& other) : data(other.data)                // Выкарыстанне канструктара капіявання std::string.
{
}

MyString::~MyString()
{
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other)                                                     // Праверка на самапрысвойванне.
    {
        data = other.data;                                                  // std::string бярэ на сябе кіраванне памяццю.
    }
    return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
    data += other.data;                                                     // Выкарыстанне стандартнага метаду далучэння.
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
    if (rhs.data.empty())
    {
        return MyString(lhs);
    }
    
    size_t pos = lhs.data.find(rhs.data);                                   // Пошук індэкса пачатку падстарокі.
    if (pos == std::string::npos)
    {
        return MyString(lhs);
    }
    
    std::string temp = lhs.data;
    temp.erase(pos, rhs.data.length());                                     // Выдаленне знойдзенай часткі з радка.
    
    return MyString(temp.c_str());
}

MyString& MyString::operator++()
{
    for (size_t i = 0; i < data.length(); ++i) data[i]++;                   // Зрух ASCII кодаў кожнага сімвала.
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
    for (size_t i = 0; i < data.length(); ++i) data[i]--;
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
    if (index < 0 || index >= (int)data.length())
    {
        throw std::out_of_range("Index out of bounds!");
    }
    return data[index];
}

MyString MyString::operator()(int start, int len) const
{
    if (start < 0 || start >= (int)data.length() || len <= 0)
    {
        return MyString();
    }
    
    int actualLen = (start + len > (int)data.length()) ? (data.length() - start) : len;
    std::string sub = data.substr(start, actualLen);                        // Выкарыстанне бяспечнага метаду substr.
    
    return MyString(sub.c_str());
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
    return lhs.data < rhs.data;                                             // Стандартнае лексікаграфічнае параўнанне.
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    return lhs.data > rhs.data;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
    return lhs.data <= rhs.data;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
    return lhs.data >= rhs.data;
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