#ifndef MATRIX_H
#define MATRIX_H

class Matrix
{
private:
    int rows;
    int cols;
    int** data;                                   // dynamic 2D array

public:
    Matrix(int r, int c);                         // constructor
    Matrix(const Matrix& other);                  // copy constructor  (needs &)
    Matrix& operator=(const Matrix& other);       // copy assignment   (needs &)
    ~Matrix();                                    // destructor

    void input();
    void print() const;
    Matrix multiply(const Matrix other) const;    // by value, as you wanted
};

#endif
