#ifndef _PORT_H_
#define _PORT_H_

#include "circuit/node.h"
#include "circuit/edge.h"
#include "util/libhead.h"
#include "util/_point.hpp"
#include "util/_properties.h"
#include "util/_map_property.hpp"

class Edge;

// all port types
enum PType
{
    _IN = 0,
    _OUT = 1,
    _INOUT = 2,
    _UNDEFINED_P = 3,
};

extern const std::unordered_map<string, PType> Str_PType;
extern const std::unordered_map<PType, string, EnumClassHash> PType_Str;

class Port : virtual public MapProperty
{
public:
    string name;
    PType type;
    size_t id;
    Node *own;
    vector<Edge *> in_edges;
    vector<Edge *> out_edges;
    Point<> position;

public:
    Port() : name(nullptr), type(_UNDEFINED_P), own(nullptr){};
    Port(string _name, PType _type, Node *_own) : name(_name), type(_type), own(_own){};
    Port(PType _type, Node *_own) : type(_type), own(_own)
    {
        this->name = PType_Str.at(_type);
    };
    ~Port();
};

#endif