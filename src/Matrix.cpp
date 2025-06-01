// Directory: src/Matrix.cpp
#include "Matrix.hpp"
#include <cassert>
#include <iostream>

Matrix::Matrix(int numRows, int numCols) : mNumRows(numRows), mNumCols(numCols) {
    mData = new double*[mNumRows]; // allocate array of pointers
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols]();  // initialize to zero
    }
}

Matrix Matrix::Transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) { 
    // copy constructor 
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; i++) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;
}

int Matrix::NumRows() const { return mNumRows; } // The function only reads from the object.
int Matrix::NumCols() const { return mNumCols; } // The function only reads from the object.

double& Matrix::operator()(int row, int col) {
    // 1-based indexing check || Allows writing (non-const) 
    // A(1, 2) = 3.14;  
    assert(row >= 1 && row <= mNumRows);
    assert(col >= 1 && col <= mNumCols);
    return mData[row - 1][col - 1];
}

double Matrix::operator()(int row, int col) const {
    // 1-based indexing check || Allows reading (const)
    // double x = A(1, 2);
    assert(row >= 1 && row <= mNumRows);
    assert(col >= 1 && col <= mNumCols);
    return mData[row - 1][col - 1];
}

Matrix& Matrix::operator=(const Matrix& other) {  // returns a reference to the current object
    if (this == &other) return *this;
     // Prevents doing unnecessary work if you're assigning the matrix to itself (`A = A`)

    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
        for (int i = 0; i < mNumRows; i++) { 
            delete[] mData[i];
        }
        delete[] mData;

        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; i++) {
            mData[i] = new double[mNumCols];
        }
    }

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
    return *this; // Returns the current object by reference
}

void Matrix::Print() const {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            std::cout << mData[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= other.mNumCols; ++j) {
            double sum = 0.0;
            for (int k = 1; k <= mNumCols; ++k) {
                sum += (*this)(i, k) * other(k, j); // (*this) dereference the pointer turning it to an object
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.Size());
    Vector result(mNumRows);
    for (int i = 1; i <= mNumRows; ++i) {
        double sum = 0.0;
        for (int j = 1; j <= mNumCols; ++j) {
            sum += (*this)(i, j) * vec[j - 1];
        }
        result[i - 1] = sum;
    }
    return result;
}