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
    for (size_t i = 0, len = this->in_edges.size(); i < len; ++i)
    {
        if (this->in_edges[i])
        {
            if (this->in_edges[i]->src)
                this->in_edges[i]->src->out_edges.erase(find(this->in_edges[i]->src->out_edges.begin(), this->in_edges[i]->src->out_edges.end(), this->in_edges[i]));

            delete this->in_edges[i];
        }
    }
    vector<Edge *>().swap(this->in_edges);
    for (size_t i = 0, len = this->out_edges.size(); i < len; ++i)
    {
        if (this->out_edges[i])
        {
            if (this->out_edges[i]->tar)
                this->out_edges[i]->tar->in_edges.erase(find(this->out_edges[i]->tar->in_edges.begin(), this->out_edges[i]->tar->in_edges.end(), this->out_edges[i]));

            delete this->in_edges[i];
        }
    }
    this->own = nullptr;
}