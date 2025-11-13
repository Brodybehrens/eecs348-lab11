#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
private:
    int n;        //size 
    int* data;    //pointer to n*n ints stored in row-major order

public:
    //Default constructor: empty matrix
    Matrix();

    //Constructor for an n x n matrix (allocates memory)
    Matrix(int size);

    //Copy constructor (needed because we allocate memory)
    Matrix(const Matrix& other);

    //Assignment operator (deep copy)
    Matrix& operator=(const Matrix& other);

    //Destructor: free memory
    ~Matrix();

    //Get matrix size
    int getSize() const;

    //Element access
    int& at(int row, int col);

    //Element access 
    int at(int row, int col) const;

    //Print matrix with aligned columns
    void print(std::ostream& out = std::cout) const;

    //Operator overloading for addition
    Matrix operator+(const Matrix& other) const;

    //Operator overloading for multiplication
    Matrix operator*(const Matrix& other) const;

    //Diagonal sums
    int mainDiagonalSum() const;
    int secondaryDiagonalSum() const;
    int totalDiagonalSum() const; //main + secondary
};

//Free functions for row/column swapping and updating

Matrix swapRows(Matrix m, int i = 0, int j = 1);
Matrix swapCols(Matrix m, int i = 0, int j = 1);
Matrix updateCell(Matrix m, int row = 0, int col = 0, int newValue = 100);

#endif //MATRIX_H
