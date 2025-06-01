#include <iostream>
#include <cassert>
#include "../include/Vector.hpp"


void test_constructor_and_indexing() {
    Vector v(3);
    assert(v.Size() == 3);
    for (int i = 0; i < 3; i++) assert(v[i] == 0.0);
    v[0] = 1.1; v[1] = 2.2; v[2] = 3.3;
    assert(v[0] == 1.1);
    assert(v(1) == 1.1);  // 1-based indexing
    assert(v(3) == 3.3);
}

void test_copy_constructor_and_assignment() {
    Vector v1(2);
    v1[0] = 4.5; v1[1] = -1.2;
    Vector v2 = v1;  // Copy constructor
    assert(v2[0] == 4.5 && v2[1] == -1.2);

    Vector v3(2);
    v3 = v1;  // Assignment operator
    assert(v3[0] == 4.5 && v3[1] == -1.2);
}

void test_unary_operators() {
    Vector v(2);
    v[0] = 2; v[1] = -3;
    Vector pos = +v;
    Vector neg = -v;
    assert(pos[0] == 2 && pos[1] == -3);
    assert(neg[0] == -2 && neg[1] == 3);
}

void test_binary_operators() {
    Vector a(2), b(2);
    a[0] = 1; a[1] = 2;
    b[0] = 3; b[1] = 4;

    Vector sum = a + b;
    assert(sum[0] == 4 && sum[1] == 6);

    Vector diff = a - b;
    assert(diff[0] == -2 && diff[1] == -2);

    Vector scaled = a * 2.0;
    assert(scaled[0] == 2 && scaled[1] == 4);
}

void test_dot_product() {
    Vector a(3), b(3);
    a[0] = 1; a[1] = 2; a[2] = 3;
    b[0] = 4; b[1] = 5; b[2] = 6;
    double dot = a.Dot(b);  // 1*4 + 2*5 + 3*6 = 32
    assert(dot == 32);
}

int main() {
    test_constructor_and_indexing();
    test_copy_constructor_and_assignment();
    test_unary_operators();
    test_binary_operators();
    test_dot_product();

    std::cout << "All Vector tests passed successfully.\n";
    return 0;
}
