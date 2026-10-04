#include "matrix.h"
#include <stdexcept>

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

Matrix Matrix::operator*(const Matrix& other) const
{
    if (cols != other.rows)                                     // Слупкі першай павінны дараўнаваць радкам другой.
    {
        throw std::runtime_error("Matrices cannot be multiplied (dimension mismatch)!");
    }

    Matrix result(rows, other.cols);                            // Памер выніку: rows x other.cols.

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result.data[i][j] = 0;

            for (int k = 0; k < cols; k++)
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    return result;
}

int& Matrix::operator()(int r, int c)                          // m1(0, 0) = 5;
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)               // Абарона ад выхаду за межы матрыцы.
    {
        throw std::out_of_range("Matrix indices out of bounds!");
    }

    return data[r][c];                                          // Вяртанне спасылкі для магчымасці змянення.
}

int Matrix::operator()(int r, int c) const
{
    if (r < 0 || r >= rows || c < 0 || c >= cols)
    {
        throw std::out_of_range("Matrix indices out of bounds!");
    }

    return data[r][c];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            os << m.data[i][j] << " ";
        }

        os << "\n";
    }

    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            is >> m.data[i][j];                                 // Паслядоўны ўвод элементаў.
        }
    }

    return is;
}
