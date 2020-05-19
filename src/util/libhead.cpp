#include "libhead.h"

/* initial */
unsigned int init_id = 0;
map<string, Gtype> Value_Str = {
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
    
    {"_EXOR", _EXOR}
};

map<Gtype, string> Str_Value = {
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
    {_EXOR, "_EXOR"}
};

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

inline Value HMUX(const Value &S, const Value &I0, const Value &I1)
{
    if (S==H)
    {
        return I0 == I1 ? I0 : X;
    } else
    {
        return S==L?I0:I1;
    }
}

inline Value EXOR(const Value &A, const Value &B) {
    if (A==X || A==B) {
        return L;
    } else
    {
        return H;
    }
}

Value calculate(node *g) {
    node temp_g;
    if (g) {
        temp_g.val =  g->ins->at(0)->val;
        vector<node *>::iterator it_ = g->ins->begin() + 1;
        vector<node *>::iterator it_end = g->ins->end();
        switch (g->cell)
        {
        case AND:
            while (it_ != it_end)
            {
                temp_g = temp_g&*(*(it_++));
            }
            break;
        case NAND:
            while (it_ != it_end)
            {
                temp_g = temp_g&*(*(it_++));
            }
            temp_g = ~temp_g;
            break;
        case OR:
            while (it_ != it_end)
            {
                temp_g = temp_g|*(*(it_++));
            }
            break;
        case NOR:
            while (it_ != it_end)
            {
                temp_g = temp_g|*(*(it_++));
            }
            temp_g = ~temp_g;
            break;
        case XOR:
            while (it_ != it_end)
            {
                temp_g = temp_g^*(*(it_++));
            }
            break;
        case XNOR:
            while (it_ != it_end)
            {
                temp_g = temp_g^*(*(it_++));
            }
            temp_g = ~temp_g;
            break;
        case INV:
            temp_g = ~temp_g;
            break;
        case BUF:
            break;
        case _HMUX:
            temp_g.val = HMUX(temp_g.val, (*it_)->val, (*(it_+1))->val);
            break;
        case _DC:
            temp_g.val = DC(temp_g.val, (*it_)->val);
            break;
        case _EXOR:
            temp_g.val = EXOR(temp_g.val, (*it_)->val);
            break;
        default:
            break;
        }
    } else {
        cout << "The node g is empty in libhead.cpp: Value calculate(node *g)" << endl;
        exit(-1);
    }
    return temp_g.val;
}