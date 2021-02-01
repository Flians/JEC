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
    this->map_PIs.clear();
    this->map_POs.clear();
    INFO_Fout("The netlist is destroyed!");
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
        port = new Node(Const_Str.at((Value)index), _CONSTANT, this->num_gate++, (Value)index);
        this->gates.emplace_back(port);
        this->map_PIs.insert(make_pair(port->name, port->id));
    }
    else
    {
        ERROR_Exit_Fout("There is a undefined input port '" + item + "' in netlist.parse_inport for " + line);
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
        ERROR_Exit_Fout("There is a undefined output port '" + item + "' in netlist.parse_outport for " + line);
    }
    port->ins.emplace_back(g);
    g->outs.emplace_back(port);
}

/** parse the netlist */
void Netlist::parse_netlist(stringstream &in, bool is_golden)
{
    string line;
    smatch match;
    regex pattern("[^ \f\n\r\t\v,;\()]+");
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
                    WARN_Fout("The comment '/*' is not end with '*/' in netlist.parse_netlist. \nThe line: " + line);
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
        string::const_iterator iterStart = line.begin();
        string::const_iterator iterEnd = line.end();
        int bits_begin = -1;
        int bits_end = -1;
        if (regex_search(iterStart, iterEnd, match, pattern))
        {
            string item = match[0];
            iterStart = match[0].second;
            // cout << item << endl;
            int mp = item.find_last_of(':');
            if (mp != -1)
            {
                int lp = item.find_last_of('[');
                int rp = item.find_last_of(']');
                if (lp == -1 || rp == -1 || lp >= rp)
                {
                    ERROR_Exit_Fout("There are some troubles in netlist.parse_netlist for multiple bits: " + line);
                }
                bits_end = atoi(item.substr(lp + 1, mp - lp).c_str());
                bits_begin = atoi(item.substr(mp + 1, rp - mp).c_str());
                if (bits_begin > bits_end)
                    swap(bits_begin, bits_end);
                item = item.substr(0, lp);
            }
            if (Str_GType.find(item) != Str_GType.end())
            {
                const GType &nt = Str_GType.at(item);
                switch (nt)
                {
                case _MODULE:
                {
                    if (!regex_search(iterStart, iterEnd, match, pattern))
                    {
                        ERROR_Exit_Fout("There are some troubles in netlist.parse_netlist for MODULE: " + line);
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
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                Node *pi_new = new Node(item + "[" + to_string(i) + "]", _PI, this->num_gate);
                                this->gates.emplace_back(pi_new);
                                this->map_PIs.insert(make_pair(pi_new->name, this->num_gate++));
                            }
                        }
                        else
                        {
                            Node *new_pi = new Node(item, _PI, this->num_gate);
                            this->gates.emplace_back(new_pi);
                            this->map_PIs.insert(make_pair(new_pi->name, this->num_gate++));
                            if (item.find("clk") != string::npos)
                            {
                                new_pi->type = _CLK;
                                swap(this->map_PIs[item], this->map_PIs[new_pi->name]);
                                swap(this->gates[0]->id, new_pi->id);
                                swap(this->gates[0], new_pi);
                            }
                        }
                    }
                    break;
                }
                case _PO:
                {
                    if (!is_golden)
                        continue;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                Node *new_po = new Node(item + "[" + to_string(i) + "]", _PO, this->num_gate);
                                this->gates.emplace_back(new_po);
                                this->map_POs.insert(make_pair(new_po->name, this->num_gate++));
                            }
                        }
                        else
                        {
                            Node *new_po = new Node(item, _PO, this->num_gate);
                            this->gates.emplace_back(new_po);
                            this->map_POs.insert(make_pair(new_po->name, this->num_gate++));
                        }
                    }
                    break;
                }
                case WIRE:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (bits_begin >= 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                string bitN = item + "[" + to_string(i) + "]";
                                if (wires.find(bitN) != wires.end())
                                {
                                    ERROR_Exit_Fout("The wire '" + bitN + "' is repeatedly defined in netlist.parse_netlist!");
                                }
                                if (this->map_PIs.find(bitN) == this->map_PIs.end() && this->map_POs.find(bitN) == this->map_POs.end())
                                {
                                    wires.insert(make_pair(bitN, new Node(bitN, WIRE)));
                                }
                            }
                        }
                        else
                        {
                            if (wires.find(item) != wires.end())
                            {
                                ERROR_Exit_Fout("The wire '" + item + "' is repeatedly defined in netlist.parse_netlist!");
                            }
                            if (this->map_PIs.find(item) == this->map_PIs.end() && this->map_POs.find(item) == this->map_POs.end())
                            {
                                wires.insert(make_pair(item, new Node(item, WIRE)));
                            }
                        }
                    }
                    break;
                }
                default:
                {
                    if (!regex_search(iterStart, iterEnd, match, pattern))
                    {
                        ERROR_Exit_Fout("There are some troubles in netlist.parse_netlist for GATE definition: " + line);
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
                                ERROR_Exit_Fout("There are some troubles in netlist.parse_netlist for PORT definition: " + line);
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
                if (item == "endmodule")
                    break;
                ERROR_Exit_Fout("There key word '" + item + "' is unknown in netlist.parse_netlist: " + line);
            }
        }
    }
    // clean all wires
    for (auto &item : wires)
    {
        if (item.second->outs.size() > 1)
        {
            WARN_Fout("The netlist '" + this->name + "' has multi fan-outs!");
        }
        this->delete_node(item.second);
    }
    wires.clear();
}

void Netlist::parse_netlist(ifstream &in, bool is_golden)
{
    if (!in.is_open())
    {
        ERROR_Exit_Fout("The netlist can not be open!");
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
    for (auto po : this->map_POs)
    {
        this->gates[po.second]->type = _EXOR;
    }
    vector<Node *>(this->gates).swap(this->gates);
    this->update_num_gates();
}

Node *Netlist::delete_node(Node *cur)
{
    if (!cur)
        return nullptr;
    if (cur->ins.empty() && cur->outs.empty() && cur->type == WIRE)
    {
        WARN_Fout("The wire '" + cur->name + "' is useless in netlist.delete_node!");
        delete cur;
        cur = nullptr;
        return nullptr;
    }
    size_t num_ins = cur->ins.size();
    if (num_ins != 1 && !(cur->type != WIRE && num_ins == 2 && cur->ins[0]->type == _CLK))
    {
        WARN_Fout("The node '" + cur->name + "' have none or more one inputs in netlist.delete_node!");
        return nullptr;
    }
    Node *tin = cur->ins.back();
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
                ERROR_Exit_Fout("There are some troubles in netlist.delete_node for the node: " + cur->name);
            }
            ++it;
        }
        vector<Node *>().swap(cur->outs);
    }
    delete cur;
    cur = nullptr;
    return tin;
}

bool Netlist::merge_node(Node *node, Node *repeat)
{
    if (!node || !repeat)
    {
        WARN_Fout("There is NULL in these two vectors in netlist.merge_node!");
        return 0;
    }
    if (node == repeat)
    {
        WARN_Fout("The two nodes are the same in netlist.merge_node!");
        return 0;
    }
    if (node->ins.size() != repeat->ins.size() || Util::vectors_intersection(node->ins, repeat->ins).size() != node->ins.size())
    {
        WARN_Fout("The two nodes do not have the same inputs, so they cannot be merged in netlist.merge_node!");
        return 0;
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
            WARN_Fout("The repeated node '" + repeat->name + "' can't be found in the inputs of it's outputs in netlist.merge_node!");
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
    sort(this->gates.begin(), this->gates.end(), [](Node *a, Node *b) {
        if (a && b)
        {
            return a->type < b->type;
        }
        else
        {
            return a != nullptr;
        }
    });
    this->map_PIs.clear();
    this->map_POs.clear();
    while (!this->gates.back())
    {
        --this->num_gate;
        this->gates.pop_back();
    }
    size_t i = 0;
    while (i < this->num_gate)
    {
        if (this->gates[i])
        {
            this->gates[i]->id = i;
            if (this->gates[i]->type <= _PI)
            {
                this->map_PIs[this->gates[i]->name] = i;
            }
            else if (this->gates[i]->type <= _PO)
            {
                this->map_POs[this->gates[i]->name] = i;
            }
            ++i;
        }
        else
        {
            this->gates[--this->num_gate]->id = i;
            this->gates[i] = this->gates[this->num_gate];
            this->gates.pop_back();
        }
    }
    vector<Node *>(this->gates).swap(this->gates);
}

void Netlist::clean_useless_nodes()
{
}

void Netlist::clean_spl(bool delete_dff)
{
    bool flag_spl = false, flag_dff = false;
    size_t i = 0;
    while (i < this->num_gate)
    {
        if (this->gates[i]->type == SPL || this->gates[i]->type == SPL3 || (delete_dff && this->gates[i]->type == DFF))
        {
            if (this->gates[i]->type == DFF)
            {
                flag_dff = true;
            }
            else
            {
                flag_spl = true;
            }
            // maintain the id
            --this->num_gate;
            swap(this->gates[i]->id, this->gates[this->num_gate]->id);
            this->delete_node(this->gates[i]);
            this->gates[i] = this->gates[this->num_gate];
            this->gates.pop_back();
        }
        else
        {
            ++i;
        }
    }
    if (flag_spl)
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
        WARN_Fout("The netlist is empty in util.merge_nodes_between_networks!");
        return 0;
    }
    if (!this->hasProperty(PROPERTIES::LAYERS))
    {
        INFO_Fout("The layers is empty in util.merge_nodes_between_networks, and now build the layers.");
        if (!Util::path_balance(this))
        {
            WARN_Fout("The netlist is path-balanced in util.merge_nodes_between_networks!");
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
            if (!layers[i][j] || layers[i][j]->ins.empty())
            {
                continue;
            }
            Roaring same_id;
            bool flag = false;
            size_t num_npi = layers[i][j]->ins.size();
            for (size_t k = 0; k < num_npi; ++k)
            {
                if (layers[i][j]->ins[k]->type == _CLK)
                {
                    continue;
                }
                Roaring tmp;
                for (auto &iout : layers[i][j]->ins[k]->outs)
                {
                    if (iout && iout->type == layers[i][j]->type && iout != layers[i][j])
                    {
                        if (iout->ins.size() != num_npi)
                        {
                            WARN_Fout("The number of inputs of the same type of node is different in netlist.merge_nodes_between_networks");
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
                if (this->gates[it.i.current_value])
                {
                    if (this->merge_node(layers[i][j], this->gates[it.i.current_value]))
                    {
                        this->gates[it.i.current_value] = nullptr;
                        position[layers[position[it.i.current_value].first].back()->id].second = position[it.i.current_value].second;
                        layers[position[it.i.current_value].first][position[it.i.current_value].second] = layers[position[it.i.current_value].first].back();
                        layers[position[it.i.current_value].first].pop_back();
                        if (position[it.i.current_value].first == i)
                        {
                            --num_node;
                        }
                        ++reduce;
                    }
                    else
                    {
                        WARN_Fout("The node '" + this->gates[it.i.current_value]->name + "' can be replaced by the node '" + layers[i][j]->name + "'!");
                    }
                }
                ++it;
            }
        }
    }
    vector<pair<size_t, size_t>>().swap(position);
    // reassign the id for all nodes
    this->id_reassign();
    std::cout << "The number of INV, BUF, and others reduction is " << reduce << std::endl;
    return reduce;
}