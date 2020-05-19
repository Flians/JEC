#include "ec.h"

void ec::print_PIs_value(vector<node *> *PIs, ofstream &output)
{
    for (auto pi : *PIs)
    {
        output << pi->name << " " << pi->val << endl;
    }
}
