#include "parser.h"

parser::parser(/* args */)
{
    this->constants = new vector<node *>[3];
    for (Value val = L; val <= X; val = (Value)(val + 1))
    {
        node *cont = new node("1'b" + L, _CONSTANT, val);
        this->constants->push_back(cont);
    }
    this->constants->at(2)->name = "1'bx";
}

parser::~parser()
{
    if (this->constants)
    {
        for (auto &con : *this->constants)
        {
            if (con->outs)
            {
                for (auto &out : *con->outs)
                {
                    vector<node *>::iterator temp = find(out->ins->begin(), out->ins->end(), con);
                    if (temp != out->ins->end())
                        out->ins->erase(temp);
                }
            }
            delete con;
        }
        vector<node *>().swap(*this->constants);
    }
    cout << "The parser is destroyed!" << endl;
}

vector<node *> *parser::get_constants()
{
    return this->constants;
}

node *parser::find_node_by_name(vector<node *> *nodes, string name)
{
    for (auto node : *nodes)
    {
        if (name == node->name)
        {
            return node;
        }
    }
    return nullptr;
}

bool parser::replace_node_by_name(vector<node *> *nodes, node *new_node)
{
    for (auto &node : *nodes)
    {
        if (new_node->name == node->name)
        {
            node = new_node;
            return true;
        }
    }
    return false;
}

void parser::parse_inport(node *g, string item, string line, vector<node *> *PIs, vector<node *> *wires)
{

    node *port;
    if (item.length() == 4 && libstring::startsWith(item, "1'b"))
    {
        switch (item[3])
        {
        case '0':
        case '1':
            port = this->constants->at(item[3] - '0');
            break;
        default:
            port = this->constants->at(2);
            break;
        }
    }
    else
    {
        port = find_node_by_name(wires, item);
        if (!port)
        {
            port = find_node_by_name(PIs, item);
            if (!port)
            {
                cout << "There are some troubles in parser.cpp for input port: " << line << endl;
                exit(-1);
            }
        }
    }
    g->ins->push_back(port);
    if (!port->outs)
    {
        port->outs = new vector<node *>[2];
    }
    port->outs->push_back(g);
}

void parser::parse_outport(node *g, string item, string line, vector<node *> *POs, vector<node *> *wires)
{
    node *port = find_node_by_name(wires, item);
    if (!port)
    {
        port = find_node_by_name(POs, item);
        if (!port)
        {
            cout << "There are some troubles in parser.cpp for output port: " << line << endl;
            exit(-1);
        }
    }
    g->outs->push_back(port);
    if (!port->ins)
    {
        port->ins = new vector<node *>[1];
    }
    port->ins->push_back(g);
}

void parser::parse_verilog(ifstream &in, vector<node *> *PIs, vector<node *> *POs, vector<node *> *wires, vector<node *> *gates)
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
                    cout << "There are some troubles in parser.cpp for multiple bits: " << line << endl;
                    exit(-1);
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
                case IN:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                PIs->push_back(new node(item + "[" + to_string(i) + "]", IN));
                            }
                        }
                        else
                        {
                            PIs->push_back(new node(item, IN));
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                case OUT:
                {
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        item = match[0];
                        if (bits_begin > 0)
                        {
                            for (int i = bits_begin; i <= bits_end; ++i)
                            {
                                POs->push_back(new node(item + "[" + to_string(i) + "]", _EXOR));
                            }
                        }
                        else
                        {
                            POs->push_back(new node(item, _EXOR));
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
                                if (!find_node_by_name(PIs, bitN) && !find_node_by_name(POs, bitN))
                                    wires->push_back(new node(bitN, WIRE));
                            }
                        }
                        else
                        {
                            if (!find_node_by_name(PIs, item) && !find_node_by_name(POs, item))
                                wires->push_back(new node(item, WIRE));
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                default:
                {
                    node *g = new node;
                    g->ins = new vector<node *>[2];
                    g->outs = new vector<node *>[1];
                    g->cell = nt;
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        g->name = match[0];
                        iterStart = match[0].second;
                    }
                    cout << "gate: " << g->name << endl;
                    int index_port = 0;
                    // ports: index_port = 0 -> output, index_port > 0 -> input
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        string item = match[0];
                        iterStart = match[0].second;
                        cout << "port: ";
                        if (item[0] == '.')
                        {
                            cout << item << " ";
                            bool flag = libstring::startsWith(item, ".dout");
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            if (flag)
                            {
                                parse_outport(g, item, line, POs, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, PIs, wires);
                            }
                        }
                        else
                        {
                            if (index_port == 0)
                            {
                                parse_outport(g, item, line, POs, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, PIs, wires);
                            }
                            ++index_port;
                        }
                        cout << item << endl;
                    }
                    gates->push_back(g);
                    break;
                }
                }
            }
        }
    }
}

void parser::parse_revised(ifstream &in, vector<node *> *PIs, vector<node *> *POs, vector<node *> *wires, vector<node *> *gates)
{
    string line;
    smatch match;
    regex pattern("[^ \f\n\r\t\v,;\()]+");
    while (getline(in, line))
    {
        line = libstring::trim(line);
        // skip annotations // and empty line
        if (libstring::startsWith(line, "//") || line.empty())
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
                    cout << "There are some troubles in parser.cpp for multiple bits: " << line << endl;
                    exit(-1);
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
                case IN:
                case OUT:
                    break;
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
                                if (!find_node_by_name(PIs, bitN) && !find_node_by_name(POs, bitN))
                                    wires->push_back(new node(bitN, WIRE));
                            }
                        }
                        else
                        {
                            if (!find_node_by_name(PIs, item) && !find_node_by_name(POs, item))
                                wires->push_back(new node(item, WIRE));
                        }
                        iterStart = match[0].second;
                    }
                    break;
                }
                default:
                {
                    node *g = new node;
                    g->ins = new vector<node *>[2];
                    g->outs = new vector<node *>[1];
                    g->cell = nt;
                    if (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        g->name = match[0];
                        iterStart = match[0].second;
                    }
                    cout << "gate: " << g->name << endl;
                    int index_port = 0;
                    // ports: index_port = 0 -> output, index_port > 0 -> input
                    while (regex_search(iterStart, iterEnd, match, pattern))
                    {
                        string item = match[0];
                        iterStart = match[0].second;
                        cout << "port: ";
                        if (item[0] == '.')
                        {
                            cout << item << " ";
                            bool flag = libstring::startsWith(item, ".dout");
                            regex_search(iterStart, iterEnd, match, pattern);
                            item = match[0];
                            iterStart = match[0].second;
                            if (flag)
                            {
                                parse_outport(g, item, line, POs, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, PIs, wires);
                            }
                        }
                        else
                        {
                            if (index_port == 0)
                            {
                                parse_outport(g, item, line, POs, wires);
                            }
                            else
                            {
                                parse_inport(g, item, line, PIs, wires);
                            }
                            ++index_port;
                        }
                        cout << item << endl;
                    }
                    gates->push_back(g);
                    break;
                }
                }
            }
        }
    }
}

void parser::build_miter(vector<node *> *PIs_golden, vector<node *> *POs_golden, vector<node *> *PIs_revised, vector<node *> *POs_revised)
{
    int ig_len = PIs_golden->size();
    int ir_len = PIs_revised->size();
    int og_len = POs_golden->size();
    int or_len = POs_revised->size();
    if (ig_len != ir_len || og_len != or_len)
    {
        cerr << "The golden Verilog has a different number of PIs and POs than the revised Verilog!" << endl;
        exit(-1);
    }
    vector<node *>::iterator iter = PIs_golden->begin();
    // merge all inputs
    while (iter != PIs_golden->end())
    {
        // cout << (*iter)->name << endl;
        node *pi = find_node_by_name(PIs_revised, (*iter)->name);
        if (!pi)
        {
            cerr << "The input pi in the golden Verilog does not exist in the revised Verilog!" << endl;
            exit(-1);
        }
        else
        {
            if (pi->outs)
            {
                vector<node *>::iterator it = pi->outs->begin();
                while (it != pi->outs->end())
                {
                    if (!replace_node_by_name((*it)->ins, (*iter)))
                    {
                        cerr << "There may be some wrong!" << endl;
                        exit(-1);
                    }
                    (*iter)->outs->push_back(*it);
                    it++;
                }
            }
            delete pi;
        }
        iter++;
    }
    vector<node *>().swap(*PIs_revised);
    // merge all outputs
    iter = POs_golden->begin();
    int i = 0;
    while (iter != POs_golden->end())
    {
        node *po = find_node_by_name(POs_revised, (*iter)->name);
        if (!po)
        {
            cerr << "The output po in the golden Verilog does not exist in the revised Verilog!" << endl;
            exit(-1);
        }
        else
        {
            (*iter)->cell = _EXOR;
            for (auto &tg : *po->ins)
            {
                (*iter)->ins->push_back(tg);
                tg->outs->push_back((*iter));
            }
            delete po;
        }
        iter++;
    }
    vector<node *>().swap(*POs_revised);
}

void parser::parse(ifstream &golden, ifstream &revised, vector<node *> *&PIs, vector<node *> *&POs)
{
    if (!golden.is_open())
    {
        cerr << "The golden can not be open!" << endl;
        exit(-1);
    }
    if (!PIs)
        PIs = new vector<node *>[32];
    if (!POs)
        POs = new vector<node *>[32];
    vector<node *> *wires_golden = new vector<node *>[128];
    vector<node *> *gates_golden = new vector<node *>[2048];
    parse_verilog(golden, PIs, POs, wires_golden, gates_golden);

    if (!revised.is_open())
    {
        cerr << "The revised can not be open!" << endl;
        exit(-1);
    }
    vector<node *> *wires_revised = new vector<node *>[128];
    vector<node *> *gates_revised = new vector<node *>[2048];
    /*
    vector<node *> *PIs_revised = new vector<node *>[32];
    vector<node *> *POs_revised = new vector<node *>[32];
    parse_verilog(revised, PIs_revised, POs_revised, wires_revised, gates_revised);
    build_miter(PIs, POs, PIs_revised, POs_revised);
    */

    parse_revised(revised, PIs, POs, wires_revised, gates_revised);
}

void parser::parse(const string &path_golden, const string &path_revised, vector<node *> *&PIs, vector<node *> *&POs)
{
    ifstream golden(path_golden);
    ifstream revised(path_revised);
    parse(golden, revised, PIs, POs);
    golden.close();
    revised.close();
}

void parser::printG(vector<node *> *nodes)
{
    if (!nodes || nodes->size() == 0)
        return;
    int len = nodes->size();
    vector<node *>::iterator pi = nodes->begin();
    while (pi != nodes->end())
    {
        cout << (*pi)->name << " " << Str_Value[(*pi)->cell] << " " << (*pi)->val << endl;
        printG((*pi)->outs);
        pi++;
    }
}