#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "util.h"

class Netlist
{
public:
    string name;
    vector<Node *> gates;
    std::unordered_map<std::string, int> map_PIs;
    std::unordered_map<std::string, int> map_POs;

public:
    Netlist();
    Netlist(const string &_name);
    ~Netlist();

    // delete the node, return its parent
    static Node *delete_node(Node *node);

    // merge two nodes
    static void merge_node(Node *node, Node *repeat);

private:
    /** parse a port of the Node */
    void parse_inport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);
    void parse_outport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);

};

#endif