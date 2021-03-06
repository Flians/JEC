#include "circuit/netlist.h"

Netlist::Netlist()
{
    this->name = GType_Str.at(_UNDEFINED_G);
    this->num_gate = 0;
    this->num_port = 0;
}

/** parse an netlist */
Netlist::Netlist(const string &path_verilog)
{
    this->num_gate = 0;
    this->num_port = 0;
    ifstream netlist(path_verilog);
    this->parse_netlist(netlist);
    netlist.close();
}
Netlist::Netlist(ifstream &in)
{
    this->num_gate = 0;
    this->num_port = 0;
    this->parse_netlist(in);
}

/** parse golden and revised verilog files, and make the miter */
Netlist::Netlist(const string &path_golden, const string &path_revised)
{
    this->num_gate = 0;
    this->num_port = 0;
    ifstream golden(path_golden);
    ifstream revised(path_revised);
    this->make_miter(golden, revised);
    golden.close();
    revised.close();
}
Netlist::Netlist(ifstream &golden, ifstream &revised)
{
    this->num_gate = 0;
    this->num_port = 0;
    this->make_miter(golden, revised);
}

Netlist::~Netlist()
{
    for (std::size_t i = 0; i < this->num_port; ++i)
    {
        auto &cur = this->ports[i];
        if (!cur)
        {
            continue;
        }
        cur->own = nullptr;
        std::vector<Edge *>().swap(cur->in_edges);

        std::size_t out_size = cur->out_edges.size();
        for (std::size_t i = 0; i < out_size; ++i)
        {
            auto &out_e = cur->out_edges[i];
            out_e->src = nullptr;
            out_e->tar = nullptr;
            delete out_e;
        }
        std::vector<Edge *>().swap(cur->out_edges);
        delete cur;
    }
    vector<Port *>().swap(this->ports);

    for (std::size_t i = 0; i < this->num_gate; ++i)
    {
        auto &cur = this->gates[i];
        if (!cur)
        {
            continue;
        }
        std::unordered_map<std::string, Port *>().swap(cur->ins);
        std::unordered_map<std::string, Port *>().swap(cur->outs);
        delete cur;
    }
    vector<Node *>().swap(this->gates);

    this->map_PIs.clear();
    this->map_POs.clear();
    JINFO("The netlist is destroyed!");
}

void Netlist::parse_inport(Node *g, const string &name, const string &item, const string &line, const std::unordered_map<std::string, Port *> &wires)
{
    Port *port = new Port(name, _IN, g, this->num_port++);
    this->ports.emplace_back(port);
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
        this->gates.emplace_back(const_PI);
        Port *port_ = new Port(_OUT, const_PI, this->num_port++);
        this->ports.emplace_back(port_);
        const_PI->outs.emplace(port_->name, port_);
        port_->add_output(port);
        this->map_PIs.emplace(const_PI->name, const_PI);
    }
    else
    {
        JERROR("There is a undefined input port '", item, "' in netlist.parse_inport for ", line);
    }
    g->ins.emplace(name, port);
}

void Netlist::parse_outport(Node *g, const string &name, const string &item, const string &line, const std::unordered_map<std::string, Port *> &wires)
{
    Port *port = new Port(name, _OUT, g, this->num_port++);
    this->ports.emplace_back(port);
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
        JERROR("There is a undefined output port '", item, "' in netlist.parse_outport for ", line);
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
                JERROR("There are some troubles in netlist.parse_netlist for multiple bits:", line);
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
                JERROR("There are some troubles in netlist.parse_netlist for input:", line);
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
                    JWARN("The comment '/*' is not end with '*/' in netlist.parse_netlist. \nThe line:", line);
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
                        JERROR("There are some troubles in netlist.parse_netlist for MODULE: ", line);
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
                                Node *node_ = new Node(item + "[" + to_string(i) + "]", _PI, this->num_gate++);
                                this->gates.emplace_back(node_);
                                Port *port_ = new Port(_OUT, node_, this->num_port++);
                                this->ports.emplace_back(port_);
                                node_->outs.emplace(port_->name, port_);
                                this->map_PIs.emplace(node_->name, node_);
                            }
                        }
                        else
                        {
                            Node *node_ = new Node(item, _PI, this->num_gate++);
                            this->gates.emplace_back(node_);
                            Port *port_ = new Port(_OUT, node_, this->num_port++);
                            this->ports.emplace_back(port_);
                            node_->outs.emplace(port_->name, port_);
                            this->map_PIs.emplace(node_->name, node_);
                            if (item.find("clk") != string::npos)
                            {
                                node_->type = _CLK;
                                swap(this->gates.front()->id, node_->id);
                                swap(this->gates.front(), this->gates.back());
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
                                Node *node_ = new Node(item + "[" + to_string(i) + "]", _PO, this->num_gate++);
                                this->gates.emplace_back(node_);
                                Port *port_ = new Port(_IN, node_, this->num_port++);
                                this->ports.emplace_back(port_);
                                node_->ins.emplace(port_->name, port_);
                                this->map_POs.emplace(node_->name, node_);
                            }
                        }
                        else
                        {
                            Node *node_ = new Node(item, _PO, this->num_gate++);
                            this->gates.emplace_back(node_);
                            Port *port_ = new Port(_IN, node_, this->num_port++);
                            this->ports.emplace_back(port_);
                            node_->ins.emplace(port_->name, port_);
                            this->map_POs.emplace(node_->name, node_);
                        }
                    }
                    break;
                }
                case _WIRE:
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
                        JERROR("There are some troubles in netlist.parse_netlist for GATE definition: ", line);
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
                                JERROR("There are some troubles in netlist.parse_netlist for PORT definition: ", line);
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
                JERROR("There key word '", item, "' is unknown in netlist.parse_netlist: ", line);
            }
        }
    }
    // clean all wires
    for (auto &item : wires)
    {
        size_t in_size = item.second->in_edges.size();
        size_t out_size = item.second->out_edges.size();
        if (in_size > 1 || in_size * out_size == 0)
        {
            if (in_size + out_size == 0)
            {
                JWARN("The wire '", item.second->name, "' in netlist '", this->name, " is useless.");
            }
            else
            {
                JERROR("The wire '", item.second->name, "' in netlist '", this->name, " is wrong!");
            }
        }
        Port *parent = item.second->in_edges[0]->src;
        if (out_size > 1 && parent->own->type != _CLK)
        {
            JWARN("The wire '", this->name, "' in netlist '", this->name, "' has multi fan-outs.");
        }
        for (size_t i = 0; i < out_size; ++i)
        {
            auto &out_e = item.second->out_edges[i];
            out_e->src = parent;
            parent->out_edges.emplace_back(out_e);
        }
        vector<Edge *>().swap(item.second->out_edges);
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
    vector<Port *>(this->ports).swap(this->ports);
    this->update_num_ports();
}

Node *Netlist::delete_node(Node *cur)
{
    if (!cur)
        return nullptr;
    if (cur->ins.empty() && cur->outs.empty() && cur->type == _WIRE)
    {
        JWARN("The wire '", cur->name, "' is useless in netlist.delete_node!");
        delete cur;
        cur = nullptr;
        return nullptr;
    }
    std::vector<Port *> predecessors = cur->get_predecessors_port(false);
    size_t num_ins = predecessors.size();
    if (num_ins != 1)
    {
        JWARN("The node '", cur->name, "' have none or more one inputs in netlist.delete_node!");
        return nullptr;
    }
    Port *tin = predecessors[0];
    for (auto &out : cur->outs)
    {
        auto &o_port = out.second;
        if (o_port)
        {
            auto &last_port = this->ports[--this->num_port];
            last_port->id = o_port->id;
            this->ports[o_port->id] = last_port;
            std::size_t out_size = o_port->out_edges.size();
            for (size_t i = 0; i < out_size; ++i)
            {
                auto &out_e = o_port->out_edges[i];
                out_e->src = tin;
                tin->out_edges.emplace_back(out_e);
            }
            vector<Edge *>().swap(o_port->out_edges);
        }
        o_port->own = nullptr;
        delete o_port;
    }
    std::unordered_map<std::string, Port *>().swap(cur->outs);
    for (auto &in : cur->ins)
    {
        auto &i_port = in.second;
        if (i_port)
        {
            auto &last_port = this->ports[--this->num_port];
            last_port->id = i_port->id;
            this->ports[i_port->id] = last_port;
            std::size_t in_size = i_port->in_edges.size();
            for (size_t i = 0; i < in_size; ++i)
            {
                auto &in_e = i_port->in_edges[i];
                in_e->set_source(nullptr);
            }
            vector<Edge *>().swap(i_port->in_edges);
        }
        i_port = nullptr;
        delete i_port;
    }
    std::unordered_map<std::string, Port *>().swap(cur->ins);
    this->ports.erase(this->ports.begin() + this->num_port, this->ports.end());
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
    if (node->get_indegree() != repeat->get_indegree() || !Util::contained(node->ins, repeat->ins))
    {
        JWARN("The two nodes do not have the same inputs, so they cannot be merged in netlist.merge_node!");
        return 0;
    }

    for (auto &out : repeat->outs)
    {
        auto &o_port = out.second;
        if (o_port)
        {
            auto &last_port = this->ports[--this->num_port];
            last_port->id = o_port->id;
            this->ports[o_port->id] = last_port;
            std::size_t out_size = o_port->out_edges.size();
            if (out_size == 0)
                continue;
            auto _find = node->outs.find(out.first);
            if (_find == node->outs.end())
            {
                JERROR("The output port '", out.first, "' of repeated node '", repeat->name, "' can't be found in the node '", node->name, "' in netlist.merge_node!");
            }
            for (size_t i = 0; i < out_size; ++i)
            {
                auto &out_e = o_port->out_edges[i];
                out_e->src = _find->second;
                _find->second->out_edges.emplace_back(out_e);
            }
            vector<Edge *>().swap(o_port->out_edges);
        }
        o_port->own = nullptr;
        delete o_port;
    }
    std::unordered_map<std::string, Port *>().swap(repeat->outs);

    for (auto &in : repeat->ins)
    {
        auto &i_port = in.second;
        if (i_port)
        {
            auto &last_port = this->ports[--this->num_port];
            last_port->id = i_port->id;
            this->ports[i_port->id] = last_port;
            std::size_t in_size = i_port->in_edges.size();
            for (size_t i = 0; i < in_size; ++i)
            {
                auto &in_e = i_port->in_edges[i];
                in_e->set_source(nullptr);
            }
            vector<Edge *>().swap(i_port->in_edges);
        }
        i_port = nullptr;
        delete i_port;
    }
    std::unordered_map<std::string, Port *>().swap(repeat->ins);

    this->ports.erase(this->ports.begin() + this->num_port, this->ports.end());
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

size_t Netlist::get_num_ports()
{
    return this->num_port;
}

void Netlist::update_num_ports()
{
    this->num_port = this->ports.size();
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
    this->gates.erase(this->gates.begin() + this->num_gate, this->gates.end());
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
            JWARN("The netlist '", this->name, "' is path-balanced in util.merge_nodes_between_networks!");
        }
        else
        {
            JWARN("The netlist '", this->name, "' is path_balanced in util.merge_nodes_between_networks!");
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
            if (!cur || cur->ins.empty())
            {
                continue;
            }
            Roaring same_id;
            bool flag = false;
            std::vector<Node *> predecessors = cur->get_predecessors(false);
            size_t num_npi = predecessors.size();
            for (auto &parent : predecessors)
            {
                Roaring tmp;
                std::vector<Node *> brothers = parent->get_successors();
                for (auto &brother : brothers)
                {
                    if (brother && brother->type == cur->type && brother != cur)
                    {
                        if (brother->get_indegree(false) != num_npi)
                        {
                            JWARN("'", cur->name, "' and '", brother->name, "' Nodes of the same type have different numbers of inputs in netlist.merge_nodes_between_networks");
                            continue;
                        }
                        tmp.add(brother->id);
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
                        JWARN("The node '", this->gates[eq_id]->name, "' can be replaced by the node '", cur->name, "'!");
                    }
                }
                ++it;
            }
        }
    }
    vector<pair<size_t, size_t>>().swap(position);
    // reassign the id for all nodes
    this->id_reassign();
    JINFO("The number of INV, BUF, and others reduction is ", std::to_string(reduce));
    return reduce;
}

ostream &operator<<(ostream &output, const Netlist &n)
{
    bool vis[n.num_gate] = {0};
    std::string str_module, str_pis, str_pos;
    str_module.append("module ").append(n.name).append("(");
    bool flag = true;
    for (auto &pi : n.map_PIs)
    {
        vis[pi.second->id] = 1;
        if (pi.second->type != _CONSTANT && (print_rsfq || (!print_rsfq && pi.second->type != _CLK)))
        {
            str_module.append(pi.first).append(", ");
            str_pis.append(pi.first).append(", ");
        }
        auto pi_succ = pi.second->get_successors_port();
        for (auto *tar : pi_succ)
        {
            tar->setProperty(PROPERTIES::NET_NAME, pi.first);
            for (auto &tar_src : tar->in_edges)
            {
                tar_src->src->setProperty(PROPERTIES::NET_NAME, pi.first);
            }
        }
    }
    flag = true;
    for (auto &po : n.map_POs)
    {
        vis[po.second->id] = 1;
        if (!flag)
        {
            str_module.append(", ");
            str_pos.append(", ");
        }
        else
        {
            flag = 0;
        }
        str_pos.append(po.first);
        str_module.append(po.first);
        auto po_pre = po.second->get_predecessors_port(print_rsfq);
        for (auto *src : po_pre)
        {
            src->setProperty(PROPERTIES::NET_NAME, po.first);
            for (auto &src_tar : src->out_edges)
            {
                src_tar->tar->setProperty(PROPERTIES::NET_NAME, po.first);
            }
        }
    }
    str_module.append(");");
    output << str_module << endl;
    if (!str_pis.empty())
    {
        // drop ','
        str_pis.pop_back();
        output << "    input " << str_pis << ";" << endl;
    }
    if (!str_pos.empty())
    {
        output << "    output " << str_pos << ";" << endl;
    }
    for (size_t i = 0; i < n.num_port; ++i)
    {
        if (n.ports[i] && n.ports[i]->type == _OUT && !n.ports[i]->out_edges.empty())
        {
            if (!n.ports[i]->own || (n.ports[i]->own && (vis[n.ports[i]->own->id] || n.ports[i]->own->type == _CLK)) || n.ports[i]->hasProperty(PROPERTIES::NET_NAME))
            {
                continue;
            }
            output << "    wire n" << n.ports[i]->id << ";" << endl;
        }
    }
    for (auto &node : n.gates)
    {
        if (!vis[node->id])
        {
            output << "    " << *node << endl;
        }
        vis[node->id] = 1;
    }
    output << "endmodule" << endl;
    return output;
}