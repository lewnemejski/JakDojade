#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.h"
#include <iostream>

using namespace std;

template<typename T>
Queue<T>::Queue() {
    queue = nullptr;
}

template<typename T>
Queue<T>::Queue(int c) {
    if (c <= 0) {
        throw std::invalid_argument("Capacity must be a positive integer.");
    }
    capacity = c;
    queue = new T[capacity];
    if (!queue) {
        throw std::bad_alloc();
    }
}

template<typename T>
Queue<T>::~Queue() {
    delete[] queue;
}

template<typename T>
size_t Queue<T>::size() const {
    return rear;
}

template<typename T>
bool Queue<T>::empty() const {
    return front == rear;
}

template<typename T>
void Queue<T>::push(T data) {
    if (rear < capacity)
        queue[rear++] = data;
    else {
        size_t new_capacity = (capacity == 0 ? 1 : capacity * 2);
        T* newQueue = new T[new_capacity];
        if (queue != nullptr) {
            for (int i = 0; i < capacity; i++)
            {
                newQueue[i] = queue[i];
            }
            delete[] queue;
        }
        queue = newQueue;
        capacity = new_capacity;
        queue[rear++] = data;
    }
}

template<typename T>
T Queue<T>::pop() {
    if (empty()) {
        std::cout << "Queue is empty\n";
        return T();
    }
    T data = queue[0];
    for (int i = 0; i < rear - 1; i++) {
        queue[i] = queue[i + 1];
    }
    rear--;
    if (front == rear)
        clear();
    return data;
}

template<typename T>
T Queue<T>::Front() const {
    return queue[front];
}

template<typename T>
void Queue<T>::clear() {
    delete[] queue;
    queue = nullptr;
    front = rear = capacity = 0;
}

template<typename T>
T& Queue<T>::operator[](int index) const {
    return queue[index];
}

#endif // QUEUE_CPP