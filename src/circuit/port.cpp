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
    for (auto &in : this->in_edges)
    {
        delete in;
    }
    this->in_edges.clear();
    for (auto &out : this->out_edges)
    {
        delete out;
    }
    this->out_edges.clear();
    this->own = nullptr;
}