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
        bool res = true;
        for (int level = 1; level < layers->size(); level++)
        {
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
    for (auto node : (*nodes))
    {
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
    // layers[0][0] is clk
    if (assign_PIs_value(layers, 1))
    {
        this->fout << "EQ" << endl;
    }
}

// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(vector<node *> *POs)
{
}

bool cmp(node *o1, node *o2)
{
    return o1->id < o2->id;
}

void jec::reduce_repeat_nodes(vector<vector<node *> *> *layers)
{
    int reduce = 0;
    for (int i = 0; i < layers->size() - 1; i++)
    {
        sort(layers->at(i)->begin(), layers->at(i)->end(), cmp);
        for (auto &item : (*layers->at(i)))
        {
            if (item->outs && item->outs->size() > 0)
            {
                sort(item->outs->begin(), item->outs->end(), cmp);
                if (item->cell == IN && item->name.find("clk") != string::npos)
                    continue;
                map<Gtype, vector<node *>> record;
                for (int j = 0; j < item->outs->size(); j++)
                {
                    if (record.count(item->outs->at(j)->cell))
                    {
                        record[item->outs->at(j)->cell].push_back(item->outs->at(j));
                    }
                    else
                    {
                        vector<node *> nodes;
                        nodes.push_back(item->outs->at(j));
                        record.insert(make_pair(item->outs->at(j)->cell, nodes));
                    }
                }
                for (auto &it : record)
                {
                    if (it.second.size() > 1)
                    {
                        if (it.first == DFF || it.first == INV)
                        {
                            for (int d = 1; d < it.second.size(); ++d)
                            {
                                // grandson.ins.push(son)
                                it.second.at(d)->outs->at(0)->ins->push_back(it.second.at(0));
                                // son.outs.push(grandson)
                                it.second.at(0)->outs->push_back(it.second.at(d)->outs->at(0));
                                layers->at(i + 1)->erase(find(layers->at(i + 1)->begin(), layers->at(i + 1)->end(), it.second.at(d)));
                                delete it.second.at(d);
                                reduce++;
                            }
                        } else {
                            
                        }
                    }
                }
                record.clear();
            }
        }
    }
    cout << "The number of DFF reduction is " << reduce << endl;
}