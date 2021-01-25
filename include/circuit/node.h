#ifndef _NODE_H_
#define _NODE_H_

#include "circuit/port.h"
#include "util/libhead.h"
#include "util/_point.hpp"
#include "util/libstring.h"
#include "util/_map_property.hpp"

// all cell types
enum GType
{
    _CONSTANT = 0,
    _CLK = 1,
    _PI = 2,
    _EXOR = 3, // connected to outputs
    _PO = 4,
    WIRE = 5,
    AND = 6,
    NAND = 7,
    OR = 8,
    NOR = 9,
    XOR = 10,
    XNOR = 11,
    INV = 12,
    BUF = 13,
    DFF = 14,
    SPL = 15,
    SPL3 = 16,
    CB = 17,
    CB3 = 18,
    _HMUX = 19, // _HMUX \U$1 ( .O(\282 ), .I0(1'b1), .I1(\277 ), .S(\281 ));
    _DC = 20,   // _DC \n6_5[9] ( .O(\108 ), .C(\96 ), .D(\107 ));
    _ANDF = 21,
    _MODULE = 22,
    _UNDEFINED_G = 23,
    COUNT = 24
};

extern const std::unordered_map<std::string, GType> Str_GType;
extern const std::unordered_map<GType, std::string, EnumClassHash> GType_Str;

class Port;

class Node : virtual public MapProperty
{
public:
    // the name of the gate
    std::string name;
    // the type of the gate
    GType type;
    // unique
    size_t id;
    // the value of the gate
    Value val;
    std::unordered_map<std::string, Port *> ins;
    std::unordered_map<std::string, Port *> outs;

    Point<> position;
    Point<> size;

public:
    Node() : name(nullptr), type(_UNDEFINED_G), id(init_id++), val(X) {}
    Node(const std::string &_name, const GType &_cell = WIRE, int _id = (init_id++), const Value &_val = X) : name(_name), type(_cell), id(_id), val(_val) {}
    ~Node();

    std::unordered_map<std::string, Node *> get_successors() const;
    std::unordered_map<std::string, Port *> get_successors_port() const;
    std::unordered_map<std::string, Node *> get_predecessors(bool has_clk = true) const;
    std::unordered_map<std::string, Port *> get_predecessors_port(bool has_clk = true) const;

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

    friend ostream &operator<<(ostream &output, const Node &p);
};

#endif