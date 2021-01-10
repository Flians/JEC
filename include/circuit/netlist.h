#ifndef _NETLIST_H_
#define _NETLIST_H_

#include <math.h>
#include <float.h>
#include "util/util.h"
#include "util/libstring.h"

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

    /**
     * print the netlist
     */
    void print_netlist();

    /** 
     * delete all splitters. 
     * if delete_dff is true, delete all DFFs
     */
    void clean_spl(bool delete_dff = false);

    /** 
     * delete all useless nodes whose in-degree or out-degree is 0 except I/Os
     */
    void clean_useless_nodes();

    void cycle_break(vector<pair<Node *, Node *>> reversed);

    /**
     *  calculate the logic level of each node, and judge whether the netlist is path balanced
     * @return the layers group by the logic level
     */
    bool path_balance(vector<vector<Node *>> &layers);

    /** 
     * merge equivalent  nodes 
     * @return the number of nodes to be merged
     */
    int merge_nodes_between_networks(vector<vector<Node *>> &layers);

private:
    /** parse a port of the Node */
    void parse_inport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);
    void parse_outport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires);
    /** parse the netlist file */
    void parse_netlist(stringstream &in, bool is_golden = true);
    void parse_netlist(ifstream &in, bool is_golden = true);
    /**
     * parse two netlist files, and make a miter for them
     */
    void make_miter(ifstream &golden, ifstream &revised);
    /**
     * reassign id of each node, and assign ids to I/Os first
     */
    void id_reassign();
    /**
     * delete the node whose in-degree = 1 except the clk input
     * @return its non-clock parent node
     */
    Node *delete_node(Node *node);
    /**
     * merge two nodes
     */
    void merge_node(Node *node, Node *repeat);
};

#endif