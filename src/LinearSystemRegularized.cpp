#include "../include/LinearSystemRegularized.hpp"

LinearSystemRegularized::LinearSystemRegularized(const Matrix& A, const Vector& b, double lambda)
    : mA(A), mb(b), mLambda(lambda) {
    if (A.NumRows() != b.Size()) {
        throw std::invalid_argument("Matrix row count must match vector size");
    }
}

Vector LinearSystemRegularized::Solve() const {
    int m = mA.NumRows();
    int n = mA.NumCols();

    if (m >= n) {
        // Solve: x = (A^T A + λI)^(-1) A^T b
        Matrix At = mA.Transpose();
        Matrix AtA = At * mA;

        // Add λ * I to AtA
        for (int i = 1; i <= n; ++i) {
            AtA(i, i) += mLambda;
        }

        Matrix AtA_inv = AtA.Inverse();  // You need to implement Matrix::Inverse()
        Vector Atb = At * mb;
        return AtA_inv * Atb;
    } else {
        // Solve: x = A^T (A A^T + λI)^(-1) b
        Matrix AAt = mA * mA.Transpose();

        // Add λ * I to AAt
        for (int i = 1; i <= m; ++i) {
            AAt(i, i) += mLambda;
        }

        Matrix AAt_inv = AAt.Inverse();
        Vector temp = AAt_inv * mb;
        return mA.Transpose() * temp;
    }
}
