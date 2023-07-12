#ifndef PRIORITY_QUEUE_CPP
#define PRIORITY_QUEUE_CPP

#include "Priority_Queue.h"
#include <iostream>

using namespace std;

template<typename T>
Priority_Queue<T>::Priority_Queue() {
    queue = nullptr;
}

template<typename T>
Priority_Queue<T>::Priority_Queue(int c) {
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
Priority_Queue<T>::~Priority_Queue() {
    delete[] queue;
}

template<typename T>
size_t Priority_Queue<T>::size() const {
    return rear;
}

template<typename T>
bool Priority_Queue<T>::empty() const {
    return front == rear;
}

template<typename T>
void Priority_Queue<T>::push(T data) {
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
    prioritize(data);
}

template<typename T>
void Priority_Queue<T>::prioritize(T data) {
    for (int i = 0; i < rear; i++) {
        if (queue[i] > data) {
            for (int j = rear - 1; j > i; j--) {
                queue[j] = queue[j - 1];
            }
            queue[i] = data;
            break;
        }
    }
}

template<typename T>
T Priority_Queue<T>::pop() {
    if (empty()) {
        std::cout << "Priority_Queue is empty\n";
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
T Priority_Queue<T>::Front() const {
    return queue[front];
}

template<typename T>
void Priority_Queue<T>::clear() {
    delete[] queue;
    queue = nullptr;
    front = rear = capacity = 0;
}

template<typename T>
T& Priority_Queue<T>::operator[](int index) const {
    return queue[index];
}

#endif // PRIORITY_QUEUE_CPP