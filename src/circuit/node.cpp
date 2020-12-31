#include "node.h"

Node::~Node()
{
    // cout << "~delete Node: " << this->name << endl;
    for (auto &in : this->ins)
    {
        if (in && !in->outs.empty())
        {
            vector<Node *>::iterator temp = find(in->outs.begin(), in->outs.end(), this);
            if (temp != in->outs.end())
            {
                // in->outs.erase(temp);
                *temp = *(in->outs.end() - 1);
                *(in->outs.end() - 1) = nullptr;
                in->outs.resize(in->outs.size() - 1);
            }
        }
    }
    vector<Node *>().swap(this->ins);

    for (auto &out : this->outs)
    {
        if (out && !out->ins.empty())
        {
            vector<Node *>::iterator temp = find(out->ins.begin(), out->ins.end(), this);
            if (temp != out->ins.end())
            {
                out->ins.erase(temp);
            }
        }
    }
    vector<Node *>().swap(this->outs);
}

Value Node::calculate()
{
    Value res = X;
    res = this->ins.front()->val;
    vector<Node *>::iterator it_ = this->ins.begin();
    if ((*it_)->type == CLK)
    {
        ++it_;
        res = (*it_)->val;
    }
    vector<Node *>::iterator it_end = this->ins.end() - 1;
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
        res = HMUX(res, (*it_)->val, (*(it_ + 1))->val);
        break;
    case _DC:
        res = DC(res, (*(it_ + 1))->val);
        break;
    case _EXOR:
        res = EXOR(res, (*(it_ + 1))->val);
        break;
    default:
        break;
    }
    this->val = res;
    return res;
}

/** operator overload */
// AND
Node Node::operator&(const Node &B)
{
    Node re;
    re.val = this->val & B.val;
    // cout << this->val << " AND " << B.val << " = " << re.val << endl;
    return re;
}
Node &Node::operator&=(const Node &B)
{
    this->val = this->val & B.val;
    // cout << this->val << " AND " << B.val << " = " << this->val << endl;
    return *this;
}

// OR
Node Node::operator|(const Node &B)
{
    Node re;
    re.val = this->val | B.val;
    // cout << this->val << " OR " << B.val << " = " << re.val << endl;
    return re;
}
Node &Node::operator|=(const Node &B)
{
    this->val = this->val | B.val;
    // cout << this->val << " OR " << B.val << " = " << this->val << endl;
    return *this;
}

// XOR
Node Node::operator^(const Node &B)
{
    Node re;
    re.val = this->val ^ B.val;
    // cout << this->val << " XOR " << B.val << " = " << re.val << endl;
    return re;
}
Node &Node::operator^=(const Node &B)
{
    this->val = this->val ^ B.val;
    // cout << this->val << " XOR " << B.val << " = " << this->val << endl;
    return *this;
}

// not
Node Node::operator~()
{
    Node re;
    re.val = ~this->val;
    // cout << this->val << " not = " << re.val << endl;
    return re;
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