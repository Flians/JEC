#include "jec.h"

jec::jec(/* args */)
{
}

jec::jec(const string &path_output)
{
    this->fout.open(path_output, ios::out);
}

jec::~jec()
{
    this->fout.flush();
    this->fout.close();
}

bool jec::assign_PIs_value(vector<node *> *PIs, int i)
{
    return true;
}

bool jec::evaluate(vector<node *> nodes)
{
    return true;
}

// evaluate from PIs to POs
void jec::evaluate_from_PIs_to_POs(vector<node *> *PIs)
{
}
// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(vector<node *> *POs)
{
}