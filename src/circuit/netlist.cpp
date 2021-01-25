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

void Netlist::parse_inport(Node *g, const string &name, const string &item, const string &line, const std::unordered_map<std::string, Port *> &wires)
{
    Port *port = new Port(name, _IN, g);
    std::unordered_map<std::string, Port *>::const_iterator _find_p;
    std::unordered_map<std::string, Node *>::const_iterator _find_n;
    if ((_find_p = wires.find(item)) != wires.end())
    {
        _find_p->second->add_output(port);
    }
    else if ((_find_n = map_PIs.find(item)) != map_PIs.end())
    {
        _find_n->second->outs.begin()->second->add_output(port);
    }
    else if (item.length() == 4 && Libstring::startsWith(item, "1'b"))
    {
        int index = item[3] - '0';
        if (index > 2)
            index = 2;
        Node *const_PI = new Node(Const_Str.at((Value)index), _CONSTANT, this->num_gate++, (Value)index);
        const_PI->outs.emplace(PType_Str.at(_OUT), new Port(_OUT, const_PI));
        const_PI->outs.begin()->second->add_output(port);
        this->gates.emplace_back(const_PI);
        this->map_PIs.emplace(const_PI->name, const_PI);
    }
    else
    {
        JERROR("There is a undefined input port '" + item + "' in netlist.parse_inport for " + line);
    }
    g->ins.emplace(name, port);
}

void Netlist::parse_outport(Node *g, const string &name, const string &item, const string &line, const std::unordered_map<std::string, Port *> &wires)
{
    Port *port = new Port(name, _OUT, g);
    std::unordered_map<std::string, Port *>::const_iterator _find_p;
    std::unordered_map<std::string, Node *>::const_iterator _find_n;
    if ((_find_p = wires.find(item)) != wires.end())
    {
        _find_p->second->add_input(port);
    }
    else if ((_find_n = this->map_POs.find(item)) != this->map_POs.end())
    {
        _find_n->second->ins.begin()->second->add_input(port);
    }
    else
    {
        JERROR("There is a undefined output port '" + item + "' in netlist.parse_outport for " + line);
    }
    g->outs.emplace(name, port);
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
    std::unordered_map<std::string, Port *> wires;
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
                                pi_new->outs.emplace(PType_Str.at(_OUT), new Port(PType_Str.at(_OUT), _OUT, pi_new));
                                this->gates.emplace_back(pi_new);
                                this->map_PIs.emplace(pi_new->name, pi_new);
                            }
                        }
                        else
                        {
                            Node *new_pi = new Node(item, _PI, this->num_gate++);
                            new_pi->outs.emplace(PType_Str.at(_OUT), new Port(PType_Str.at(_OUT), _OUT, new_pi));
                            this->gates.emplace_back(new_pi);
                            this->map_PIs.emplace(new_pi->name, new_pi);
                            if (item.find("clk") != string::npos)
                            {
                                new_pi->type = _CLK;
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
                                new_po->ins.emplace(PType_Str.at(_IN), new Port(PType_Str.at(_IN), _IN, new_po));
                                this->gates.emplace_back(new_po);
                                this->map_POs.emplace(new_po->name, new_po);
                            }
                        }
                        else
                        {
                            Node *new_po = new Node(item, _PO, this->num_gate++);
                            new_po->ins.emplace(PType_Str.at(_IN), new Port(PType_Str.at(_IN), _IN, new_po));
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
                                    JWARN("The wire '", bitN, "' is repeatedly defined in netlist.parse_netlist!");
                                }
                                if (this->map_PIs.find(bitN) == this->map_PIs.end() && this->map_POs.find(bitN) == this->map_POs.end())
                                {
                                    wires.emplace(bitN, new Port(bitN, _INOUT));
                                }
                            }
                        }
                        else
                        {
                            if (wires.find(item) != wires.end())
                            {
                                JWARN("The wire '", item, "' is repeatedly defined in netlist.parse_netlist!");
                            }
                            if (this->map_PIs.find(item) == this->map_PIs.end() && this->map_POs.find(item) == this->map_POs.end())
                            {
                                wires.emplace(item, new Port(item, _INOUT));
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
                        string port_name = match[0];
                        iterStart = match[0].second;
                        // cout << "port: ";
                        if (port_name[0] == '.')
                        {
                            bool flag = Libstring::startsWith(port_name, ".dout");
                            if (!regex_search(iterStart, iterEnd, match, pattern))
                            {
                                JERROR("There are some troubles in netlist.parse_netlist for PORT definition: " + line);
                            }
                            item = match[0];
                            iterStart = match[0].second;
                            if (flag)
                            {
                                parse_outport(g, port_name, item, line, wires);
                            }
                            else
                            {
                                parse_inport(g, port_name, item, line, wires);
                            }
                        }
                        else
                        {
                            if (index_port == 0 || (g->type == SPL && index_port < 2) || (g->type == SPL3 && index_port < 3))
                            {
                                parse_outport(g, PType_Str.at(_OUT), item, line, wires);
                            }
                            else
                            {
                                parse_inport(g, PType_Str.at(_OUT), item, line, wires);
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
        size_t in_size = item.second->in_edges.size();
        if (in_size > 1)
        {
            JWARN("The wire '" + item.second->name + "' in netlist '" + this->name + "' has multi fan-outs!");
        }
        Port *parent = in_size == 0 ? nullptr : (*item.second->in_edges.begin())->src;
        size_t out_size = item.second->out_edges.size();
        if (out_size > 1 && (!parent || parent->own->type != _CLK))
        {
            JWARN("The wire '" + this->name + "' has multi fan-ins in netlist '" + this->name + "'.");
        }
        while ((out_size--) > 0)
        {
            (*item.second->out_edges.begin())->set_source(parent);
        }
        delete item.second;
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
    this->id_reassign();
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
    size_t num_ins = predecessors.size();
    if (num_ins != 1)
    {
        JWARN("The node '" + cur->name + "' have none or more one inputs in netlist.delete_node!");
        return nullptr;
    }
    Port *tin = predecessors.begin()->second;
    if (!cur->outs.empty())
    {
        for (auto &out : cur->outs)
        {
            if (out.second)
            {
                std::size_t in_size = out.second->out_edges.size();
                while ((in_size--) > 0)
                {
                    (*out.second->out_edges.begin())->set_source(tin);
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
    if (node->ins.size() != repeat->ins.size() || Util::contained(node->ins, repeat->ins))
    {
        JWARN("The two nodes do not have the same inputs, so they cannot be merged in netlist.merge_node!");
        return 0;
    }
    std::unordered_map<std::string, Port *> successors_port = repeat->get_successors_port();

    for (auto &o_port : repeat->outs)
    {
        if (o_port.second)
        {
            size_t out_size = o_port.second->out_edges.size();
            while ((out_size--) > 0)
            {
                auto &o_edge = *o_port.second->out_edges.begin();
                if (o_edge)
                {
                    if (node->outs.find(o_port.first) != node->outs.end())
                    {
                        o_edge->set_source(node->outs[o_port.first]);
                    }
                    else
                    {
                        JERROR("The output port '", o_port.first, "' of repeated node '", repeat->name, "' can't be found in the node '", node->name, "' in netlist.merge_node!");
                    }
                }
                else
                {
                    o_port.second->out_edges.erase(nullptr);
                }
            }
        }
    }
    std::unordered_map<std::string, Port *>().swap(repeat->outs);
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
            std::unordered_map<std::string, Node *> predecessors = layers[i][j]->get_predecessors(false);
            size_t num_npi = layers[i][j]->ins.size();
            for (auto &parent : predecessors)
            {
                Roaring tmp;
                std::unordered_map<std::string, Node *> brothers = parent.second->get_successors();
                for (auto &brother : brothers)
                {
                    if (brother.second && brother.second->type == layers[i][j]->type && brother.second != layers[i][j])
                    {
                        if (brother.second->ins.size() != num_npi)
                        {
                            JWARN("'", layers[i][j]->name, "' and '", brother.first + "' Nodes of the same type have different numbers of inputs in netlist.merge_nodes_between_networks");
                            continue;
                        }
                        tmp.add(brother.second->id);
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
        output << "output reg " << po.first << "=0";
    }
    output << ");" << endl;
    for (size_t i = 0; i < n.num_gate; ++i)
    {
        auto &node = n.gates[i];
        if (node->type != _CLK && node->type != _PI && node->type != _EXOR && node->type != _PO && node->type != _CONSTANT)
        {
            for (auto &out : node->outs)
            {
                output << "    wire n" << node->id << "_" << out.second->id << ";" << endl;
            }
        }
    }
    for (auto &node : n.gates)
    {
        if (node->type != _PI && node->type != _PO && node->type != _CONSTANT)
        {
            output << *node << endl;
        }
    }
    output << "endmodule" << endl;
    return output;
}