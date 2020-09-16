#ifndef _PARSER_H_
#define _PARSER_H_

#include "libhead.h"

class parser
{
private:
    std::unordered_map<std::string, Node *> wires_golden;
    std::unordered_map<std::string, Node *> wires_revised;
    std::unordered_map<std::string, int> map_PIs;
    std::unordered_map<std::string, int> map_POs;

    bool is_clk(const string &name);
    void parse_inport(Node *g, const string &item, const string &line, std::unordered_map<std::string, Node *> &wires);
    void parse_outport(Node *g, const string &item, const string &line, std::unordered_map<std::string, Node *> &wires);

public:
    vector<Node *> PIs;
    vector<Node *> POs;
    vector<Node *> constants;
    
    parser(/* args */);
    ~parser();
    vector<Node *> &get_PIs();
    vector<Node *> &get_POs();
    vector<Node *> &get_constants();

    // parse the verilog file
    void parse_verilog(stringstream &in, bool is_golden=true);

    // parse the verilog files, and return the PIs and POs of the miter
    void parse(ifstream &golden, ifstream &revised);

    // parse the verilog files, and return the PIs and POs of the miter
    void parse(const string &path_golden, const string &path_revised);

    // delete all wires
    void clean_wires();

    // clean the spl
    void clean_spl();

    // print the graph
    void printG(vector<Node *> &);

    // find the node from vector<node *> *nodes by name
    Node *find_node_by_name(vector<Node *> &nodes, const string &name);

    // replace the node from vector<node *> *nodes with the new_node, which the name of this node is same as the new_node
    bool replace_node_by_name(vector<Node *> &nodes, Node *new_node);

    // build the miter for the Combinational Equivalence Checking (CEC)
    // POs is PIs_golden, and return POs
    void build_miter(vector<Node *> &PIs_golden, vector<Node *> &POs_golden, vector<Node *> &PIs_revised, vector<Node *> &POs_revised);
};

#endif
