#pragma once
#include <chrono>
using namespace std;

template <typename FuncType, class T>
inline double measureTime(FuncType func, T input)
{
    chrono::time_point<chrono::high_resolution_clock> st = chrono::high_resolution_clock::now();
    func(input);
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    return (end - st) / chrono::nanoseconds(1);
}

inline chrono::time_point<chrono::high_resolution_clock> measureStartTime()
{
    chrono::time_point<chrono::high_resolution_clock> st = chrono::high_resolution_clock::now();
    return st;
}
inline chrono::time_point<chrono::high_resolution_clock> measureEndTime()
{
    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    return end;
}
inline double measureCalculateTime(chrono::time_point<chrono::high_resolution_clock> st, chrono::time_point<chrono::high_resolution_clock> end)
{
    return (end - st) / chrono::nanoseconds(1);
}