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

// ANDF
inline Value ANDF(const Value &A, const Value &B, const Value &O)
{
    O = A + B | O;
    return O;
}

template <typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts &&... params)
{
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

template <size_t I = 0, typename FuncT, typename Tuple>
inline typename std::enable_if<I == std::tuple_size<Tuple>::value>::type for_each(Tuple &, FuncT)
{
}

template <size_t I = 0, typename FuncT, typename Tuple>
    inline typename std::enable_if < I<std::tuple_size<Tuple>::value>::type for_each(Tuple &t, FuncT f)
{
    f(std::get<I>(t));
    for_each<I + 1, FuncT, Tuple>(t, f);
}

// show error messages and exit
template <typename... Args>
inline void JERROR(const Args &... messages)
{
    std::cerr << "ERROR: ";
    auto a = std::forward_as_tuple(messages...);
    for_each(a, [](auto &item) {
#ifdef WIN
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED);
        std::cerr << item << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
            std::cerr << "\033[31m" << item << " \033[0m";
#endif
    });
    std::cerr << std::endl;
    exit(-1);
}

// show warning messages
template <typename... Args>
inline void JWARN(const Args &... messages)
{
    std::cerr << "WARN: ";
    auto a = std::forward_as_tuple(messages...);
    for_each(a, [](auto &item) {
#ifdef WIN
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
        std::cerr << item << " ";
        SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
            std::cerr << "\033[33m" << item << " \033[0m";
#endif
    });
    std::cerr << std::endl;
}

// show info messages
template <typename... Args>
inline void JINFO(const Args &... messages)
{
    std::cerr << "INFO: ";
    auto a = std::forward_as_tuple(messages...);
    for_each(a, [](auto &item) {
        std::cerr << item << " ";
    });
    std::cerr << std::endl;
}

#endif