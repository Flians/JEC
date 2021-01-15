#ifndef _LIBHEAD_H_
#define _LIBHEAD_H_

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "_platform.h"

#ifdef WIN
#include <Windows.h>
#endif

#define enumtoCharArr(val) #val

using namespace std;

// resolve the error: 'implicit instantiation of undefined template 'std::__1::hash<Gtype>'
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

enum Value
{
    L = 0,
    H = 1,
    X = 2
};

extern size_t init_id;
extern const std::unordered_map<Value, string, EnumClassHash> Const_Str;

template <typename T = double>
class Point
{
public:
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    Point(const Point &obj);
    Point &operator=(const Point &obj);
    Point operator+(const Point &a);
    Point operator-(const Point &a);
    Point &operator+=(const Point &a);
    Point &operator-=(const Point &a);
    bool operator<(const Point &p) const;

    T getX();
    T getY();
    void setX(T _x);
    void setY(T _y);
    void set(T _x, T _y);
    /**
     * @return the distance from point (0,0).
     */
    T distance();

    template <typename Q>
    friend ostream &operator<<(ostream &output, const Point<Q> &p);

protected:
    T x;
    T y;
};

/* Global operator overload */
// and
inline Value operator&(const Value &A, const Value &B)
{
    if (A == L || B == L)
    {
        return L;
    }
    else
    {
        return max(A, B);
    }
}

// or
inline Value operator|(const Value &A, const Value &B)
{
    if (A == H || B == H)
    {
        return H;
    }
    else
    {
        return max(A, B);
    }
}

// xore
inline Value operator^(const Value &A, const Value &B)
{
    if (A == H && B == H)
    {
        return L;
    }
    else
    {
        return max(A, B);
    }
}

// not
inline Value operator~(const Value &A)
{
    switch (A)
    {
    case L:
        return H;
    case H:
        return L;
    default:
        return X;
    }
}

// _DC in ICCAD's 2020 contest
inline Value DC(const Value &C, const Value &D)
{
    if (D == L)
    {
        return C;
    }
    else
    {
        return X;
    }
}

// _HMUX in ICCAD's 2020 contest
inline Value HMUX(const Value &I0, const Value &I1, const Value &S)
{
    if (S == X)
    {
        return I0 == I1 ? I0 : X;
    }
    else
    {
        return S == L ? I0 : I1;
    }
}

// Output
inline Value EXOR(const Value &A, const Value &B)
{
    if (A == X || A == B)
    {
        return L;
    }
    else
    {
        return H;
    }
}

template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts &&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

// show error message and exit
inline void ERROR_Exit_Fout(string &&message)
{
    std::cerr << "ERROR: ";
#ifdef WIN
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED);
    std::cerr << message;
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    std::cerr << "\033[31m" << message << "\033[0m";
#endif
    std::cerr << std::endl;
    exit(-1);
}

// show warning message
inline void WARN_Fout(string &&message)
{
    std::cerr << "WARN: ";
#ifdef WIN
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
    std::cerr << message;
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
    std::cerr << "\033[33m" << message << "\033[0m";
#endif
    std::cerr << std::endl;
}

// show info message
inline void INFO_Fout(string &&message)
{
    cerr << "INFO: " << message << endl;
}

#endif