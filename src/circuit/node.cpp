#include "circuit/node.h"

const std::unordered_map<string, GType> Str_GType = {
    {"constant", _CONSTANT},
    {"input", _PI},
    {"output", _PO},
    {"wire", _WIRE},

    {"jand", AND},
    {"jnand", NAND},
    {"jor", OR},
    {"jnor", NOR},
    {"jxor", XOR},
    {"jxnor", XNOR},
    {"jnot", INV},
    {"jdff", DFF},
    {"jspl", SPL},
    {"jspl3", SPL3},
    {"jcb", CB},
    {"jcb3", CB3},
    {"jandf", _ANDF},

    {"and", AND},
    {"nand", NAND},
    {"or", OR},
    {"nor", NOR},
    {"xor", XOR},
    {"xnor", XNOR},
    {"not", INV},
    {"buf", BUF},
    {"_HMUX", _HMUX},
    {"_DC", _DC},

    {"_EXOR", _EXOR},
    {"module", _MODULE},
    {"undefined", _UNDEFINED_G}};

const std::unordered_map<GType, string, EnumClassHash> GType_Str = {
    {_CONSTANT, "constant"},
    {_CLK, "input"},
    {_PI, "input"},
    {_PO, "output"},
    {_WIRE, "wire"},
    {AND, "and"},
    {NAND, "nand"},
    {OR, "or"},
    {NOR, "nor"},
    {XOR, "xor"},
    {XNOR, "xnor"},
    {INV, "not"},
    {BUF, "buf"},
    {DFF, "dff"},
    {SPL, "spl"},
    {SPL3, "spl3"},
    {CB, "cb"},
    {CB3, "cb3"},
    {_HMUX, "_HMUX"},
    {_DC, "_DC"},
    {_ANDF, "andf"},
    {_EXOR, "output"},
    {_MODULE, "module"},
    {_UNDEFINED_G, "undefined"}};

Node::~Node()
{
    // cout << "~delete Node: " << this->name << endl;
    for (auto it = this->ins.begin(), it_end = this->ins.end(); it != it_end; ++it)
    {
        it->second->own = nullptr;
        delete it->second;
    }
    std::unordered_map<std::string, Port *>().swap(this->ins);

    for (auto it = this->outs.begin(), it_end = this->outs.end(); it != it_end; ++it)
    {
        it->second->own = nullptr;
        delete it->second;
    }
    std::unordered_map<std::string, Port *>().swap(this->outs);
}

std::size_t Node::get_outdegree(bool has_self) const
{
    std::size_t outdeg = 0;
    for (auto &out : this->outs)
    {
        if (out.second)
        {
            for (auto &o_edge : out.second->out_edges)
            {
                auto tar = o_edge->get_target();
                if (tar)
                {
                    if (!has_self && tar == this)
                    {
                        continue;
                    }
                    ++outdeg;
                }
            }
        }
    }
    return outdeg;
}

std::vector<Node *> Node::get_successors() const
{
    std::vector<Node *> successors;
    for (auto &out : this->outs)
    {
        if (out.second)
        {
            for (auto &o_edge : out.second->out_edges)
            {
                successors.emplace_back(o_edge->get_target());
            }
        }
    }
    return successors;
}

std::vector<Port *> Node::get_successors_port() const
{
    std::vector<Port *> successors;
    for (auto &out : this->outs)
    {
        if (out.second)
        {
            for (auto &o_edge : out.second->out_edges)
            {
                successors.emplace_back(o_edge->tar);
            }
        }
    }
    return successors;
}

std::size_t Node::get_indegree(bool has_clk, bool has_self) const
{
    std::size_t indeg = 0;
    for (auto &in : this->ins)
    {
        if (in.second)
        {
            for (auto &i_edge : in.second->in_edges)
            {
                Node *src = i_edge->get_source();
                if (src)
                {
                    if (!has_clk && src->type == _CLK)
                    {
                        continue;
                    }
                    if (!has_self && src == this)
                    {
                        continue;
                    }
                    ++indeg;
                }
            }
        }
    }
    return indeg;
}

std::vector<Node *> Node::get_predecessors(bool has_clk) const
{
    std::vector<Node *> predecessors;
    for (auto &in : this->ins)
    {
        if (in.second)
        {
            for (auto &i_edge : in.second->in_edges)
            {
                Node *src = i_edge->get_source();
                if (src)
                {
                    if (!has_clk && src->type == _CLK)
                    {
                        continue;
                    }
                    predecessors.emplace_back(i_edge->get_source());
                }
            }
        }
    }
    return predecessors;
}

std::vector<Port *> Node::get_predecessors_port(bool has_clk) const
{
    std::vector<Port *> predecessors;
    for (auto &in : this->ins)
    {
        if (in.second)
        {
            for (auto &i_edge : in.second->in_edges)
            {
                Node *src = i_edge->get_source();
                if (src)
                {
                    if (!has_clk && src->type == _CLK)
                    {
                        continue;
                    }
                    predecessors.emplace_back(i_edge->src);
                }
            }
        }
    }
    return predecessors;
}

bool Node::containCLK()
{
    switch (this->type)
    {
    case _CONSTANT:
    case _PI:
    case _PO:
    case AND:
    case NAND:
    case OR:
    case NOR:
    case XOR:
    case XNOR:
    case INV:
    case BUF:
    case DFF:
    case _HMUX:
    case _DC:
    case _ANDF:
    case _EXOR:
        return true;
    default:
        return false;
    }
}

Value Node::calculate()
{
    std::vector<Node *> predecessors = this->get_predecessors(false);
    std::vector<Node *>::iterator it_ = predecessors.begin();
    std::vector<Node *>::iterator it_end = predecessors.end();
    if (it_ == it_end)
    {
        return X;
    }
    Value res = (*it_)->val;
    switch (this->type)
    {
    case AND:
        while (it_ != it_end)
        {
            res = res & (*(++it_))->val;
        }
        break;
    case NAND:
        while (it_ != it_end)
        {
            res = res & (*(++it_))->val;
        }
        res = ~res;
        break;
    case OR:
        while (it_ != it_end)
        {
            res = res | (*(++it_))->val;
        }
        break;
    case NOR:
        while (it_ != it_end)
        {
            res = res | (*(++it_))->val;
        }
        res = ~res;
        break;
    case XOR:
        while (it_ != it_end)
        {
            res = res ^ (*(++it_))->val;
        }
        break;
    case XNOR:
        while (it_ != it_end)
        {
            res = res ^ (*(++it_))->val;
        }
        res = ~res;
        break;
    case INV:
        res = ~res;
        break;
    case BUF:
        break;
    case _HMUX:
        res = HMUX(this->ins["I0"]->in_edges[0]->get_source()->val,
                   this->ins["I1"]->in_edges[0]->get_source()->val,
                   this->ins["S"]->in_edges[0]->get_source()->val);
        break;
    case _DC:
        res = DC(this->ins["C"]->in_edges[0]->get_source()->val,
                 this->ins["D"]->in_edges[0]->get_source()->val);
        break;
    case _EXOR:
        res = EXOR(res, (*(++it_))->val);
        break;
    default:
        break;
    }
    this->val = res;
    return res;
}

/** operator overload */
// AND
Value Node::operator&(const Node &B)
{
    return this->val & B.val;
}
Node &Node::operator&=(const Node &B)
{
    this->val = this->val & B.val;
    // cout << this->val << " AND " << B.val << " = " << this->val << endl;
    return *this;
}

// OR
Value Node::operator|(const Node &B)
{
    return this->val | B.val;
}
Node &Node::operator|=(const Node &B)
{
    this->val = this->val | B.val;
    // cout << this->val << " OR " << B.val << " = " << this->val << endl;
    return *this;
}

// XOR
Value Node::operator^(const Node &B)
{
    return this->val ^ B.val;
}
Node &Node::operator^=(const Node &B)
{
    this->val = this->val ^ B.val;
    // cout << this->val << " XOR " << B.val << " = " << this->val << endl;
    return *this;
}

// not
Value Node::operator~()
{
    return ~this->val;
}

// for find
bool Node::operator==(const Node &B)
{
    return this->id == B.id;
}

// for find
bool Node::operator==(const Node *B)
{
    return this->id == B->id;
}

// for sort
bool Node::operator<(const Node &B)
{
    if (this->outs.size() != B.outs.size())
    {
        return this->outs.size() > B.outs.size();
    }
    else
    {
        return this->id < B.id;
    }
}

ostream &operator<<(ostream &output, const Node &n)
{
    output << "j";
    if (n.type == BUF)
    {
        output << GType_Str.at(DFF) << " " << n.name << "(";
    }
    else
    {
        output << GType_Str.at(n.type) << " " << n.name << "(";
    }
    for (auto &in : n.ins)
    {
        if (!print_rsfq && in.second->name == ".clk")
        {
            continue;
        }
        output << *in.second << ", ";
    }
    bool flag = 1;
    for (auto &out : n.outs)
    {
        if (flag)
        {
            flag = 0;
        }
        else
        {
            output << ", ";
        }
        output << *out.second;
    }
    output << ");";
    return output;
}
