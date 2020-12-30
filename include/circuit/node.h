#ifndef _NODE_H_
#define _NODE_H_
#include "libhead.h"

class node
{
private:
    // the name of the gate
    string name;
    // the type of the gate
    Gtype cell;
    // unique
    size_t id;
    vector<Node *> ins;
    vector<Node *> outs;
public:
    node(/* args */) : name("unknown"), cell(_UNDEFINED), id(init_id++) {}
    ~node();
};

#endif