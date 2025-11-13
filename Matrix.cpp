#include "Matrix.h"
#include <iomanip>   
#include <stdexcept> 

//Default constructor: empty matrix
Matrix::Matrix() : n(0), data(nullptr) {}

//Constructor that creates an n x n matrix and sets all values to 0
Matrix::Matrix(int size) : n(size), data(nullptr) {
    if (n > 0) {
        data = new int[n * n];
        for (int i = 0; i < n * n; ++i) {
            data[i] = 0;
        }
    }
}

//Copy constructor (deep copy)
Matrix::Matrix(const Matrix& other) : n(other.n), data(nullptr) {
    if (n > 0) {
        data = new int[n * n];
        for (int i = 0; i < n * n; ++i) {
            data[i] = other.data[i];
        }
    }
}

//Assignment operator 
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this; //self-assignment, do nothing
    }

    //Free old memory
    delete[] data;

    n = other.n;
    data = nullptr;

    if (n > 0) {
        data = new int[n * n];
        for (int i = 0; i < n * n; ++i) {
            data[i] = other.data[i];
        }
    }

    return *this;
}

//Destructor
Matrix::~Matrix() {
    delete[] data;
}

//Size accessor
int Matrix::getSize() const {
    return n;
}

//Helper: 1D index from (row, col)
static int index2D(int n, int row, int col) {
    return row * n + col;
}

//Mutable access
int& Matrix::at(int row, int col) {
    if (row < 0 || row >= n || col < 0 || col >= n) {
        throw std::out_of_range("Matrix::at indices out of range");
    }
    return data[index2D(n, row, col)];
}

//Read-only access
int Matrix::at(int row, int col) const {
    if (row < 0 || row >= n || col < 0 || col >= n) {
        throw std::out_of_range("Matrix::at indices out of range");
    }
    return data[index2D(n, row, col)];
}

//Print with aligned columns
void Matrix::print(std::ostream& out) const {
    
    const int width = 4;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            out << std::setw(width) << at(i, j) << " ";
        }
        out << '\n';
    }
}

//Matrix addition using operator overloading
Matrix Matrix::operator+(const Matrix& other) const {
    if (n != other.n) {
        throw std::runtime_error("Matrix sizes do not match for addition");
    }

    Matrix result(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result.at(i, j) = this->at(i, j) + other.at(i, j);
        }
    }
    return result;
}

//Matrix multiplication using operator overloading
Matrix Matrix::operator*(const Matrix& other) const {
    if (n != other.n) {
        throw std::runtime_error("Matrix sizes do not match for multiplication");
    }

    Matrix result(n);

    //Standard triple-loop matrix multiplication
    for (int i = 0; i < n; ++i) {          // row of this
        for (int j = 0; j < n; ++j) {      // column of other
            int sum = 0;
            for (int k = 0; k < n; ++k) {  // across row/col
                sum += this->at(i, k) * other.at(k, j);
            }
            result.at(i, j) = sum;
        }
    }

    return result;
}

//Sum of main diagonal 
int Matrix::mainDiagonalSum() const {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += at(i, i);
    }
    return sum;
}

//Sum of secondary diagonal
int Matrix::secondaryDiagonalSum() const {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int col = n - 1 - i;
        sum += at(i, col);
    }
    return sum;
}

//Total of both diagonals (if n is odd, center counted twice – you can decide)
int Matrix::totalDiagonalSum() const {
    //If you don't want to double-count the center for odd n,
    //you can adjust here For now, we just add both sums.
    return mainDiagonalSum() + secondaryDiagonalSum();
}



//Swap two rows and return new matrix, Matrix is passed BY VALUE
Matrix swapRows(Matrix m, int i, int j) {
    int n = m.getSize();

    if (i < 0 || i >= n || j < 0 || j >= n) {
        std::cerr << "swapRows: indices out of range, no swap performed.\n";
        return m;
    }

    for (int col = 0; col < n; ++col) {
        int temp = m.at(i, col);
        m.at(i, col) = m.at(j, col);
        m.at(j, col) = temp;
    }

    return m;
}

//Swap two columns and return new matrix, Matrix passed BY VALUE
Matrix swapCols(Matrix m, int i, int j) {
    int n = m.getSize();

    if (i < 0 || i >= n || j < 0 || j >= n) {
        std::cerr << "swapCols: indices out of range, no swap performed.\n";
        return m;
    }

    for (int row = 0; row < n; ++row) {
        int temp = m.at(row, i);
        m.at(row, i) = m.at(row, j);
        m.at(row, j) = temp;
    }

    return m;
}

//Update a cell and return new matrix, Matrix passed BY VALUE
Matrix updateCell(Matrix m, int row, int col, int newValue) {
    int n = m.getSize();

    if (row < 0 || row >= n || col < 0 || col >= n) {
        std::cerr << "updateCell: indices out of range, no update performed.\n";
        return m;
    }

    m.at(row, col) = newValue;
    return m;
}
