#ifndef LINEARSYSTEMREGULARIZED_HPP
#define LINEARSYSTEMREGULARIZED_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <stdexcept>

class LinearSystemRegularized {
private:
    Matrix mA;
    Vector mb;
    double mLambda;  // regularization parameter

public:
    LinearSystemRegularized(const Matrix& A, const Vector& b, double lambda = 0.0);

    Vector Solve() const;  // Solve with Moore-Penrose or Tikhonov regularization
};

#endif // LINEARSYSTEMREGULARIZED_HPP
