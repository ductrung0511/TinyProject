#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA; // Deep copy of matrix A
    Vector* mpb; // Deep copy of vector b

    // Prevent default construction
    LinearSystem() = delete;

    // Prevent copying
    LinearSystem(const LinearSystem&) = delete;
    LinearSystem& operator=(const LinearSystem&) = delete;

public:
    // Construct system from given matrix and RHS vector
    LinearSystem(const Matrix& A, const Vector& b);

    virtual ~LinearSystem();

    // Solve using Gaussian elimination with pivoting
    virtual Vector Solve() const;
};

class PosSymLinSystem : public LinearSystem {
private:
    // Check if matrix is symmetric

public:
    // Constructor
    PosSymLinSystem(const Matrix& A, const Vector& b);

    // Solve using conjugate gradient method
    Vector Solve() const override;
};

#endif // LINEARSYSTEM_HPP
