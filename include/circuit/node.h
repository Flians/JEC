#ifndef _NODE_H_
#define _NODE_H_

#include "libhead.h"
#include "libstring.h"

class Node
{
public:
    // the name of the gate
    string name;
    // the type of the gate
    GType type;
    // the value of the gate
    Value val;
    // unique
    size_t id;
    vector<Node *> ins;
    vector<Node *> outs;
public:
    Node() : name(NULL), type(_UNDEFINED), val(X), id(init_id++) {}
    Node(const string &_name, const GType &_cell = WIRE, const Value &_val = X, int _id = (init_id++)) : name(_name), type(_cell), val(_val), id(_id) {}
    ~Node();

    /** calculate the value of this Node by it's all inputs */
    Value calculate();

    /** operator overload */
    // AND
    Node operator&(const Node &B);
    Node& operator&=(const Node &B);
    // OR
    Node operator|(const Node &B);
    Node& operator|=(const Node &B);
    // XOR
    Node operator^(const Node &B);
    Node& operator^=(const Node &B);
    // NOT
    Node operator~();
    // for find
    bool operator==(const Node &B);
    bool operator==(const Node *B);
    // for sort
    bool operator<(const Node &B);
};

#endif