#include "util.h"

void Util::unique_element_in_vector(vector<Node *> &v)
{
    sort(v.begin(), v.end(), [](const Node *A, const Node *B) {
        if (A->id == B->id)
        {
            return A->outs.size() > B->outs.size();
        }
        else
        {
            return A->id < B->id;
        }
    });
    vector<Node *>::iterator vector_iterator = unique(v.begin(), v.end());
    if (vector_iterator != v.end())
    {
        v.erase(vector_iterator, v.end());
    }
}

Node *Util::find_node_by_name(vector<Node *> &nodes, const string &name)
{
    for (auto &node : nodes)
    {
        if (name == node->name)
        {
            return node;
        }
    }
    return nullptr;
}

bool Util::replace_node_by_name(vector<Node *> &nodes, Node *new_node)
{
    for (auto &node : nodes)
    {
        if (new_node->name == node->name)
        {
            node = new_node;
            return true;
        }
    }
    return false;
}

/** make a miter for golden and revised */
Netlist *Util::make_miter(Netlist *&golden, Netlist *&revised)
{
    if (!golden) 
    {
        return revised;
    } else if (!revised) {
        return golden;
    }
    Netlist* miter = golden;
    if (golden->map_PIs.size() != revised->map_PIs.size() || golden->map_POs.size() != revised->map_POs.size())
    {
        error_fout("The golden Verilog has a different number of PIs and POs than the revised Verilog!");
    }
    auto iter = golden->map_PIs.begin(), iter_end = golden->map_PIs.end();
    // merge all inputs
    while (iter != iter_end)
    {
        // cout << iter->first << endl;
        auto pi = revised->map_PIs.find(iter->first);
        if (pi == revised->map_PIs.end())
        {
            error_fout("The input '" + iter->first + "' in the golden Verilog does not exist in the revised Verilog!");
        }
        vector<Node *>::iterator it = revised->gates[pi->second]->outs.begin();
        vector<Node *>::iterator it_end = revised->gates[pi->second]->outs.end();
        while (it != it_end)
        {
            if (!replace_node_by_name((*it)->ins, golden->gates[iter->second]))
            {
                error_fout("There are some troubles in util.make_miter!");
            }
            golden->gates[iter->second]->outs.emplace_back(*it);
            ++it;
        }
        delete revised->gates[pi->second];
        revised->gates[pi->second] = nullptr;
        ++iter;
    }
    revised->map_PIs.clear();
    // merge all outputs
    iter = golden->map_POs.begin();
    iter_end = golden->map_POs.end();
    while (iter != iter_end)
    {
        // cout << iter->first << endl;
        auto po = revised->map_POs.find(iter->first);
        if (po == revised->map_POs.end())
        {
            error_fout("The output '" + po->first + "' in the golden Verilog does not exist in the revised Verilog!");
        }
        golden->gates[iter->second]->type = _EXOR;
        for (auto &tg : revised->gates[po->second]->ins)
        {
            golden->gates[iter->second]->ins.emplace_back(tg);
            tg->outs.emplace_back(golden->gates[iter->second]);
        }
        delete revised->gates[po->second];
        revised->gates[po->second] = nullptr;
        ++iter;
    }
    revised->map_POs.clear();
    /** merge gates */
    for (auto gate : revised->gates) {
        if (gate) {
            gate->id = golden->num_gate++;
            golden->gates.push_back(gate);
        }
    }
    revised->gates.clear();
    delete revised;
    revised = nullptr;
    golden = nullptr;
    return miter;
}