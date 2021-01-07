#ifndef _NETLIST_H_
#define _NETLIST_H_

#include "util.h"
#include "libstring.h"

class Netlist
{
public:
    string name;
    size_t num_gate;
    vector<Node *> gates;
    std::unordered_map<std::string, int> map_PIs;
    std::unordered_map<std::string, int> map_POs;

public:
    // make an empty netlist
    Netlist();
    // parse an netlist
    Netlist(const string &path_verilog);
    Netlist(ifstream &in);
    // parse golden and revised verilog files, and make the miter
    Netlist(const string &path_golden, const string &path_revised);
    Netlist(ifstream &golden, ifstream &revised);
    ~Netlist();

    /** delete all splitters. If delete_dff is true, delete all DFFs*/
    void clean_spl(bool delete_dff = false);

    // print the netlist
    void print_netlist();

    // delete the node, return its parent
    static Node *delete_node(Node *node);
    // merge two nodes
    static void merge_node(Node *node, Node *repeat);

private:
    /** parse a port of the Node */
    void parse_inport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);
    void parse_outport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);
    /** parse the netlist file */
    void parse_netlist(stringstream &in, bool is_golden=true);
    void parse_netlist(ifstream &in, bool is_golden=true);
    void make_miter(ifstream &golden, ifstream &revised);    
};

#endif