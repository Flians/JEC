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

#include "libstring.h"

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
    _CONSTANT,
    IN,
    OUT,
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
    _MODULE
};

enum Value
{
    L,
    H,
    X
};

extern size_t init_id;
extern std::unordered_map<string, Gtype> Value_Str;
extern std::unordered_map<Gtype, string, EnumClassHash> Str_Value;
extern std::unordered_map<Value, string, EnumClassHash> Const_Str;

struct Node
{
    // the name of the gate
    string name;
    // the type of the gate
    Gtype cell;
    Value val;
    size_t id;
    // record the number of times the node is visited
    size_t vis;
    vector<Node *> *ins;
    vector<Node *> *outs;

    // constructor
    Node() : val(X), id(init_id++), vis(0), ins(nullptr), outs(nullptr) {}
    Node(string _name, Gtype _cell = WIRE, Value _val = L, int _id = (init_id++)) : name(_name), cell(_cell), val(_val), id(_id), vis(0), ins(nullptr), outs(nullptr) {}

    // destructor
    // delete this node and all edges connected to this node.
    ~Node()
    {
        cout << "~delete node: " << this->name << endl;
        if (this->ins)
        {
            for (auto &in : (*this->ins))
            {
                if (in && in->outs)
                {
                    vector<Node *>::iterator temp = find(in->outs->begin(), in->outs->end(), this);
                    if (temp != in->outs->end())
                    {
                        // in->outs->erase(temp);
                        *temp = *(in->outs->end() - 1);
                        *(in->outs->end() - 1) = nullptr;
                        in->outs->resize(in->outs->size() - 1);
                    }
                }
            }
            vector<Node *>().swap(*this->ins);
            this->ins = nullptr;
        }
        if (this->outs)
        {
            for (auto &out : (*this->outs))
            {
                if (out && out->ins)
                {
                    vector<Node *>::iterator temp = find(out->ins->begin(), out->ins->end(), this);
                    if (temp != out->ins->end()) {
                        out->ins->erase(temp);
                    }
                }
            }
            vector<Node *>().swap(*this->outs);
            this->outs = nullptr;
        }
    }

    /* operator overload */
    // AND
    Node operator&(const Node &B)
    {
        Node re;
        if (this->val == L || B.val == L)
        {
            re.val = L;
        }
        else
        {
            re.val = max(this->val, B.val);
        }
        // cout << this->val << " AND " << B.val << " = " << re.val << endl;
        return re;
    }

    // OR
    Node operator|(const Node &B)
    {
        Node re;
        if (this->val == H || B.val == H)
        {
            re.val = H;
        }
        else
        {
            re.val = max(this->val, B.val);
        }
        // cout << this->val << " OR " << B.val << " = " << re.val << endl;
        return re;
    }

    // XOR
    Node operator^(const Node &B)
    {
        Node re;
        if (this->val == H && B.val == H)
        {
            re.val = L;
        }
        else
        {
            re.val = max(this->val, B.val);
        }
        // cout << this->val << " XOR " << B.val << " = " << re.val << endl;
        return re;
    }

    // not
    Node operator~()
    {
        Node re;
        switch (this->val)
        {
        case L:
            re.val = H;
            break;
        case H:
            re.val = L;
            break;
        default:
            re.val = X;
        }
        // cout << this->val << " not = " << re.val << endl;
        return re;
    }

    // for find
    bool operator==(const Node &B)
    {
        return this->id == B.id;
    }

    // for find
    bool operator==(const Node *B)
    {
        return this->id == B->id;
    }

    // for sort
    bool operator<(const Node &B)
    {
        if (this->outs)
        {
            if (B.outs)
            {
                return this->outs->size() > B.outs->size();
            }
            return true;
        }
        else
        {
            if (B.outs)
            {
                return false;
            }
            return this->id < B.id;
        }
    }
};

/* Global operator overload */
// and
extern Value operator&(const Value &, const Value &);

// or
extern Value operator|(const Value &, const Value &);

// xor
extern Value operator^(const Value &, const Value &);

// not
extern Value operator~(const Value &);

/* O=D?1'bx:C */
extern Value DC(const Value &C, const Value &D);

/* O=S?I1:I0 */
extern Value HMUX(const Value &S, const Value &I0, const Value &I1);

// exor
extern Value EXOR(const Value &, const Value &);

extern Value calculate(Node *g);

extern void unique_element_in_vector(vector<Node *> &v);

extern void cleanVP(vector<Node *> vp);

extern void error_fout(const string &message);

#endif