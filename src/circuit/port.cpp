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
    for (std::size_t i = 0; i < in_size; ++i)
    {
        auto &in_e = this->in_edges[i];
        in_e->set_source(nullptr);
        in_e->tar = nullptr;
        delete in_e;
    }
    std::vector<Edge *>().swap(this->in_edges);

    std::size_t out_size = this->out_edges.size();
    for (std::size_t i = 0; i < out_size; ++i)
    {
        auto &out_e = this->out_edges[i];
        out_e->src = nullptr;
        out_e->set_target(nullptr);
        delete out_e;
    }
    std::vector<Edge *>().swap(this->out_edges);

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
    this->out_edges.emplace_back(e);
    if (tar)
    {
        tar->in_edges.emplace_back(e);
    }
}

void Port::add_input(Port *src)
{
    Edge *e = new Edge(src, this);
    this->in_edges.emplace_back(e);
    if (src)
    {
        src->out_edges.emplace_back(e);
    }
}

ostream &operator<<(ostream &output, const Port &p)
{
    output << p.name << "(";
    if (p.hasProperty(PROPERTIES::NET_NAME))
    {
        output << const_cast<Port &>(p).getProperty(PROPERTIES::NET_NAME);
    }
    else
    {
        output << "n" << (p.type == _IN ? (*p.in_edges.begin())->src->id : p.id);
    }
    output << ")";
    return output;
}