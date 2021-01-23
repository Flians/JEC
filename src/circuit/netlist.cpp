#include "circuit/netlist.h"

Netlist::Netlist()
{
    this->name = GType_Str.at(_UNDEFINED_G);
    this->num_gate = 0;
}

/** parse an netlist */
Netlist::Netlist(const string &path_verilog)
{
    this->num_gate = 0;
    ifstream netlist(path_verilog);
    this->parse_netlist(netlist);
    netlist.close();
}
Netlist::Netlist(ifstream &in)
{
    this->num_gate = 0;
    this->parse_netlist(in);
}

/** parse golden and revised verilog files, and make the miter */
Netlist::Netlist(const string &path_golden, const string &path_revised)
{
    this->num_gate = 0;
    ifstream golden(path_golden);
    ifstream revised(path_revised);
    this->make_miter(golden, revised);
    golden.close();
    revised.close();
}
Netlist::Netlist(ifstream &golden, ifstream &revised)
{
    this->num_gate = 0;
    this->make_miter(golden, revised);
}

Netlist::~Netlist()
{
    Util::cleanVP(this->gates);
    Util::cleanVP(this->ports);
    this->map_PIs.clear();
    this->map_POs.clear();
    JINFO("The netlist is destroyed!");
}

void Netlist::parse_inport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires)
{
    Node *port = nullptr;
    std::unordered_map<std::string, Node *>::const_iterator _find;
    if ((_find = wires.find(item)) != wires.end())
    {
        port = _find->second;
    }
    else if ((_find = map_PIs.find(item)) != map_PIs.end())
    {
        port = _find->second;
    }
    else if (item.length() == 4 && Libstring::startsWith(item, "1'b"))
    {
        int index = item[3] - '0';
        if (index > 2)
            index = 2;
        port = new Node(Const_Str.at((Value)index), _CONSTANT, this->num_gate++, (Value)index);
        this->gates.emplace_back(port);
        this->map_PIs.emplace(port->name, port);
    }
    else
    {
        JERROR("There is a undefined input port '" + item + "' in netlist.parse_inport for " + line);
    }
    port->outs.emplace_back(g);
    g->ins.emplace_back(port);
    if (port->type == _CLK)
    {
        swap(g->ins.front(), g->ins.back());
    }
}

void Netlist::parse_outport(Node *g, const string &item, const string &line, const std::unordered_map<std::string, Node *> &wires)
{
    Node *port = nullptr;
    std::unordered_map<std::string, Node *>::const_iterator _find;
    if ((_find = wires.find(item)) != wires.end())
    {
        port = _find->second;
    }
    else if ((_find = this->map_POs.find(item)) != this->map_POs.end())
    {
        port = _find->second;
    }
    else
    {
        JERROR("There is a undefined output port '" + item + "' in netlist.parse_outport for " + line);
    }
    port->ins.emplace_back(g);
    g->outs.emplace_back(port);
}

/** parse the netlist */
void Netlist::parse_netlist(stringstream &in, bool is_golden)
{
    string line;
    smatch match;
    regex pattern("[^\\s,\\();]+");
    string::const_iterator iterStart, iterEnd;
    auto parse_bits = [&line, &match, &pattern, &iterStart, &iterEnd](std::string &item, int &bits_begin, int &bits_end) {
        string::size_type mp = item.find_last_of(':');
        if (mp != item.npos)
        {
            string::size_type lp = item.find_last_of('[');
            string::size_type rp = item.find_last_of(']');
            if (lp == item.npos || rp == item.npos || lp >= rp)
            {
                JERROR("There are some troubles in netlist.parse_netlist for multiple bits: " + line);
            }
            bits_end = atoi(item.substr(lp + 1, mp - lp).c_str());
            bits_begin = atoi(item.substr(mp + 1, rp - mp).c_str());
            if (bits_begin > bits_end)
                swap(bits_begin, bits_end);
            if (regex_search(iterStart, iterEnd, match, pattern))
            {
                item = match[0];
                iterStart = match[0].second;
            }
            else
            {
                JERROR("There are some troubles in netlist.parse_netlist for input: " + line);
            }
            return true;
        }
        return false;
    };
    std::unordered_map<std::string, Node *> wires;
    while (!in.eof())
    {
        getline(in, line);
        Libstring::trim(line);
        // /* ... */
        if (Libstring::startsWith(line, "/*"))
        {
            size_t pos;
            bool flag = false;
            while ((pos = line.find("*/")) == line.npos)
            {
                string tl;
                if (in.eof())
                {
                    flag = true;
                    JWARN("The comment '/*' is not end with '*/' in netlist.parse_netlist. \nThe line: " + line);
                    break;
                }
                getline(in, tl);
                line += tl;
            }
            if (flag)
                break;
            line = line.substr(pos + 2);
            Libstring::trim(line);
        }
        // skip annotations and empty line
        if (line.find("//") == 0 || line[0] == '`' || line.empty())
            continue;
        // the wire is more than one line
        while (line.find(';') == line.npos && !Libstring::startsWith(line, "endmodule"))
        {
            string tl;
            if (in.eof())
            {
                break;
            }
            getline(in, tl);
            line += tl;
        }
        iterStart = line.begin();
        iterEnd = line.end();
        int bits_begin = -1, bits_end = -1;
        if (regex_search(iterStart, iterEnd, match, pattern))
        {
            string item = match[0];
            iterStart = match[0].second;
            // cout << item << endl;
            if (Str_GType.find(item) != Str_GType.end())
            {
                const GType &nt = Str_GType.at(item);
                switch (nt)
                {
                case _MODULE:
                {
                    if (!regex_search(iterStart, iterEnd, match, pattern))
                    {
                        JERROR("There are some troubles in netlist.parse_netlist for MODULE: " + line);
                    }
                    item = match[0];
                    iterStart = match[0].second;
                    if (is_golden)
                    {
                        this->name = item;
                    }
                    else
                    {
                        this->name.append("_miter_").append(item);
                    }
                    // int io_num = count(iterStart, iterEnd, ',');
                    break;
                }
                case _PI:
                {
                    if (!is_golden)
                        continue;
                    bool has_bits = false, flag_first = true;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (!has_bits && flag_first)
                        {
                            has_bits = parse_bits(item, bits_begin, bits_end);
                        }
                        flag_first = false;
                        if (has_bits)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                Node *pi_new = new Node(item + "[" + to_string(i) + "]", _PI, this->num_gate++);
                                this->gates.emplace_back(pi_new);
                                this->map_PIs.emplace(pi_new->name, pi_new);
                            }
                        }
                        else
                        {
                            Node *new_pi = new Node(item, _PI, this->num_gate++);
                            this->gates.emplace_back(new_pi);
                            this->map_PIs.emplace(new_pi->name, new_pi);
                            if (item.find("clk") != string::npos)
                            {
                                new_pi->type = _CLK;
                                swap(this->map_PIs[item], this->map_PIs[new_pi->name]);
                                swap(this->gates[0]->id, new_pi->id);
                                swap(this->gates[0], this->gates[this->num_gate - 1]);
                            }
                        }
                    }
                    break;
                }
                case _PO:
                {
                    if (!is_golden)
                        continue;
                    bool has_bits = false, flag_first = true;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (!has_bits && flag_first)
                        {
                            has_bits = parse_bits(item, bits_begin, bits_end);
                        }
                        flag_first = false;
                        if (has_bits)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                Node *new_po = new Node(item + "[" + to_string(i) + "]", _PO, this->num_gate++);
                                this->gates.emplace_back(new_po);
                                this->map_POs.emplace(new_po->name, new_po);
                            }
                        }
                        else
                        {
                            Node *new_po = new Node(item, _PO, this->num_gate++);
                            this->gates.emplace_back(new_po);
                            this->map_POs.emplace(new_po->name, new_po);
                        }
                    }
                    break;
                }
                case WIRE:
                {
                    bool has_bits = false, flag_first = true;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (!has_bits && flag_first)
                        {
                            has_bits = parse_bits(item, bits_begin, bits_end);
                        }
                        flag_first = false;
                        if (has_bits)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                string bitN = item + "[" + to_string(i) + "]";
                                if (wires.find(bitN) != wires.end())
                                {
                                    JERROR("The wire '" + bitN + "' is repeatedly defined in netlist.parse_netlist!");
                                }
                                if (this->map_PIs.find(bitN) == this->map_PIs.end() && this->map_POs.find(bitN) == this->map_POs.end())
                                {
                                    wires.emplace(bitN, new Node(bitN, WIRE));
                                }
                            }
                        }
                        else
                        {
                            if (wires.find(item) != wires.end())
                            {
                                JERROR("The wire '" + item + "' is repeatedly defined in netlist.parse_netlist!");
                            }
                            if (this->map_PIs.find(item) == this->map_PIs.end() && this->map_POs.find(item) == this->map_POs.end())
                            {
                                wires.emplace(item, new Node(item, WIRE));
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    if (!regex_search(iterStart, iterEnd, match, pattern))
                    {
                        JERROR("There are some troubles in netlist.parse_netlist for GATE definition: " + line);
                    }
                    Node *g = new Node(match[0], nt, this->num_gate++);
                    this->gates.emplace_back(g);
                    iterStart = match[0].second;
                    // cout << "gate: " << g->name << endl;
                    int index_port = 0;
                    // ports: index_port = 0 -> output, index_port > 0 -> input
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        // cout << "port: ";
                        if (item[0] == '.')
                        {
                            bool flag = Libstring::startsWith(item, ".dout");
                            if (!regex_search(iterStart, iterEnd, match, pattern))
                            {
                                JERROR("There are some troubles in netlist.parse_netlist for PORT definition: " + line);
                            }
                            item = match[0];
                            iterStart = match[0].second;
                            if (flag)
                            {
                                parse_outport(g, item, line, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, wires);
                            }
                        }
                        else
                        {
                            if (index_port == 0 || (g->type == SPL && index_port < 2) || (g->type == SPL3 && index_port < 3))
                            {
                                parse_outport(g, item, line, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, wires);
                            }
                            ++index_port;
                        }
                        // cout << item << endl;
                    }
                    break;
                }
                }
            }
            else
            {
                // read single module
                if (Libstring::startsWith(item, "endmodule"))
                    break;
                JERROR("There key word '" + item + "' is unknown in netlist.parse_netlist: " + line);
            }
        }
    }
    // clean all wires
    for (auto &item : wires)
    {
        if (item.second->outs.size() > 1)
        {
            JWARN("The wire '" + item.second->name + "' in netlist '" + this->name + "' has multi fan-outs!");
        }
        this->delete_node(item.second);
    }
    wires.clear();
}

void Netlist::parse_netlist(ifstream &in, bool is_golden)
{
    if (!in.is_open())
    {
        JWARN("The netlist can not be open!");
        return;
    }
    string buffer;
    // clear eof flag first
    in.clear();
    buffer.resize(in.seekg(0, std::ios::end).tellg());
    in.seekg(0, std::ios::beg).read(&buffer[0], static_cast<std::streamsize>(buffer.size()));
    stringstream f_input;
    f_input.str(buffer);
    this->parse_netlist(f_input, is_golden);
    buffer.clear();
    f_input.clear();
}

void Netlist::make_miter(ifstream &golden, ifstream &revised)
{
    this->parse_netlist(golden);
    this->parse_netlist(revised, false);
    // change the outputs' type into _EXOR
    for (auto &po : this->map_POs)
    {
        po.second->type = _EXOR;
    }
    vector<Node *>(this->gates).swap(this->gates);
    this->update_num_gates();
}

Node *Netlist::delete_node(Node *cur)
{
    if (!cur)
        return nullptr;
    size_t num_ins = cur->ins.size(), num_outs = cur->outs.size();
    if (num_ins == 0 && num_outs == 0 && cur->type == WIRE)
    {
        JWARN("The wire '" + cur->name + "' is useless in netlist.delete_node!");
        delete cur;
        cur = nullptr;
        return nullptr;
    }
    std::unordered_map<std::string, Port *> predecessors = cur->get_predecessors_port(false);
    std::unordered_map<std::string, Port *>::iterator it_ = predecessors.begin();
    std::unordered_map<std::string, Port *>::iterator it_end = predecessors.end();
    size_t num_ins = predecessors.size();
    if (num_ins != 1)
    {
        JWARN("The node '" + cur->name + "' have none or more one inputs in netlist.delete_node!");
        return nullptr;
    }
    Port *tin = (*predecessors.begin()).second;
    if (!cur->outs.empty())
    {
        for (auto &out : cur->outs)
        {
            if (out.second)
            {
                std::unordered_set<Edge *> o_edges = out.second->out_edges;
                for (auto &o_edge : o_edges)
                {
                    o_edge->set_source(tin);
                }
            }
        }
        std::unordered_map<std::string, Port *>().swap(cur->outs);
    }
    delete cur;
    cur = nullptr;
    return tin ? tin->own : nullptr;
}

bool Netlist::merge_node(Node *node, Node *repeat)
{
    if (!node || !repeat)
    {
        JWARN("There is NULL in these two vectors in netlist.merge_node!");
        return 0;
    }
    if (node == repeat)
    {
        JWARN("The two nodes are the same in netlist.merge_node!");
        return 0;
    }
    if (node->ins.size() != repeat->ins.size() || Util::vectors_intersection(node->ins, repeat->ins).size() != node->ins.size())
    {
        JWARN("The two nodes do not have the same inputs, so they cannot be merged in netlist.merge_node!");
        return 0;
    }
    for (size_t i = 0, len = repeat->outs.size(); i < len; ++i)
    {
        auto &out = repeat->outs[i];
        bool flag = false;
        for (size_t j = 0, len2 = out->ins.size(); j < len2; ++j)
        {
            if (repeat == out->ins[j])
            {
                out->ins[j] = node;
                flag = true;
            }
        }
        if (flag)
        {
            node->outs.emplace_back(out);
        }
        else
        {
            JWARN("The repeated node '" + repeat->name + "' can't be found in the inputs of it's outputs in netlist.merge_node!");
        }
    }
    vector<Node *>().swap(repeat->outs);
    delete repeat;
    repeat = nullptr;
    return 1;
}

size_t Netlist::get_num_gates()
{
    return this->num_gate;
}

void Netlist::update_num_gates()
{
    this->num_gate = this->gates.size();
}

bool Netlist::isEmpty()
{
    return this->gates.empty();
}

void Netlist::print_netlist()
{
    vector<Node *>::iterator pi = this->gates.begin();
    vector<Node *>::iterator pi_end = this->gates.end();
    while (pi != pi_end)
    {
        cout << (*pi)->name << " " << GType_Str.at((*pi)->type) << " " << (*pi)->val << endl;
        ++pi;
    }
}

void Netlist::id_reassign()
{
    if (this->isEmpty())
    {
        return;
    }
    size_t i = 0;
    while (i < this->num_gate)
    {
        if (this->gates[i])
        {
            this->gates[i]->id = i;
            ++i;
        }
        else
        {
            while (this->num_gate > i && !this->gates[--this->num_gate])
                ;
            if (this->num_gate == i)
            {
                break;
            }
            this->gates[this->num_gate]->id = i;
            this->gates[i] = this->gates[this->num_gate];
            this->gates[this->num_gate] = nullptr;
        }
    }
    // this->gates.erase(this->gates.begin() + this->num_gate, this->gates.end());
    this->gates.resize(this->num_gate);
    vector<Node *>(this->gates).swap(this->gates);
}

void Netlist::clean_useless_nodes()
{
}

void Netlist::clean_spl(bool delete_spl, bool delete_dff)
{
    if (!delete_spl && !delete_dff)
        return;
    bool flag_spl = false, flag_dff = false;
    size_t i = 0;
    while (i < this->num_gate)
    {
        auto &cur = this->gates[i];
        if ((delete_spl && (cur->type == SPL || cur->type == SPL3)) || (delete_dff && cur->type == DFF))
        {
            if (cur->type == DFF)
            {
                flag_dff = true;
            }
            else
            {
                flag_spl = true;
            }
            // maintain the id
            --this->num_gate;
            this->gates[this->num_gate]->id = cur->id;
            this->delete_node(cur);
            cur = this->gates[this->num_gate];
        }
        else
        {
            ++i;
        }
    }
    this->gates.erase(this->gates.begin() + this->num_gate, this->gates.end());
    vector<Node *>(this->gates).swap(this->gates);
    if (delete_spl && flag_spl)
    {
        this->setProperty<bool>(PROPERTIES::CLEAN_SPL, true);
    }
    if (delete_dff && flag_dff)
    {
        this->setProperty<bool>(PROPERTIES::CLEAN_DFF, true);
    }
}

int Netlist::merge_nodes_between_networks()
{
    if (this->isEmpty())
    {
        JWARN("The netlist is empty in util.merge_nodes_between_networks!");
        return 0;
    }
    if (!this->hasProperty(PROPERTIES::LAYERS))
    {
        JINFO("The layers is empty in util.merge_nodes_between_networks, and now build the layers.");
        if (!Util::path_balance(this))
        {
            JWARN("The netlist '" + this->name + "' is path-balanced in util.merge_nodes_between_networks!");
        }
        else
        {
            JWARN("The netlist '" + this->name + "' is path_balanced in util.merge_nodes_between_networks!");
        }
    }
    vector<vector<Node *>> &layers = this->getProperty(PROPERTIES::LAYERS);
    vector<pair<size_t, size_t>> position(this->num_gate, {0, 0});
    size_t num_layer = layers.size();
    for (size_t i = 0; i < num_layer; ++i)
    {
        size_t num_node = layers[i].size();
        for (size_t j = 0; j < num_node; ++j)
        {
            position[layers[i][j]->id] = {i, j};
        }
    }

    int reduce = 0;
    for (size_t i = 1; i < num_layer - 1; ++i)
    {
        size_t num_node = layers[i].size();
        for (size_t j = 0; j < num_node; ++j)
        {
            auto &cur = layers[i][j];
            auto &cur_type = cur->type;
            if (!cur || cur->ins.empty())
            {
                continue;
            }
            Roaring same_id;
            bool flag = false;
            size_t num_npi = cur->ins.size();
            for (size_t k = 0; k < num_npi; ++k)
            {
                auto &cur_in = cur->ins[k];
                if (cur_in->type == _CLK)
                {
                    continue;
                }
                Roaring tmp;
                for (auto &iout : cur_in->outs)
                {
                    if (iout && iout->type == cur_type && iout != cur)
                    {
                        if (iout->ins.size() != num_npi)
                        {
                            JWARN("The number of inputs of the same type of node is different in netlist.merge_nodes_between_networks");
                            continue;
                        }
                        tmp.add(iout->id);
                    }
                }
                if (flag)
                {
                    same_id &= tmp;
                }
                else
                {
                    same_id = tmp;
                    flag = true;
                }
            }
            Roaring::const_iterator it = same_id.begin();
            while (it != same_id.end())
            {
                auto &eq_id = it.i.current_value;
                if (this->gates[eq_id])
                {
                    if (this->merge_node(cur, this->gates[eq_id]))
                    {
                        this->gates[eq_id] = nullptr;
                        position[layers[position[eq_id].first].back()->id].second = position[eq_id].second;
                        layers[position[eq_id].first][position[eq_id].second] = layers[position[eq_id].first].back();
                        layers[position[eq_id].first].pop_back();
                        if (position[eq_id].first == i)
                        {
                            --num_node;
                        }
                        ++reduce;
                    }
                    else
                    {
                        JWARN("The node '" + this->gates[eq_id]->name + "' can be replaced by the node '" + layers[i][j]->name + "'!");
                    }
                }
                ++it;
            }
        }
    }
    vector<pair<size_t, size_t>>().swap(position);
    // reassign the id for all nodes
    this->id_reassign();
    JINFO("The number of INV, BUF, and others reduction is " + std::to_string(reduce));
    return reduce;
}

ostream &operator<<(ostream &output, const Netlist &n)
{

    output << "module " << n.name << "(";
    for (auto &pi : n.map_PIs)
    {
        if (pi.second->type != _CONSTANT)
        {
            output << "input wire " << pi.first << ", ";
        }
    }
    bool flag = true;
    for (auto &po : n.map_POs)
    {
        if (!flag)
        {
            output << ", ";
        }
        else
        {
            flag = 0;
        }
        output << "output reg " << po.first << " = 0";
    }
    output << ");" << endl;
    for (size_t i = 0; i < n.num_gate; ++i)
    {
        auto &node = n.gates[i];
        if (node->type != _CLK && node->type != _PI && node->type != _EXOR && node->type != _PO && node->type != _CONSTANT)
        {
            for (auto &out : node->outs)
            {
                output << "    wire n" << node->id << "_" << out->id << ";" << endl;
            }
        }
    }
    for (auto &node : n.gates)
    {
        if (node->type != _CLK && node->type != _PI && node->type != _EXOR && node->type != _PO && node->type != _CONSTANT)
        {
            output << "    " << GType_Str.at(node->type) << " " << node->name << "(";
            for (size_t i = 0, num_ins = node->ins.size(); i < num_ins; ++i)
            {
                if (node->ins[i]->type == _CLK)
                {
                    output << ".clk"
                           << "(" << node->ins[i]->name
                           << "), ";
                }
                else if (node->ins[i]->type == _PI || node->ins[i]->type == _CONSTANT)
                {
                    output << ".din" << (char)('a' + i - 1) << "(" << node->ins[i]->name
                           << "), ";
                }
                else
                {
                    output << ".din" << (char)('a' + i - 1) << "(n" << node->ins[i]->id << "_" << node->id
                           << "), ";
                }
            }
            bool flag = 1;
            for (size_t i = 0, num_outs = node->outs.size(); i < num_outs; ++i)
            {
                if (flag)
                {
                    flag = 0;
                }
                else
                {
                    output << ", ";
                }
                if (node->outs[i]->type == _EXOR || node->outs[i]->type == _PO)
                {
                    output << ".dout" << (char)('a' + i) << "(" << node->outs[i]->name
                           << ")";
                }
                else
                {
                    output << ".dout" << (char)('a' + i) << "(n" << node->id << "_" << node->outs[i]->id
                           << ")";
                }
            }
            output << ");" << endl;
        }
    }
    output << "endmodule" << endl;
    return output;
}