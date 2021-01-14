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
    for (size_t i = 0, len = this->edges.size(); i < len; ++i)
    {
        if (this->edges[i])
        {
            if (this->edges[i]->src == this)
            {
                if (this->edges[i]->tar)
                    this->edges[i]->tar->edges.erase(find(this->edges[i]->tar->edges.begin(), this->edges[i]->tar->edges.end(), this->edges[i]));
            }
            else
            {
                if (this->edges[i]->src)
                    this->edges[i]->src->edges.erase(find(this->edges[i]->src->edges.begin(), this->edges[i]->src->edges.end(), this->edges[i]));
            }
            delete this->edges[i];
        }
    }
    this->own = nullptr;
    vector<Edge *>().swap(this->edges);
}