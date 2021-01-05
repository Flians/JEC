#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "util.h"
#include "libhead.h"

class Netlist
{
private:
    vector<Node *> PIs;
    vector<Node *> POs;
    vector<Node *> gates;

public:
    Netlist(/* args */);
    ~Netlist();

    // delete the node, return its parent
    static Node *delete_node(Node *node);

    // merge two nodes
    static void merge_node(Node *node, Node *repeat);
};

#endif