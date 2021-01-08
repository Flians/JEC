#include "ec/cec.h"

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
        if (PIs.at(i)->type == _CONSTANT)
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

bool cec::evaluate(const vector<Node *> &nodes)
{
    if (nodes.empty())
        return true;
    queue<Node *> qu;
    for (auto &g : nodes)
    {
        qu.push(g);
    }
    size_t len = qu.size();
    bool visited[init_id] = {0};
    while (len > 0)
    {
        while (len--) {
            Node* cur = qu.front();
            qu.pop();
            cur->calculate();
            visited[cur->id] = 1;
            for (auto &out : cur->outs)
            {
                if (!visited[cur->id])
                {
                    if (out->type == _EXOR && out->val == H)
                    {
                        return false;
                    }
                    qu.push(out);
                }
            }
        }
        len = qu.size();
    }
    return true;
}

void cec::evaluate_from_POs_to_PIs(vector<Node *> &POs) {
    
}