#include "parser.h"

parser::parser(/* args */)
{
    this->constants.reserve(3);
    for (Value val = L; val <= X; val = (Value)(val + 1))
    {
        Node *cont = new Node(Const_Str[val], _CONSTANT, val);
        this->constants.emplace_back(cont);
    }
}

parser::~parser()
{
    vector<Node *>().swap(this->PIs);
    vector<Node *>().swap(this->POs);
    vector<Node *>().swap(this->constants);
    this->clean_wires_temp();
    cout << "The parser is destroyed!" << endl;
}

vector<Node *> &parser::get_PIs()
{
    return this->PIs;
}

vector<Node *> &parser::get_POs()
{
    return this->POs;
}

vector<Node *> &parser::get_constants()
{
    return this->constants;
}

void parser::clean_wires_temp()
{
    this->wires_golden.clear();
    this->wires_revised.clear();
    this->map_PIs.clear();
    this->map_POs.clear();
}

bool parser::is_clk(const string &name)
{
    return name.find("clk") != string::npos;
}

void parser::parse_inport(Node *g, const string &item, const string &line, std::unordered_map<std::string, Node *> &wires)
{
    Node *port;
    if (item.length() == 4 && libstring::startsWith(item, "1'b"))
    {
        switch (item[3])
        {
        case '0':
        case '1':
            port = this->constants[item[3] - '0'];
            break;
        default:
            port = this->constants[2];
            break;
        }
    }
    else
    {
        if (wires.count(item))
        {
            port = wires[item];
        }
        else if (this->map_PIs.count(item))
        {
            port = this->PIs[this->map_PIs[item]];
        }
        else
        {
            error_fout("There is no input port " + item + " in parser.parse_inport for " + line);
        }
    }
    port->outs.emplace_back(g);
    g->ins.emplace_back(port);
    if (port->cell == CLK) {
        swap(g->ins.front(), g->ins.back());
    }
}

void parser::parse_outport(Node *g, const string &item, const string &line, std::unordered_map<std::string, Node *> &wires)
{
    Node *port = nullptr;
    if (wires.count(item))
    {
        port = wires[item];
    }
    else if (this->map_POs.count(item))
    {
        port = this->POs[this->map_POs[item]];
    }
    else
    {
        error_fout("There is no output port " + item + " in parser.parse_outport for " + line);
    }
    port->ins.emplace_back(g);
    g->outs.emplace_back(port);
}

void parser::parse_verilog(stringstream &in, bool is_golden)
{
    string line;
    smatch match;
    regex pattern("[^ \f\n\r\t\v,;\()]+");
    while (getline(in, line))
    {
        line = libstring::trim(line);
        // skip annotations and empty line
        if (line.find("//") == 0 || line[0] == '`' || line.empty())
            continue;
        // /* ... */
        if (libstring::startsWith(line, "/*"))
        {
            while (line.find("*/") == line.npos)
            {
                string tl;
                if (!getline(in, tl))
                    return;
                line += tl;
            }
            continue;
        }
        // the wire is more than one line
        while (line.find(';') == line.npos)
        {
            string tl;
            if (!getline(in, tl))
                return;
            line += tl;
        }
        string::const_iterator iterStart = line.begin();
        string::const_iterator iterEnd = line.end();
        string item;
        int bits_begin = -1;
        int bits_end = -1;
        if (regex_search(iterStart, iterEnd, match, pattern))
        {
            item = match[0];
            iterStart = match[0].second;
            // cout << item << endl;
            int mp = item.find_last_of(':');
            if (mp != -1)
            {
                int lp = item.find_last_of('[');
                int rp = item.find_last_of(']');
                if (lp == -1 || rp == -1 || lp >= rp)
                {
                    error_fout("There are some troubles in parser.cpp for multiple bits: " + line);
                }
                bits_end = atoi(item.substr(lp + 1, mp - lp).c_str());
                bits_begin = atoi(item.substr(mp + 1, rp - mp).c_str());
                if (bits_begin > bits_end)
                    swap(bits_begin, bits_end);
                item = item.substr(0, lp);
            }
            if (Value_Str.count(item))
            {
                Gtype nt = Value_Str[item];
                switch (nt)
                {
                case _MODULE:
                {
                    if (!is_golden) continue;
                    int io_num = count(iterStart, iterEnd, ',');
                    this->PIs.reserve(io_num);
                    this->POs.reserve(io_num);
                    break;
                }
                case IN:
                {
                    if (!is_golden) continue;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                this->map_PIs[item + "[" + to_string(i) + "]"] = this->PIs.size();
                                this->PIs.emplace_back(new Node(item + "[" + to_string(i) + "]", IN));
                            }
                        }
                        else
                        {
                            this->map_PIs[item] = this->PIs.size();
                            if (is_clk(item)) {
                                this->PIs.emplace_back(new Node(item, CLK));
                                swap(this->map_PIs[item], this->map_PIs[this->PIs.front()->name]);
                                swap(this->PIs.front(), this->PIs.back());
                            } else {
                                this->PIs.emplace_back(new Node(item, IN));
                            }
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                case OUT:
                {
                    if (!is_golden) continue;
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                this->map_POs[item + "[" + to_string(i) + "]"] = this->POs.size();
                                this->POs.emplace_back(new Node(item + "[" + to_string(i) + "]", _EXOR));
                            }
                        }
                        else
                        {
                            this->map_POs[item] = this->POs.size();
                            this->POs.emplace_back(new Node(item, _EXOR));
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                case WIRE:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (bits_begin >= 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                string bitN = item + "[" + to_string(i) + "]";
                                if (this->map_PIs.count(bitN) == 0 && this->map_POs.count(bitN) == 0) {
                                    if (is_golden) {
                                        this->wires_golden[bitN] = new Node(bitN, WIRE);
                                    } else {
                                        this->wires_revised[bitN] = new Node(bitN, WIRE);
                                    }
                                } 
                            }
                        }
                        else
                        {
                            if (this->map_PIs.count(item) == 0 && this->map_POs.count(item) == 0) {
                                if (is_golden) {
                                    this->wires_golden[item] = new Node(item, WIRE);
                                } else {
                                    this->wires_revised[item] = new Node(item, WIRE);
                                }
                            }
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                default:
                {
                    Node *g = new Node();
                    g->cell = nt;
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        g->name = match[0];
                        iterStart = match[0].second;
                    }
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
                            bool flag = libstring::startsWith(item, ".dout");
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            if (flag)
                            {
                                parse_outport(g, item, line, is_golden ? this->wires_golden : this->wires_revised);
                            }
                            else
                            {
                                parse_inport(g, item, line, is_golden ? this->wires_golden : this->wires_revised);
                            }
                        }
                        else
                        {
                            if (index_port == 0 || (g->cell == SPL && index_port < 2) || (g->cell == SPL3 && index_port < 3))
                            {
                                parse_outport(g, item, line, is_golden ? this->wires_golden : this->wires_revised);
                            }
                            else
                            {
                                parse_inport(g, item, line, is_golden ? this->wires_golden : this->wires_revised);
                            }
                            ++index_port;
                        }
                        // cout << item << endl;
                    }
                    break;
                }
                }
            } else {
                error_fout("There key word '" + item + "' is unknown in parser.parse_verilog: " + line);
            }
        }
    }
}

void parser::parse(ifstream &golden, ifstream &revised)
{
    // parse the golden file
    if (!golden.is_open())
    {
        cerr << "The golden can not be open!" << endl;
        error_fout("The golden can not be open");
    }
    string buffer;
    buffer.resize(golden.seekg(0, std::ios::end).tellg());
    golden.seekg(0, std::ios::beg).read(&buffer[0], static_cast<std::streamsize>(buffer.size()));
    stringstream f_input;
    f_input.str(buffer);

    parse_verilog(f_input);
    buffer.clear();
    f_input.clear();

    // parse the revised file
    if (!revised.is_open())
    {
        cerr << "The revised can not be open!" << endl;
        error_fout("The revised can not be open");
    }

    buffer.resize(revised.seekg(0, std::ios::end).tellg());
    revised.seekg(0, std::ios::beg).read(&buffer[0], static_cast<std::streamsize>(buffer.size()));
    f_input.str(buffer);

    parse_verilog(f_input, false);
    buffer.clear();
    f_input.clear();

    // merge PIs and constants
    for (auto &con : this->constants)
    {
        if (!con->outs.empty())
        {
            this->PIs.emplace_back(con);
        }
    }

    // clear the wires
    this->clean_wires_temp();
}

void parser::parse(const string &path_golden, const string &path_revised)
{
    ifstream golden(path_golden);
    ifstream revised(path_revised);
    parse(golden, revised);
    golden.close();
    revised.close();
    cout << "The parsing process is over!" << endl;
}

void parser::printG(vector<Node *> &nodes)
{
    vector<Node *>::iterator pi = nodes.begin();
    vector<Node *>::iterator pi_end = nodes.end();
    while (pi != pi_end)
    {
        cout << (*pi)->name << " " << Str_Value[(*pi)->cell] << " " << (*pi)->val << endl;
        printG((*pi)->outs);
        ++pi;
    }
}

Node *parser::find_node_by_name(vector<Node *> &nodes, const string &name)
{
    for (auto node : nodes)
    {
        if (name == node->name)
        {
            return node;
        }
    }
    return nullptr;
}

bool parser::replace_node_by_name(vector<Node *> &nodes, Node *new_node)
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

void parser::build_miter(vector<Node *> &PIs_golden, vector<Node *> &POs_golden, vector<Node *> &PIs_revised, vector<Node *> &POs_revised)
{
    int ig_len = PIs_golden.size();
    int ir_len = PIs_revised.size();
    int og_len = POs_golden.size();
    int or_len = POs_revised.size();
    if (ig_len != ir_len || og_len != or_len)
    {
        cerr << "The golden Verilog has a different number of PIs and POs than the revised Verilog!" << endl;
        error_fout("The golden Verilog has a different number of PIs and POs than the revised Verilog!");
    }
    vector<Node *>::iterator iter = PIs_golden.begin();
    vector<Node *>::iterator iter_end = PIs_golden.end();
    // merge all inputs
    while (iter != iter_end)
    {
        // cout << (*iter)->name << endl;
        Node *pi = find_node_by_name(PIs_revised, (*iter)->name);
        if (!pi)
        {
            cerr << "The input pi in the golden Verilog does not exist in the revised Verilog!" << endl;
            error_fout("The input pi in the golden Verilog does not exist in the revised Verilog!");
        }
        else
        {
            vector<Node *>::iterator it = pi->outs.begin();
            vector<Node *>::iterator it_end = pi->outs.end();
            while (it != it_end)
            {
                if (!replace_node_by_name((*it)->ins, (*iter)))
                {
                    cerr << "There may be some wrong!" << endl;
                    error_fout("There may be some wrong!");
                }
                (*iter)->outs.emplace_back(*it);
                ++it;
            }
            delete pi;
            pi = nullptr;
        }
        ++iter;
    }
    vector<Node *>().swap(PIs_revised);
    // merge all outputs
    iter = POs_golden.begin();
    iter_end = POs_golden.end();
    while (iter != iter_end)
    {
        Node *po = find_node_by_name(POs_revised, (*iter)->name);
        if (!po)
        {
            cerr << "The output po in the golden Verilog does not exist in the revised Verilog!" << endl;
            error_fout("The output po in the golden Verilog does not exist in the revised Verilog!");
        }
        else
        {
            (*iter)->cell = _EXOR;
            for (auto &tg : po->ins)
            {
                (*iter)->ins.emplace_back(tg);
                tg->outs.emplace_back((*iter));
            }
            delete po;
            po = nullptr;
        }
        ++iter;
    }
    vector<Node *>().swap(POs_revised);
}
