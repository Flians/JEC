#include "circuit/node.h"

const std::unordered_map<string, GType> Str_GType = {
    {"constant", _CONSTANT},
    {"input", _PI},
    {"output", _PO},
    {"wire", WIRE},

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
    {_PI, "input"},
    {_PO, "output"},
    {WIRE, "wire"},
    {AND, "and"},
    {NAND, "nand"},
    {OR, "or"},
    {NOR, "nor"},
    {XOR, "xor"},
    {XNOR, "xnor"},
    {INV, "not"},
    {BUF, "buf"},
    {DFF, "jdff"},
    {SPL, "jspl"},
    {SPL3, "jspl3"},
    {CB, "jcb"},
    {CB3, "jcb3"},
    {_HMUX, "_HMUX"},
    {_DC, "_DC"},
    {_ANDF, "andf"},
    {_EXOR, "_EXOR"},
    {_MODULE, "module"},
    {_UNDEFINED_G, "undefined"}};

Node::~Node()
{
    // cout << "~delete Node: " << this->name << endl;
    for (auto &in : this->ins)
    {
        if (in.second)
        {
            delete in.second;
        }
    }
    this->ins.clear();
    for (auto &out : this->outs)
    {
        if (out.second)
        {
            delete out.second;
        }
    }
    this->outs.clear();
}

std::unordered_set<Node *> Node::get_successors()
{
    std::unordered_set<Node *> successors;
    for (auto &out : this->outs)
    {
        if (out.second)
        {
            for (auto &o_edge : out.second->out_edges)
            {
                successors.emplace(o_edge->get_target());
            }
        }
    }
    return successors;
}

std::unordered_set<Node *> Node::get_predecessor()
{
    std::unordered_set<Node *> predecessors;
    for (auto &in : this->ins)
    {
        if (in.second)
        {
            for (auto &i_edge : in.second->in_edges)
            {
                predecessors.emplace(i_edge->get_source());
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
    case _EXOR:
        return true;
    default:
        return false;
    }
}

Value Node::calculate()
{
    std::unordered_set<Node *> predecessors = this->get_predecessor();
    std::unordered_set<Node *>::iterator it_ = predecessors.begin();
    std::unordered_set<Node *>::iterator it_end = predecessors.end();
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
        ++it_;
        res = HMUX((*this->ins["I0"]->in_edges.begin())->get_source()->val,
                   (*this->ins["I1"]->in_edges.begin())->get_source()->val,
                   (*this->ins["S"]->in_edges.begin())->get_source()->val);
        break;
    case _DC:
        res = DC((*this->ins["C"]->in_edges.begin())->get_source()->val,
                 (*this->ins["D"]->in_edges.begin())->get_source()->val);
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
