#ifndef PAIR_CPP
#define PAIR_CPP

#include "Pair.h"

using namespace std;

template <typename S, typename T>
int Pair<S, T>::count = 0;

template <typename S, typename T>
Pair<S, T>::Pair()
{
    first = second = '\0';
    count++;
}

template <typename S, typename T>
Pair<S, T>::Pair(S x, T y)
{
    first = x;  
    second = y;
    count++;
}

template <typename S, typename T>
Pair<S, T>::Pair(const Pair& other)
{
    first = other.first;
    second = other.second;

    count++;
}

template <typename S, typename T>
Pair<S, T>::~Pair()
{
}

template <typename S, typename T>
S Pair<S, T>::getFirst()
{
    return first;
}

template <typename S, typename T>
T Pair<S, T>::getSecond()
{
    return second;
}

template <typename S, typename T>
int Pair<S, T>::getCount() {
    return count;
}

template <typename S, typename T>
void Pair<S, T>::setFirst(S x)
{
    first = x;
}

template <typename S, typename T>
void Pair<S, T>::setSecond(T y)
{
    second = y;
}

template <typename S, typename T>
Pair<S, T>& Pair<S, T>::operator=(const Pair<S, T>& other)
{
    if (this != &other)
    {
        first = other.first;

        second = other.second;
    }
    return *this;
}

template <typename S, typename T>
bool Pair<S, T>::operator<(const Pair<S, T>& other) const {
    return this->first < other.first || this->second < other.second;
}

template <typename S, typename T>
bool Pair<S, T>::operator>(const Pair<S, T>& other) const {
    return this->first > other.first || this->second > other.second;
}

template <typename S, typename T>
bool Pair<S, T>::operator=(const Pair<S, T>& other) const {
    return this->first == other.first && this->second == other.second;
}

#endif // PAIR_CPP