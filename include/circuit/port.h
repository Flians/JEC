#ifndef _PORT_H_
#define _PORT_H_

#include "util/libhead.h"
#include "circuit/node.h"
#include "circuit/edge.h"

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

class Port : virtual public Point<> // position
{
public:
    string name;
    PType type;
    Node *own;
    vector<Edge *> edges;

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