#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{
private:
    int rows;
    int cols;
    std::vector<std::vector<int>> data;                                     // Двухмерны вектар для захавання дадзеных.

public:
    Matrix(int r, int c);

    Matrix operator+(const Matrix& other) const;                            // Перагрузка складання матрыц.
    Matrix operator*(const Matrix& other) const;                            // Перагрузка множання матрыц.
    
    int& operator()(int r, int c);                                          // Доступ да элемента па індэксах (радок, слупок).
    int operator()(int r, int c) const;                                     // Канстантны доступ для чытання элемента.

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);     // Вывад матрыцы ў струмень.
    friend std::istream& operator>>(std::istream& is, Matrix& m);           // Увод матрыцы са струменя.
};

#endif