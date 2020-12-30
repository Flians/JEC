#include "netlist.h"

netlist::netlist(/* args */)
{
}

netlist::~netlist()
{
    vector<Node *>().swap(this->PIs);
    vector<Node *>().swap(this->POs);
    cout << "The parser is destroyed!" << endl;
}