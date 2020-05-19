#ifndef _PARSER_H_
#define _PARSER_H_

#include "libhead.h"

class parser
{
private:
    vector<node *> *constants;

public:
    parser(/* args */);
    ~parser();
    vector<node *> *get_constants();

    // find the node from vector<node *> *nodes by name
    node *find_node_by_name(vector<node *> *nodes, string name);

    // replace the node from vector<node *> *nodes with the new_node, which the name of this node is same as the new_node
    bool replace_node_by_name(vector<node *> *nodes, node *new_node);

    void parse_inport(node *g, string item, string line, vector<node *> *PIs, vector<node *> *wires);

    void parse_outport(node *g, string item, string line, vector<node *> *POs, vector<node *> *wires);

    // parse the verilog file
    void parse_verilog(ifstream &in, vector<node *> *PIs, vector<node *> *POs, vector<node *> *wires, vector<node *> *gates);

    // parse the revised verilog file
    void parse_revised(ifstream &in, vector<node *> *PIs, vector<node *> *POs, vector<node *> *wires, vector<node *> *gates);

    // build the miter for the Combinational Equivalence Checking (CEC)
    // POs is PIs_golden, and return POs
    void build_miter(vector<node *> *PIs_golden, vector<node *> *POs_golden, vector<node *> *PIs_revised, vector<node *> *POs_revised);

    // parse the verilog files, and return the PIs and POs of the miter
    void parse(ifstream &golden, ifstream &revised, vector<node *> *&PIs, vector<node *> *&POs);

    // parse the verilog files, and return the PIs and POs of the miter
    void parse(const string &path_golden, const string &path_revised, vector<node *> *&PIs, vector<node *> *&POs);

    // print the graph
    void printG(vector<node *> *);
};

#endif
