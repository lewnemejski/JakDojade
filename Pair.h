#pragma once
#ifndef PAIR_H
#define PAIR_H
using namespace std;

template <typename S, typename T>
class Pair
{
public:
    Pair();
    Pair(S, T);
    Pair(const Pair& other);
    ~Pair();

    S getFirst();

    T getSecond();

    int getCount();

    void setFirst(S);

    void setSecond(T);

    Pair& operator=(const Pair& other);

    bool operator<(const Pair& other) const;

    bool operator>(const Pair& other) const;

    bool operator=(const Pair& other) const;

private:
    S first;
    T second;
    static int count;
};

#include "Pair.cpp"
#endif // PAIR_H