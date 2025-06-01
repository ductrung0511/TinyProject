// Directory: src/LinearSystem.cpp
#include "LinearSystem.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

// Constructor
LinearSystem::LinearSystem(const Matrix& A, const Vector& b)
    : mSize(b.Size()), mpA(new Matrix(A)), mpb(new Vector(b)) {
    assert(A.NumRows() == A.NumCols());
    assert(A.NumRows() == b.Size());
}

// Solve using Gaussian Elimination with Partial Pivoting
Vector LinearSystem::Solve() const {
    // Create local copy of A and b
    Matrix A = *mpA;
    Vector b = *mpb;
    Vector x(mSize);

    // Gaussian elimination with partial pivoting
    for (int k = 1; k <= mSize; ++k) {
        // Find the pivot row
        int pivotRow = k;
        double maxVal = std::abs(A(k, k));
        for (int i = k + 1; i <= mSize; ++i) {
            if (std::abs(A(i, k)) > maxVal) {
                maxVal = std::abs(A(i, k));
                pivotRow = i;
            }
        }

        assert(maxVal != 0.0); // singular matrix check

        // Swap rows if needed
        if (pivotRow != k) {
            for (int j = 1; j <= mSize; ++j) std::swap(A(k, j), A(pivotRow, j));
            std::swap(b[k - 1], b[pivotRow - 1]);
        }

        // Elimination step
        for (int i = k + 1; i <= mSize; ++i) {
            double factor = A(i, k) / A(k, k);
            for (int j = k; j <= mSize; ++j) A(i, j) -= factor * A(k, j);
            b[i - 1] -= factor * b[k - 1];
        }
    }

    // Back substitution
    for (int i = mSize; i >= 1; --i) {
        double sum = b[i - 1];
        for (int j = i + 1; j <= mSize; ++j) sum -= A(i, j) * x[j - 1];
        x[i - 1] = sum / A(i, i);
    }
    return x; // return the solution vector
}
LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

// --- PosSymLinSystem ---

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    // Check symmetry
    for (int i = 1; i <= mSize; ++i) {
        for (int j = i + 1; j <= mSize; ++j) {
            assert(std::abs((*mpA)(i, j) - (*mpA)(j, i)) < 1e-12); // difference is nearly zero — due to potential floating point error.
        }
    }
}

// Solve using Conjugate Gradient Method
Vector PosSymLinSystem::Solve() const {
    Vector x(mSize);  // initial guess is zero vector
    Vector r = *mpb;  // initial residual r = b - A*x (x = 0)
    Vector p = r;
    Vector Ap(mSize);
    double rsold = r.Dot(r);

    for (int iter = 0; iter < mSize; ++iter) {
        // Compute Ap = A*p
        for (int i = 1; i <= mSize; ++i) {
            double sum = 0.0;
            for (int j = 1; j <= mSize; ++j) {
                sum += (*mpA)(i, j) * p[j - 1];
            }
            Ap[i - 1] = sum;
        }

        double alpha = rsold / p.Dot(Ap);
        x = x + p * alpha;
        r = r - Ap * alpha;

        double rsnew = r.Dot(r);
        if (std::sqrt(rsnew) < 1e-10) break;

        p = r + p * (rsnew / rsold);
        rsold = rsnew;
    }
    return x;
}
