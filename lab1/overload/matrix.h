/*Реализовать следующие методы:
1. конструктор с параметрами
2. деструктор
3. метод ввода данных в массив (operator>>)
4. вывод массива на экран (operator<<)
5. реализовать метод уножение двухмерных массивов (operator*)
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix
{
private:
    int rows;
    int cols;
    int** data;                                                  // Двухмерны масіў на ўказателях, без vector.

public:
    Matrix(int r, int c);
    Matrix(const Matrix& other);                                 // Глыбокая копія.
    ~Matrix();

    Matrix operator*(const Matrix& other) const;                 // Перагрузка множання матрыц.
    int& operator()(int r, int c);                               // Доступ да элемента па індэксах (радок, слупок).
    int operator()(int r, int c) const;                          // Канстантны доступ для чытання элемента.

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);  // Вывад матрыцы ў струмень.
    friend std::istream& operator>>(std::istream& is, Matrix& m);       // Увод матрыцы са струменя.
};

#endif
