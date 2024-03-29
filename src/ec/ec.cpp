#include "ec/ec.h"

ec::ec(const string &path_output)
{
    this->fout.open(path_output, ios::out);
    if (!this->fout.is_open())
    {
        if (Libfile::createDirectory(path_output) == -1)
        {
            JERROR("The output file can not be open!");
        }
        this->fout.open(path_output, ios::out);
    }
}

ec::~ec()
{
    this->fout.flush();
    this->fout.close();
    JINFO("The ec is destroyed!");
}

size_t ec::merge_cone(int cur_color, Cone &cur_cone, Cone &other_cone, vector<pair<size_t, int>> &info)
{
    size_t res = other_cone.cur.size();
    while (!other_cone.cur.empty())
    {
        Node *tmp = other_cone.cur.front();
        other_cone.cur.pop_front();
        if (info[tmp->id].second != cur_color)
        {
            info[tmp->id].second = cur_color;
            cur_cone.cur.push_front(tmp);
        }
    }

    for (size_t i = 0, len = other_cone.inputs.size(); i < len; ++i)
    {
        auto &in = other_cone.inputs[i];
        info[in->id].second = cur_color;
        cur_cone.inputs.emplace_back(in);
    }
    vector<Node *>().swap(other_cone.inputs);

    for (size_t i = 0, len = other_cone.outputs.size(); i < len; ++i)
    {
        auto &out = other_cone.outputs[i];
        info[out->id].second = cur_color;
        cur_cone.outputs.emplace_back(out);
    }
    vector<Node *>().swap(other_cone.outputs);
    return res;
}

void ec::print_PIs_value(vector<Node *> &PIs, ofstream &output)
{
    for (auto &pi : PIs)
    {
        output << pi->name << " " << pi->val << endl;
    }
}

void ec::print_PIs_value(vector<Node *> &PIs, FILE *output)
{
    for (auto &pi : PIs)
    {
        fprintf(output, "%s %d", pi->name.c_str(), pi->val);
    }
}
