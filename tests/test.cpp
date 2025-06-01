// Directory: test/test.cpp
#include "../include/Vector.hpp"
#include "../include/Matrix.hpp"
#include <iostream>


void testVector() {
    std::cout << "Testing Vector class..." << std::endl;

    // Test constructor and Size()
    Vector v1(5);
    std::cout << "Size of v1: " << v1.Size() << std::endl;

    // Test [] operator and bounds check
    for (int i = 0; i < v1.Size(); ++i) {
        v1[i] = i + 1;
    }

    std::cout << "v1 using []: ";
    v1.Print();

    // Test () operator with one-based indexing
    std::cout << "v1 using () with one-based indexing: ";
    for (int i = 1; i <= v1.Size(); ++i) {
        std::cout << v1(i) << " ";
    }
    std::cout << std::endl;

    // Test copy constructor
    Vector v2 = v1;
    std::cout << "Copy constructed v2 from v1: ";
    v2.Print();

    // Test assignment operator
    Vector v3(5);
    v3 = v1;
    std::cout << "Assigned v3 = v1: ";
    v3.Print();

    // Test unary +
    Vector v4 = +v1;
    std::cout << "Unary +v1: ";
    v4.Print();

    // Test unary -
    Vector v5 = -v1;
    std::cout << "Unary -v1: ";
    v5.Print();

    // Test binary +
    Vector v6 = v1 + v2;
    std::cout << "v1 + v2: ";
    v6.Print();

    // Test binary -
    Vector v7 = v1 - v2;
    std::cout << "v1 - v2: ";
    v7.Print();

    // Test scalar multiplication
    Vector v8 = v1 * 2.0;
    std::cout << "v1 * 2.0: ";
    v8.Print();

    std::cout << "All Vector tests completed successfully." << std::endl;
    
}
void testMatrix() {
    std::cout << "=== Matrix Creation Test ===" << std::endl;
    Matrix A(3, 3);
    A(1, 1) = 1.0;
    A(1, 2) = 2.0;
    A(1, 3) = 3.0;
    A(2, 1) = 4.0;
    A(2, 2) = 5.0;
    A(2, 3) = 6.0;
    A(3, 1) = 7.0;
    A(3, 2) = 8.0;
    A(3, 3) = 9.0;

    std::cout << "Matrix A:" << std::endl;
    A.Print();

    std::cout << "\n=== Copy Constructor Test ===" << std::endl;
    Matrix B = A;  // Calls copy constructor
    std::cout << "Matrix B (copy of A):" << std::endl;
    B.Print();

    std::cout << "\n=== Assignment Operator Test ===" << std::endl;
    Matrix C(2, 2);
    C = A;  // Calls assignment operator
    std::cout << "Matrix C (assigned from A):" << std::endl;
    C.Print();

    std::cout << "\n=== Accessor Test ===" << std::endl;
    std::cout << "A(2,3) = " << A(2, 3) << std::endl;  // Should be 6.0

    std::cout << "\n=== Modify B (should not affect A) ===" << std::endl;
    B(1, 1) = 100.0;
    std::cout << "Matrix B (modified):" << std::endl;
    B.Print();
    std::cout << "Matrix A (should remain unchanged):" << std::endl;
    A.Print();

}
int main() {
    // testVector();
    testMatrix();
    // g++ test/test.cpp src/Matrix.cpp src/Vector.cpp -Iinclude -o test
    return 0;
    
}

