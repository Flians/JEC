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
#include <Windows.h>

#include "_platform.h"

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

// all cell types
enum GType
{
    _CONSTANT = 0,
    _IN,
    _OUT,
    CLK,
    WIRE,
    AND,
    NAND,
    OR,
    NOR,
    XOR,
    XNOR,
    INV,
    BUF,
    DFF,
    SPL,
    SPL3,
    CB,
    CB3,
    _HMUX, // _HMUX \U$1 ( .O(\282 ), .I0(1'b1), .I1(\277 ), .S(\281 ));
    _DC,   // _DC \n6_5[9] ( .O(\108 ), .C(\96 ), .D(\107 ));
    _EXOR,
    _MODULE,
    _UNDEFINED,
    COUNT
};

enum Value
{
    L = 0,
    H = 1,
    X = 2
};

extern size_t init_id;
extern std::unordered_map<string, GType> Str_GType;
extern std::unordered_map<GType, string, EnumClassHash> GType_Str;
extern std::unordered_map<Value, string, EnumClassHash> Const_Str;

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
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED);
    cerr << "ERROR: " << message << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    exit(-1);
}

// show warning message
inline void WARN_Fout(string &&message)
{
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
    cerr << "WARN: " << message << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// show info message
inline void INFO_Fout(string &&message)
{
    cerr << "INFO: " << message << endl;
}

#endif