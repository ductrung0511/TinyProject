#include "../include/LinearSystem.hpp"
#include "../include/Vector.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

bool AreVectorsClose(const Vector& a, const Vector& b, double tol = 1e-8) {
    if (a.Size() != b.Size()) return false;
    for (int i = 0; i < a.Size(); ++i) {
        if (std::abs(a[i] - b[i]) > tol) return false;
    }
    return true;
}

void TestSimpleSystem() {
    Matrix A(2, 2);
    A(1, 1) = 2; A(1, 2) = 1;
    A(2, 1) = 1; A(2, 2) = 3;
    Vector b(2); b[0] = 4; b[1] = 7;
    Vector expected(2); expected[0] = 1; expected[1] = 2;

    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    assert(AreVectorsClose(x, expected));
    std::cout << "TestSimpleSystem passed.\n";
}

void TestIdentityMatrix() {
    Matrix A(3, 3);
    for (int i = 1; i <= 3; ++i)
        A(i, i) = 1;
    Vector b(3); b[0] = 10; b[1] = -2; b[2] = 5;
    Vector expected = b;

    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    assert(AreVectorsClose(x, expected));
    std::cout << "TestIdentityMatrix passed.\n";
}

void TestLargerSystem() {
    Matrix A(3, 3);
    A(1, 1) = 3; A(1, 2) = 2; A(1, 3) = -1;
    A(2, 1) = 2; A(2, 2) = -2; A(2, 3) = 4;
    A(3, 1) = -1; A(3, 2) = 0.5; A(3, 3) = -1;

    Vector b(3); b[0] = 1; b[1] = -2; b[2] = 0;
    Vector expected(3); expected[0] = 1; expected[1] = -2; expected[2] = -2;

    LinearSystem sys(A, b);
    Vector x = sys.Solve();
    assert(AreVectorsClose(x, expected));
    std::cout << "TestLargerSystem passed.\n";
}

void TestSingularMatrix() {
    Matrix A(2, 2);
    A(1, 1) = 1; A(1, 2) = 2;
    A(2, 1) = 2; A(2, 2) = 4; // row 2 is a multiple of row 1

    Vector b(2); b[0] = 3; b[1] = 6;
    try {
        LinearSystem sys(A, b);
        sys.Solve(); // should assert or fail
        std::cerr << "TestSingularMatrix failed (no exception).\n";
    } catch (...) {
        std::cout << "TestSingularMatrix passed (caught expected error).\n";
    }
}

int main() {
    TestSimpleSystem();
    TestIdentityMatrix();
    TestLargerSystem();
    TestSingularMatrix();
    std::cout << "All tests completed.\n";
    return 0;
}
