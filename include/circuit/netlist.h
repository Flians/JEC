#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "libhead.h"

class netlist
{
private:
    vector<Node *> PIs;
    vector<Node *> POs;
public:
    netlist(/* args */);
    ~netlist();
};

netlist::netlist(/* args */)
{
}

netlist::~netlist()
{
}

#endif