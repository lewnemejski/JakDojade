#pragma once

#ifndef VECTOR_H
#define VECTOR_H

template<typename T>
class Vector {
public:
    Vector();
    Vector(int c);
    Vector(int c, T value);
    Vector(const Vector<T>& other);
    ~Vector();

    size_t size() const;

    size_t Capacity() const;

    bool empty() const;

    void push_back(T data);

    void clear();

    void initializeSecondDim();

    Vector<T>& operator=(const Vector<T>& other);

    T& operator[](int index) const;

private:
    size_t numberOfElements = 0;
    size_t capacity = 0;
    T* vector;
};
#include "Vector.cpp"
#endif // Vector_H