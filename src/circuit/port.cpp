#include "circuit/port.h"

const std::unordered_map<string, PType> Str_PType = {
    {".din", _IN},
    {".dout", _OUT},
    {".din_out", _INOUT},
    {".undefined", _UNDEFINED_P}};

const std::unordered_map<PType, string, EnumClassHash> PType_Str = {
    {_IN, ".din"},
    {_OUT, ".dout"},
    {_INOUT, ".din_out"},
    {_UNDEFINED_P, ".undefined"}};

Port::~Port()
{
    std::size_t in_size = this->in_edges.size();
    while ((in_size--) > 0)
    {
        delete *this->in_edges.begin();
    }
    this->in_edges.clear();
    std::size_t out_size = this->out_edges.size();
    while ((out_size--) > 0)
    {
        delete *this->out_edges.begin();
    }
    this->out_edges.clear();
    if (this->own)
    {
        if (this->type == PType::_IN)
        {
            this->own->ins.erase(this->name);
        }
        else if (this->type == PType::_OUT)
        {
            this->own->outs.erase(this->name);
        }
        else
        {
            this->own->ins.erase(this->name);
            this->own->outs.erase(this->name);
        }
    }
    this->own = nullptr;
}

void Port::add_output(Port *tar)
{
    Edge *e = new Edge(this, tar);
    this->out_edges.emplace(e);
    if (tar)
    {
        tar->in_edges.emplace(e);
    }
}

void Port::add_input(Port *src)
{
    Edge *e = new Edge(src, this);
    this->in_edges.emplace(e);
    if (src)
    {
        src->out_edges.emplace(e);
    }
}

ostream &operator<<(ostream &output, const Port &p)
{
    output << p.name << "(";
    if (!p.in_edges.empty() && (*p.in_edges.begin())->src)
    {
        if ((*p.in_edges.begin())->src->own && (*p.in_edges.begin())->src->own->type <= _PO)
        {
            output << (*p.in_edges.begin())->src->own->name;
        }
        else
        {
            output << "n" << (*p.in_edges.begin())->src->id;
        }
    }
    else
    {
        if (p.own && p.own->type <= _PO)
        {
            output << p.own->name;
        }
        else
        {
            output << "n" << p.id;
        }
    }
    output << ")";
    return output;
}