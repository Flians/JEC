#include "circuit/edge.h"

Edge::~Edge()
{
    this->src = nullptr;
    this->tar = nullptr;
    vector<Point<>>().swap(this->bend_points);
}

ostream &operator<<(ostream &output, const Edge &e)
{
    output << e.get_name() << endl;
    return output;
}

string Edge::get_name() const
{
    string name("<");
    name.append(this->src ? this->src->name : "null");
    name.append(" -> ");
    name.append(this->tar ? this->tar->name : "null");
    name.append(">");
    return name;
}