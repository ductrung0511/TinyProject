// Directory: include/Vector.hpp
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <iostream>

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructor
    Vector(int size);

    // Copy constructor
    Vector(const Vector& other);

    // Destructor
    ~Vector();

    // Assignment operator
    Vector& operator=(const Vector& other);

    // Unary operators
    Vector operator+() const;
    Vector operator-() const;

    // Binary operators
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    // Element access
    double& operator[](int index);       // zero-based with bounds checking
    double operator()(int index) const;  // one-based indexing
    double operator[](int index) const;
    // Size accessor
    int Size() const;

    double Dot(const Vector& other) const;

    // Debug print
    void Print() const;
};

#endif // VECTOR_HPP
