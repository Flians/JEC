#ifndef _NODE_H_
#define _NODE_H_

#include "util/libhead.h"
#include "util/libstring.h"

// all cell types
enum GType
{
    _CONSTANT = 0,
    _CLK,
    _PI,
    _EXOR, // connected to outputs
    _PO,
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
    _MODULE,
    _UNDEFINED_G,
    COUNT
};

extern const std::unordered_map<string, GType> Str_GType;
extern const std::unordered_map<GType, string, EnumClassHash> GType_Str;

class Node : virtual public Point<> // position
{
public:
    // the name of the gate
    string name;
    // the type of the gate
    GType type;
    // unique
    size_t id;
    // the value of the gate
    Value val;
    vector<Node *> ins;
    vector<Node *> outs;
    Point size;

public:
    Node() : name(nullptr), type(_UNDEFINED_G), id(init_id++), val(X) {}
    Node(const string &_name, const GType &_cell = WIRE, int _id = (init_id++), const Value &_val = X) : name(_name), type(_cell), id(_id), val(_val) {}
    ~Node();

    /** check if the node contains a clk input */
    bool containCLK();

    /** calculate the value of this Node by it's all inputs */
    Value calculate();

    /** operator overload */
    // AND
    Value operator&(const Node &B);
    Node &operator&=(const Node &B);
    // OR
    Value operator|(const Node &B);
    Node &operator|=(const Node &B);
    // XOR
    Value operator^(const Node &B);
    Node &operator^=(const Node &B);
    // NOT
    Value operator~();
    // for find
    bool operator==(const Node &B);
    bool operator==(const Node *B);
    // for sort
    bool operator<(const Node &B);
};

#endif