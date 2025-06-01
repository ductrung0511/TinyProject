#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <cassert>
#include "Vector.hpp"

class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;

public:
    // Constructor
    Matrix(int numRows, int numCols);

    // Copy constructor
    Matrix(const Matrix& other);

    // Destructor
    ~Matrix();

    // Accessors
    int NumRows() const;
    int NumCols() const;

    // Element access (1-based indexing)
    double& operator()(int i, int j);
    double operator()(int i, int j) const;

    // Assignment operator
    Matrix& operator=(const Matrix& other);

    // Unary operators
    Matrix operator+() const;
    Matrix operator-() const;

    // Binary operators for matrix addition and subtraction
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    // Scalar multiplication
    Matrix operator*(double scalar) const;

    // Matrix multiplication
    Matrix operator*(const Matrix& other) const;

    // Matrix and Vector multiplication
    Vector operator*(const Vector& vec) const;

    // Methods for determinant, inverse and pseudo-inverse
    double Determinant() const;
    Matrix Inverse() const;
    Matrix PseudoInverse() const;
    Matrix Transpose() const;

    // Print matrix (for debugging)
    void Print() const;
};

#endif // MATRIX_HPP
