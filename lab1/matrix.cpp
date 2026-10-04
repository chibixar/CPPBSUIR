#include "matrix.h"
#include <iostream>

Matrix::Matrix(int r, int c)
    : rows(r), cols(c)
{
    data = new int*[rows];

    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];

        for (int j = 0; j < cols; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& other)
    : rows(other.rows), cols(other.cols)
{
    data = new int*[rows];                                      // Уласная памяць для копіі, не агульная з other.

    for (int i = 0; i < rows; i++)
    {
        data[i] = new int[cols];

        for (int j = 0; j < cols; j++)
        {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] data[i];
    }

    delete[] data;
}

void Matrix::input()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

void Matrix::print() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << data[i][j] << " ";
        }

        std::cout << "\n";
    }
}


void Matrix::multiply(const Matrix& other, Matrix& result) const  //Вяртае для copy.multiply(m2, result).print();
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result.data[i][j] = 0;

            for (int k = 0; k < this->cols; k++)
            {
                result.data[i][j] += this->data[i][k] * other.data[k][j];
            }
        }
    }

    return result;                                              // Спасылка на параметр, а не на лакальны аб'ект.
}
