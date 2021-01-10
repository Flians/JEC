#ifndef _NODE_H_
#define _NODE_H_

#include "util/libhead.h"
#include "util/libstring.h"

class Node
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
public:
    Node() : name(NULL), type(_UNDEFINED), id(init_id++), val(X) {}
    Node(const string &_name, const GType &_cell = WIRE, int _id = (init_id++), const Value &_val = X) : name(_name), type(_cell), id(_id), val(_val) {}
    ~Node();

    /** check if the node contains a clk input */
    bool containCLK();

    /** calculate the value of this Node by it's all inputs */
    Value calculate();

    /** operator overload */
    // AND
    Value operator&(const Node &B);
    Node& operator&=(const Node &B);
    // OR
    Value operator|(const Node &B);
    Node& operator|=(const Node &B);
    // XOR
    Value operator^(const Node &B);
    Node& operator^=(const Node &B);
    // NOT
    Value operator~();
    // for find
    bool operator==(const Node &B);
    bool operator==(const Node *B);
    // for sort
    bool operator<(const Node &B);
};

#endif