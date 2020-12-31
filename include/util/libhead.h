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
enum Gtype
{
    _CONSTANT = 0,
    IN,
    OUT,
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

/* Global operator overload */
// and
Value operator&(const Value &, const Value &);

// or
Value operator|(const Value &, const Value &);

// xor
Value operator^(const Value &, const Value &);

// not
Value operator~(const Value &);

/* O=D?1'bx:C */
Value DC(const Value &C, const Value &D);

/* O=S?I1:I0 */
Value HMUX(const Value &I0, const Value &I1, const Value &S);

// exor
Value EXOR(const Value &, const Value &);

extern size_t init_id;
extern std::unordered_map<string, Gtype> Value_Str;
extern std::unordered_map<Gtype, string, EnumClassHash> Str_Value;
extern std::unordered_map<Value, string, EnumClassHash> Const_Str;

template<typename T>
void cleanVP(vector<T *> &vp);

void error_fout(const string &message);

#endif