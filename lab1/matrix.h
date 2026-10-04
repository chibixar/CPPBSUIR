/*Реализовать следующие методы:
1. конструктор с параметрами
2. деструктор
3. метод ввода данных в массив
4. вывод массива на экран
5. реализовать метод уножение двухмерных массивов
*/

#pragma once

class Matrix
{
private:
    int rows;
    int cols;
    int** data;

public:
    Matrix(int r, int c);
    Matrix(const Matrix& other);                                // Глыбокая копія.
    ~Matrix();

    void input();
    void print() const;
    void multiply(const Matrix& other, Matrix& result) const; // Вяртае спасылку на result.
};

#endif
