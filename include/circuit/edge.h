#ifndef _EDGE_H_
#define _EDGE_H_

#include "circuit/port.h"
#include "circuit/node.h"
#include "util/libhead.h"
#include "util/_point.hpp"
#include "util/_properties.h"
#include "util/_map_property.hpp"

class Port;
class Node;

class Edge : virtual public MapProperty
{
public:
    Port *src;
    Port *tar;
    vector<Point<double>> bend_points;

public:
    Edge() : src(nullptr), tar(nullptr){};
    Edge(Port *_src, Port *_tar) : src(_src), tar(_tar){};
    ~Edge();

    string get_name() const;
    Node *get_source() const;
    Node *get_target() const;
    /**
     * Sets the source port of this edge and adds itself to the port's out-edges. If the edge previously had another
     * source, it is removed from the original port's out-edges.
     * 
     * @param new_src the source port to set
     */
    void set_source(Port *new_src);
    /**
     * Sets the target port of this edge and adds itself to the port's in-edges. If the edge previously had another
     * target, it is removed from the original port's in-edges. 
     * 
     * @param new_tar the target port to set
     */
    void set_target(Port *new_tar);
    /**
     * reverses the edge, including its bend points.
     * an edge that was marked as being reversed is then unmarked, and the other way around
     */
    void reverse();

    friend ostream &operator<<(ostream &output, const Edge &p);
};

#endif