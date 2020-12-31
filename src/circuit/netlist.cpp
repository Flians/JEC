#include "netlist.h"

Netlist::Netlist(/* args */)
{
}

Netlist::~Netlist()
{
    cleanVP<Node>(this->PIs);
    cleanVP<Node>(this->POs);
    cleanVP<Node>(this->gates);
    cout << "The parser is destroyed!" << endl;
}