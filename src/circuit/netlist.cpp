#include "netlist.h"

Netlist::Netlist(/* args */)
{
}

Netlist::~Netlist()
{
    Util::cleanVP(this->PIs);
    Util::cleanVP(this->POs);
    Util::cleanVP(this->gates);
    cout << "The parser is destroyed!" << endl;
}


Node *Netlist::delete_node(Node *cur)
{
    if (!cur)
        return nullptr;
    if (cur->ins.empty() && cur->outs.empty() && cur->type == WIRE)
    {
        // cout << cur->name << " Wire is useless in delete_node!" << endl;
        delete cur;
        cur = nullptr;
        return nullptr;
    }
    size_t num_ins = cur->ins.size();
    if (num_ins != 1 && !(num_ins == 2 && cur->ins[0]->type == CLK))
    {
        error_fout(cur->name + " Node have none or more one inputs in delete_node!");
    }
    Node *tin = num_ins == 2 ? cur->ins.back() : cur->ins.front();
    if (!cur->outs.empty())
    {
        vector<Node *>::iterator it = cur->outs.begin();
        vector<Node *>::iterator it_end = cur->outs.end();
        while (it != it_end)
        {
            vector<Node *>::iterator temp_in = (*it)->ins.begin();
            vector<Node *>::iterator temp_in_end = (*it)->ins.end();
            bool flag = false;
            while (temp_in != temp_in_end)
            {
                if (cur == (*temp_in))
                {
                    (*temp_in) = tin;
                    flag = true;
                }
                ++temp_in;
            }
            if (flag)
            {
                tin->outs.emplace_back(*it);
            }
            else
            {
                error_fout("There are some wrong in" + cur->name);
            }
            ++it;
        }
        vector<Node *>().swap(cur->outs);
    }
    delete cur;
    cur = nullptr;
    return tin;
}

void Netlist::merge_node(Node *node, Node *repeat)
{
    if (!node || !repeat)
    {
        cout << "There are some NULL node in libhead.merge_node!" << endl;
        return;
    }
    if (node == repeat)
    {
        cout << "Both nodes are the same in libhead.merge_node!" << endl;
        return;
    }
    for (auto &out : repeat->outs)
    {
        // grandson.ins.push(son)
        vector<Node *>::iterator temp_in = out->ins.begin();
        vector<Node *>::iterator temp_in_end = out->ins.end();
        bool flag = false;
        while (temp_in != temp_in_end)
        {
            if (repeat == (*temp_in))
            {
                (*temp_in) = node;
                flag = true;
            }
            ++temp_in;
        }
        if (flag)
        {
            // son.outs.push(grandson)
            node->outs.emplace_back(out);
        }
        else
        {
            cout << "repeat can't be found in the inputs of repeat's outputs in libhead.merge_node!" << endl;
        }
    }
    vector<Node *>().swap(repeat->outs);
    delete repeat;
    repeat = nullptr;
}
