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

bool jec::assign_PIs_value(vector<vector<node *> *> *layers, int i)
{
    if (i == layers->at(0)->size())
    {
        bool res=true;
        for (int level = 1; level < layers->size(); level++) {
            res = evaluate(layers->at(level));
        }
        if (!res)
        {
            this->fout << "NEQ" << endl;
            print_PIs_value(layers->at(0), this->fout);
            return false;
        }
    }
    else
    {
        if (layers->at(0)->at(i)->cell == _CONSTANT)
        {
            if (!assign_PIs_value(layers, i + 1))
                return false;
        }
        else
        {
            for (Value val = L; val < X; val = (Value)(val + 1))
            {
                layers->at(0)->at(i)->val = val;
                if (!assign_PIs_value(layers, i + 1))
                    return false;
            }
        }
    }
    return true;
}

bool jec::evaluate(vector<node *> *nodes)
{
    bool res = false;
    for (auto node:(*nodes)) {
        res |= calculate(node);
    }
    return true;
}

// evaluate from PIs to POs
void jec::evaluate_from_PIs_to_POs(vector<vector<node *> *> *layers)
{
    if (!layers || layers->size() == 0)
    {
        cerr << "The vector layers is empty!" << endl;
        exit(-1);
    }
    if (assign_PIs_value(layers, 0))
    {
        this->fout << "EQ" << endl;
    }
}

// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(vector<node *> *POs)
{
}