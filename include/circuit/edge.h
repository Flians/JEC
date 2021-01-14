#ifndef _EDGE_H_
#define _EDGE_H_

#include "util/libhead.h"
#include "circuit/port.h"

class Port;

class Edge
{
public:
    Port *src;
    Port *tar;
    vector<Point<>> bend;

public:
    Edge() : src(nullptr), tar(nullptr){};
    Edge(Port *_src, Port *_tar) : src(_src), tar(_tar){};
    ~Edge();

    friend ostream &operator<<(ostream &output, const Edge &p);
};

#endif