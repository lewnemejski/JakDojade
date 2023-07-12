#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"
#include <iostream>

using namespace std;

template<typename T>
Vector<T>::Vector() {
    vector = nullptr;
}

template<typename T>
Vector<T>::Vector(int c) {
    if (c <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    capacity = c;
    vector = new T[capacity];
    if (!vector) {
        throw std::bad_alloc();
    }
}

template<typename T>
Vector<T>::Vector(int c, T value) {
    if (c <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    capacity = c;
    vector = new T[capacity];
    for (int i = 0; i < c; i++)
        vector[i] = value;
    if (!vector) {
        throw std::bad_alloc();
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
    numberOfElements = other.numberOfElements;
    capacity = other.capacity;
    vector = new T[capacity];
    for (int i = 0; i < numberOfElements; i++) {
        vector[i] = other.vector[i];
    }
}

template<typename T>
Vector<T>::~Vector() {
    delete[] vector;
}

template<typename T>
size_t Vector<T>::size() const {
    return numberOfElements;
}

template<typename T>
size_t Vector<T>::Capacity() const {
    return capacity;
}

template<typename T>
bool Vector<T>::empty() const {
    return numberOfElements == 0;
}

template<typename T>
void Vector<T>::push_back(T data) {
    if (numberOfElements < capacity)
        vector[numberOfElements++] = data;
    else {
        size_t new_capacity = (capacity == 0 ? 1 : capacity * 2);
        T* newVector = new T[new_capacity];
        if (vector != nullptr) {
            for (int i = 0; i < numberOfElements; i++)
            {
                newVector[i] = vector[i];
            }
            delete[] vector;
        }
        vector = newVector;
        capacity = new_capacity;
        vector[numberOfElements++] = data;
    }
}

template<typename T>
void Vector<T>::clear() {
    delete[] vector;
    vector = nullptr;
    numberOfElements = 0;
}

template<typename T>
void Vector<T>::initializeSecondDim() {
    for (int i = 0; i < capacity; i++) {
        vector[i] = T();
    }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this != &other) {
        delete[] vector;
        numberOfElements = other.numberOfElements;
        capacity = other.capacity;
        vector = new T[capacity];
        for (int i = 0; i < capacity; i++)
        {
            vector[i] = other[i];
        }
    }
    return *this;
}

template<typename T>
T& Vector<T>::operator[](int index) const {
    return vector[index];
}

#endif // VECTOR_CPP