#ifndef _PORT_H_
#define _PORT_H_

#include <list>

#include "circuit/node.h"
#include "circuit/edge.h"
#include "util/libhead.h"
#include "util/_point.hpp"
#include "util/_properties.h"
#include "util/_map_property.hpp"

class Edge;
class Node;

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
    std::string name;
    PType type;
    Node *own;
    std::size_t id;
    std::vector<Edge *> in_edges;
    std::vector<Edge *> out_edges;
    Point<> position;

public:
    Port() : name(nullptr), type(_UNDEFINED_P), own(nullptr){};
    Port(const string &_name, const PType &_type, Node *_own = nullptr, std::size_t _id = 0) : name(_name), type(_type), own(_own), id(_id){};
    Port(const PType &_type, Node *_own = nullptr, std::size_t _id = 0) : name(PType_Str.at(_type)), type(_type), own(_own), id(_id) {}
    ~Port();

    void add_output(Port *tar);
    void add_input(Port *src);
    friend ostream &operator<<(ostream &output, const Port &p);
};

#endif