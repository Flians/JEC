#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include "circuit/node.h"
#include "util/_map_property.hpp"

class Node;
class Edge;

class PROPERTIES final
{
private:
    PROPERTIES();
    PROPERTIES(const PROPERTIES &);
    PROPERTIES &operator=(const PROPERTIES &);
    ~PROPERTIES();

public:
    const static Property<bool> CYCLE;
    const static Property<vector<Edge *>> REVERSED;       // reversed edges: vector<pair<Node *, Node *>> source -> target
    const static Property<bool> CLEAN_SPL;                // bool
    const static Property<bool> CLEAN_DFF;                // bool
    const static Property<vector<vector<Node *>>> LAYERS; // vector<vector<Node*>>
    const static Property<bool> PATH_BALANCED;            // bool
    const static Property<bool> EQ;                       // bool
    const static Property<std::string> NET_NAME;          // string
};

#endif
