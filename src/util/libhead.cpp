#include "libhead.h"

/* initial */
size_t init_id = 0;
std::unordered_map<string, Gtype> Value_Str = {
    {"constant", _CONSTANT},
    {"input", IN},
    {"output", OUT},
    {"wire", WIRE},

    {"jand", AND},
    {"jnand", NAND},
    {"jor", OR},
    {"jnor", NOR},
    {"jxor", XOR},
    {"jxnor", XNOR},
    {"jnot", INV},
    {"jdff", DFF},
    {"jspl", SPL},
    {"jspl3", SPL3},
    {"jcb", CB},
    {"jcb3", CB3},

    {"and", AND},
    {"nand", NAND},
    {"or", OR},
    {"nor", NOR},
    {"xor", XOR},
    {"xnor", XNOR},
    {"not", INV},
    {"buf", BUF},
    {"_HMUX", _HMUX},
    {"_DC", _DC},

    {"_EXOR", _EXOR},
    {"module", _MODULE},
    {"undefined", _UNDEFINED}};

std::unordered_map<Gtype, string, EnumClassHash> Str_Value = {
    {_CONSTANT, "constant"},
    {IN, "input"},
    {OUT, "output"},
    {WIRE, "wire"},
    {AND, "and"},
    {NAND, "nand"},
    {OR, "or"},
    {NOR, "nor"},
    {XOR, "xor"},
    {XNOR, "xnor"},
    {INV, "not"},
    {BUF, "buf"},
    {DFF, "jdff"},
    {SPL, "jspl"},
    {SPL3, "jspl3"},
    {CB, "jcb"},
    {CB3, "jcb3"},
    {_HMUX, "_HMUX"},
    {_DC, "_DC"},
    {_EXOR, "_EXOR"},
    {_MODULE, "module"},
    {_UNDEFINED, "undefined"}};

std::unordered_map<Value, string, EnumClassHash> Const_Str = {
    {L, "1'b0"},
    {H, "1'b1"},
    {X, "1'bx"}};

/* Global operator overload */
 Value operator&(const Value &A, const Value &B)
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

 Value operator|(const Value &A, const Value &B)
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

 Value operator^(const Value &A, const Value &B)
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

 Value operator~(const Value &A)
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

 Value DC(const Value &C, const Value &D)
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

 Value HMUX(const Value &I0, const Value &I1, const Value &S)
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

 Value EXOR(const Value &A, const Value &B)
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

 void error_fout(string &&message)
{
    cerr << "Error: " << message << endl;
    exit(-1);
}