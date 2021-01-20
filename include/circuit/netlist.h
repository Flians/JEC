#ifndef _NETLIST_H_
#define _NETLIST_H_

#include <cmath>
#include <cfloat>
#include <climits>
#include <ctime>
#include <cstdlib>
#include "util/util.h"
#include "util/_point.hpp"
#include "util/libstring.h"
#include "util/_properties.h"
#include "util/_map_property.hpp"

class Netlist : virtual public MapProperty
{
public:
    string name;
    vector<Node *> gates;
    std::unordered_map<std::string, int> map_PIs;
    std::unordered_map<std::string, int> map_POs;

    Point<> position;
    Point<> size;

private:
    size_t num_gate;

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
     * @return the number of nodes
     */
    size_t get_num_gates();
    void update_num_gates();

    /**
     * determine if the netlist is empty
     */
    bool isEmpty();

    /**
     * print the netlist
     */
    void print_netlist();

    /**
     * reassign id of each node, and assign ids to I/Os first
     */
    void id_reassign();

    /** 
     * delete all useless nodes whose in-degree or out-degree is 0 except I/Os
     */
    void clean_useless_nodes();

    /** 
     * delete all splitters, and set properties[CLEAN_SPL] = true.
     * @param delete_dff if delete_dff is true, delete all DFFs, and set properties[CLEAN_DFF] = true.
     */
    void clean_spl(bool delete_dff = false);

    /** 
     * merge equivalent nodes 
     * @return the number of nodes to be merged
     */
    int merge_nodes_between_networks();

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
     * delete the node whose in-degree = 1 except the clk input
     * @return its non-clock parent node
     */
    Node *delete_node(Node *node);
    /**
     * merge two nodes
     */
    bool merge_node(Node *node, Node *repeat);
};

#endif