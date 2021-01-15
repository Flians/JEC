#include "circuit/edge.h"

Edge::~Edge()
{
    this->src = nullptr;
    this->tar = nullptr;
    vector<Point<>>().swap(this->bend_points);
}

ostream &operator<<(ostream &output, const Edge &e)
{
    output << "<" << (e.src ? e.src->name : "null")
           << " -> " << (e.tar ? e.tar->name : "null")
           << ">" << endl;
    return output;
}