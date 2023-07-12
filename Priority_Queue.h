#pragma once

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

template<typename T>
class Priority_Queue {
public:
    Priority_Queue();
    Priority_Queue(int c);
    ~Priority_Queue();

    size_t size() const;

    bool empty() const;

    void push(T data);// override;

    void prioritize(T data);

    T pop();

    T Front() const;

    void clear();

    T& operator[](int index) const;

private:
	unsigned int front = 0, rear = 0;
	size_t capacity = 0;
	T* queue;
};

#include "Priority_Queue.cpp"
#endif // PRIORITY_QUEUE_H