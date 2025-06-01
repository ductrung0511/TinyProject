// Directory: src/Vector.cpp
#include "Vector.hpp"
#include <cmath>

Vector::Vector(int size) : mSize(size), mData(new double[size]()) {} // new double[size]()  initializes all values to zero.

Vector::Vector(const Vector& other) : mSize(other.mSize), mData(new double[other.mSize]) {
    for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
}

Vector::~Vector() {
    delete[] mData;
}

int Vector::Size() const { return mSize; }

double Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}
// This is the zero-based indexing non-const version

double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

double Vector::operator()(int index) const {
    assert(index >= 1 && index <= mSize);
    return mData[index - 1];
}

Vector& Vector::operator=(const Vector& other) {
    if (this == &other) return *this;
    if (mSize != other.mSize) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
    }
    for (int i = 0; i < mSize; i++) mData[i] = other.mData[i];
    return *this;
}

Vector Vector::operator+() const {
    return *this;
}

Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result[i] = -mData[i];
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result[i] = mData[i] + other.mData[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result[i] = mData[i] - other.mData[i];
    return result;
}

Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) result[i] = mData[i] * scalar;
    return result;
}

double Vector::Dot(const Vector& other) const {
    assert(mSize == other.mSize);
    double sum = 0.0;
    for (int i = 0; i < mSize; ++i) {
        sum += mData[i] * other.mData[i];
    }
    return sum;
}

void Vector::Print() const {
    for (int i = 0; i < mSize; i++) std::cout << mData[i] << " ";
    std::cout << std::endl;
}
