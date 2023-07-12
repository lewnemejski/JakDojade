#pragma once

#ifndef QUEUE_H
#define QUEUE_H

template<typename T>
class Queue {
public:
    Queue();
    Queue(int c);
    ~Queue();

    size_t size() const;

    bool empty() const;

    void push(T data);

    T pop();

    T Front() const;

    void clear();

    T& operator[](int index) const;

private:
    unsigned int front = 0, rear = 0;
    size_t capacity = 0;
    T* queue;
};

#include "Queue.cpp"
#endif // QUEUE_H