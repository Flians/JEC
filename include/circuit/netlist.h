#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "util.h"

class Netlist
{
private:
    vector<Node *> PIs;
    vector<Node *> POs;
    vector<Node *> gates;
public:
    Netlist(/* args */);
    ~Netlist();
};

#endif