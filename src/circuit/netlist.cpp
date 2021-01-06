#include "netlist.h"

Netlist::Netlist()
{
    this->name = GType_Str[_UNDEFINED];
}

Netlist::Netlist(const string &_name)
{
    this->name = _name;
}

Netlist::~Netlist()
{
    Util::cleanVP(this->gates);
    this->map_PIs.clear();
    this->map_POs.clear();
    cout << "The netlist is destroyed!" << endl;
}

void Netlist::parse_inport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires)
{
    Node *port = nullptr;
    if (wires.find(item) != wires.end())
    {
        port = wires.at(item);
    }
    else if (map_PIs.find(item) != map_PIs.end())
    {
        port = this->gates[this->map_PIs[item]];
    }
    else if (item.length() == 4 && Libstring::startsWith(item, "1'b"))
    {
        int index = item[3] - '0';
        if (index > 2)
            index = 2;
        port = new Node(Const_Str[(Value)index], _CONSTANT, (Value)index);
        this->gates.emplace_back(port);
        this->map_PIs[port->name] = port->id;
    }
    else
    {
        error_fout("There is a undefined input port '" + item + "' in netlist.parse_inport for " + line);
    }
    port->outs.emplace_back(g);
    g->ins.emplace_back(port);
    if (port->type == CLK)
    {
        swap(g->ins.front(), g->ins.back());
    }
}

void Netlist::parse_outport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires)
{
    Node *port = nullptr;
    if (wires.find(item) != wires.end())
    {
        port = wires.at(item);
    }
    else if (this->map_POs.find(item) != this->map_POs.end())
    {
        port = this->gates[this->map_POs[item]];
    }
    else
    {
        error_fout("There is a undefined output port '" + item + "' in netlist.parse_outport for " + line);
    }
    port->ins.emplace_back(g);
    g->outs.emplace_back(port);
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
