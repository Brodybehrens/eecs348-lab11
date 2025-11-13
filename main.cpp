#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.h"

int main() {
    std::string filename;

    std::cout << "Enter input file name: ";
    std::cin >> filename;

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "'.\n";
        return 1;
    }

    int n;
    in >> n;

    if (!in || n <= 0) {
        std::cerr << "Error: invalid matrix size in file.\n";
        return 1;
    }

    Matrix A(n);
    Matrix B(n);

    //Read first matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value;
            in >> value;
            if (!in) {
                std::cerr << "Error: not enough values for first matrix.\n";
                return 1;
            }
            A.at(i, j) = value;
        }
    }

    //Read second matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value;
            in >> value;
            if (!in) {
                std::cerr << "Error: not enough values for second matrix.\n";
                return 1;
            }
            B.at(i, j) = value;
        }
    }

    std::cout << "\nMatrix A:\n";
    A.print();

    std::cout << "\nMatrix B:\n";
    B.print();

    //Addition using operator+
    std::cout << "\nA + B:\n";
    Matrix sum = A + B;
    sum.print();

    //Multiplication using operator*
    std::cout << "\nA * B:\n";
    Matrix product = A * B;
    product.print();

    //Diagonal sums for A 
    std::cout << "\nDiagonal sums for Matrix A:\n";
    int mainSum = A.mainDiagonalSum();
    int secondarySum = A.secondaryDiagonalSum();
    int totalSum = A.totalDiagonalSum();

    std::cout << "Main diagonal sum:      " << mainSum << "\n";
    std::cout << "Secondary diagonal sum: " << secondarySum << "\n";
    std::cout << "Total diagonal sum:     " << totalSum << "\n";

    //Row swap example 
    std::cout << "\nMatrix A with rows 0 and 1 swapped:\n";
    Matrix A_rows_swapped = swapRows(A);
    A_rows_swapped.print();

    //Column swap example 
    std::cout << "\nMatrix A with columns 0 and 1 swapped:\n";
    Matrix A_cols_swapped = swapCols(A);
    A_cols_swapped.print();

    
    std::cout << "\nMatrix A with cell (0,0) updated to 100:\n";
    Matrix A_updated = updateCell(A);
    A_updated.print();

    return 0;
}
