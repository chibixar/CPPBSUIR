#include "matrix.h"
#include <iostream>

Matrix::Matrix(int r, int c)
{
    rows = r;
    cols = c;
    data = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            data[i][j] = 0;
    }
}

// Copy constructor: builds a NEW independent block of memory (deep copy).
Matrix::Matrix(const Matrix& other)
{
    rows = other.rows;
    cols = other.cols;
    data = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            data[i][j] = other.data[i][j];
    }
}

// Copy assignment: a = b; (a already owns memory, so free it first).
Matrix& Matrix::operator=(const Matrix& other)
{
    if (this == &other)                           // protect against a = a
        return *this;

    for (int i = 0; i < rows; i++)                // free old memory
        delete[] data[i];
    delete[] data;

    rows = other.rows;                            // allocate new memory and copy
    cols = other.cols;
    data = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
            data[i][j] = other.data[i][j];
    }
    return *this;
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
}

void Matrix::input()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            std::cin >> data[i][j];
}

void Matrix::print() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << " ";
        std::cout << "\n";
    }
}

Matrix Matrix::multiply(const Matrix other) const
{
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++)
        {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; k++)
                result.data[i][j] += data[i][k] * other.data[k][j];
        }
    return result;
}
