#include "circuit/port.h"

const std::unordered_map<string, PType> Str_PType = {
    {"din", _IN},
    {"dout", _OUT},
    {"din_out", _INOUT},
    {"undefined", _UNDEFINED_P}};

const std::unordered_map<PType, string, EnumClassHash> PType_Str = {
    {_IN, "din"},
    {_OUT, "dout"},
    {_INOUT, "din_out"},
    {_UNDEFINED_P, "undefined"}};

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