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
    this->clean_wires();
    this->map_PIs.clear();
    this->map_POs.clear();
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

void parser::clean_wires()
{
    this->wires_golden.clear();
    this->wires_revised.clear();
}

void parser::parse_verilog(stringstream &in)
{
    string line;
    smatch match;
    regex pattern("[^ \f\n\r\t\v,;\()]+");
    while (getline(in, line))
    {
        line = libstring::trim(line);
        // skip annotations and empty line
        if (line.find("//") == 0 || line.empty())
            continue;
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
        if (regex_search(iterStart, iterEnd, match, pattern))
        {
            item = match[0];
            iterStart = match[0].second;
            // cout << item << endl;
            if (Value_Str.count(item))
            {
                Gtype nt = Value_Str[item];
                switch (nt)
                {
                case _MODULE:
                {
                    int io_num = count(iterStart, iterEnd, ',');
                    this->PIs.reserve(io_num);
                    this->POs.reserve(io_num);
                    break;
                }
                case IN:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        this->map_PIs[item] = this->PIs.size();
                        this->PIs.emplace_back(new Node(item, IN));
                        iterStart = match[0].second;
                    }
                    break;
                }
                case OUT:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        this->map_POs[item] = this->POs.size();
                        this->POs.emplace_back(new Node(item, _EXOR));
                        iterStart = match[0].second;
                    }
                    break;
                }
                case WIRE:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (this->map_PIs.count(item) == 0 && this->map_POs.count(item) == 0)
                            this->wires_golden[item] = new Node(item, WIRE);
                        iterStart = match[0].second;
                    }
                    break;
                }
                default:
                {
                    Node *g = new Node;
                    g->ins = new vector<Node *>;
                    g->outs = new vector<Node *>;
                    g->cell = nt;
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        g->name = match[0];
                        iterStart = match[0].second;
                    }
                    // output port
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (item[0] == '.')
                        {
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            // cout << item << endl;
                        }
                        Node *port = nullptr;
                        if (this->wires_golden.count(item))
                        {
                            port = this->wires_golden[item];
                        }
                        else if (this->map_POs.count(item))
                        {
                            port = this->POs[this->map_POs[item]];
                        }
                        else
                        {
                            error_fout("There is no output port " + item + " in parser.parse_verilog for " + line);
                        }
                        g->outs->emplace_back(port);
                        if (!port->ins)
                        {
                            port->ins = new vector<Node *>[1];
                        }
                        // cout << "output port: " << port->name << endl;
                        port->ins->emplace_back(g);
                    }
                    // input port
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (item[0] == '.')
                        {
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            // cout << item << endl;
                        }
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
                            if (this->wires_golden.count(item))
                            {
                                port = this->wires_golden[item];
                            }
                            else if (this->map_PIs.count(item))
                            {
                                port = this->PIs[this->map_PIs[item]];
                            }
                            else
                            {
                                error_fout("There is no input port " + item + " in parser.parse_verilog for " + line);
                            }
                        }
                        g->ins->emplace_back(port);
                        if (!port->outs)
                        {
                            port->outs = new vector<Node *>[2];
                        }
                        // cout << "input port: " << port->name << endl;
                        port->outs->emplace_back(g);
                    }
                    break;
                }
                }
            }
        }
    }
}

void parser::parse_revised(stringstream &in)
{
    string line;
    smatch match;
    regex pattern("[^ \f\n\r\t\v,;\()]+");
    while (getline(in, line))
    {
        line = libstring::trim(line);
        // skip annotations and empty line
        if (line.find("//") == 0 || line.empty())
            continue;
        // the sentence is more than one line
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
        if (regex_search(iterStart, iterEnd, match, pattern))
        {
            item = match[0];
            iterStart = match[0].second;
            // cout << item << endl;
            if (Value_Str.count(item))
            {
                Gtype nt = Value_Str[item];
                switch (nt)
                {
                case _MODULE:
                case IN:
                case OUT:
                    break;
                case WIRE:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (this->map_PIs.count(item) == 0 && this->map_POs.count(item) == 0)
                            this->wires_revised[item] = new Node(item, WIRE);
                        iterStart = match[0].second;
                    }
                    break;
                }
                default:
                {
                    Node *g = new Node;
                    g->ins = new vector<Node *>;
                    g->outs = new vector<Node *>;
                    g->cell = nt;
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        g->name = match[0];
                        iterStart = match[0].second;
                    }
                    // output port
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (item[0] == '.')
                        {
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            // cout << item << endl;
                        }
                        Node *port = nullptr;
                        if (this->wires_revised.count(item))
                        {
                            port = this->wires_revised[item];
                        }
                        else if (this->map_POs.count(item))
                        {
                            port = this->POs[this->map_POs[item]];
                        }
                        else
                        {
                            error_fout("There is no output port " + item + " in parser.parse_verilog for " + line);
                        }
                        g->outs->emplace_back(port);
                        if (!port->ins)
                        {
                            port->ins = new vector<Node *>[1];
                        }
                        // cout << "output port: " << port->name << endl;
                        port->ins->emplace_back(g);
                    }
                    // input port
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        iterStart = match[0].second;
                        if (item[0] == '.')
                        {
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            // cout << item << endl;
                        }
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
                            if (this->wires_revised.count(item))
                            {
                                port = this->wires_revised[item];
                            }
                            else if (this->map_PIs.count(item))
                            {
                                port = this->PIs[this->map_PIs[item]];
                            }
                            else
                            {
                                error_fout("There is no input port " + item + " in parser.parse_verilog for " + line);
                            }
                        }
                        g->ins->emplace_back(port);
                        if (!port->outs)
                        {
                            port->outs = new vector<Node *>[2];
                        }
                        // cout << "input port: " << port->name << endl;
                        port->outs->emplace_back(g);
                    }
                    break;
                }
                }
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

    parse_revised(f_input);
    buffer.clear();
    f_input.clear();

    // clear the wires
    this->clean_wires();

    // merge PIs and constants
    for (auto &con : this->constants)
    {
        if (con->outs)
        {
            this->PIs.emplace_back(con);
        }
    }
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

void parser::printG(vector<Node *> *nodes)
{
    if (!nodes || nodes->size() == 0)
        return;
    vector<Node *>::iterator pi = nodes->begin();
    vector<Node *>::iterator pi_end = nodes->end();
    while (pi != pi_end)
    {
        cout << (*pi)->name << " " << Str_Value[(*pi)->cell] << " " << (*pi)->val << endl;
        printG((*pi)->outs);
        ++pi;
    }
}

Node *parser::find_node_by_name(vector<Node *> &nodes, string &name)
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
            if (pi->outs)
            {
                vector<Node *>::iterator it = pi->outs->begin();
                vector<Node *>::iterator it_end = pi->outs->end();
                while (it != it_end)
                {
                    if (!replace_node_by_name(*(*it)->ins, (*iter)))
                    {
                        cerr << "There may be some wrong!" << endl;
                        error_fout("There may be some wrong!");
                    }
                    (*iter)->outs->emplace_back(*it);
                    ++it;
                }
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
            for (auto &tg : *po->ins)
            {
                (*iter)->ins->emplace_back(tg);
                tg->outs->emplace_back((*iter));
            }
            delete po;
            po = nullptr;
        }
        ++iter;
    }
    vector<Node *>().swap(POs_revised);
}
