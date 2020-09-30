#include "cec.h"

cec::cec(const string &path_output) : ec(path_output)
{
}

cec::~cec()
{
}

bool cec::assign_PIs_value(vector<Node *> &PIs, int i)
{
    if (i == (int)PIs.size())
    {
        if (!evaluate(PIs))
        {
            this->fout << "NEQ" << endl;
            print_PIs_value(PIs, this->fout);
            return false;
        }
    }
    else
    {
        if (PIs.at(i)->cell == _CONSTANT)
        {
            if (!assign_PIs_value(PIs, i + 1))
                return false;
        }
        else
        {
            for (Value val = L; val < X; val = (Value)(val + 1))
            {
                PIs.at(i)->val = val;
                if (!assign_PIs_value(PIs, i + 1))
                    return false;
            }
        }
    }
    return true;
}

void cec::evaluate_from_PIs_to_POs(vector<Node *> &PIs)
{
    if (PIs.empty())
    {
        error_fout("The vector PIs is empty!");
    }
    if (assign_PIs_value(PIs, 0))
    {
        this->fout << "EQ" << endl;
    }
}

bool cec::evaluate(vector<Node *> &nodes)
{
    if (nodes.empty())
        return true;
    vector<Node *> qu;
    for (auto &g : nodes)
    {
        if (!g->outs.empty())
        {
            for (auto &out : g->outs)
            {
                ++out->vis;
                if (out->vis == out->ins.size())
                {
                    out->vis = 0;
                    out->val = calculate(out);
                    // cout << out->name << " " << out->val << endl;
                    if (!out->outs.empty())
                    {
                        qu.push_back(out);
                    }
                    else if (out->cell == _EXOR)
                    {
                        if (out->val == H)
                            return false;
                    }
                    else
                    {
                        error_fout(out->name + " Gate have no outputs!");
                    }
                }
            }
        }
        else
        {
            cout << "The outputs of the gate " << g->name << " are empty!" << endl;
        }
    }
    unique_element_in_vector(qu);
    return evaluate(qu);
}

void cec::evaluate_from_POs_to_PIs(vector<Node *> &POs) {
    
}