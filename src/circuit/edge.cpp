#include "circuit/edge.h"

Edge::~Edge()
{
    this->set_source(nullptr);
    this->set_target(nullptr);
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

void Edge::set_source(Port *new_src)
{
    if (!this->src)
    {
        this->src->out_edges.erase(remove_if(this->src->out_edges.begin(), this->src->out_edges.end(), [this](Edge *x) { return x == this; }), this->src->out_edges.end());
    }

    this->src = new_src;

    if (this->src)
    {
        this->src->out_edges.emplace_back(this);
    }
}

void Edge::set_target(Port *new_tar)
{
    if (this->tar)
    {
        this->tar->in_edges.erase(remove_if(this->tar->in_edges.begin(), this->tar->in_edges.end(), [this](Edge *x) { return x == this; }), this->tar->in_edges.end());
    }

    this->tar = new_tar;

    if (this->tar)
    {
        this->tar->in_edges.emplace_back(this);
    }
}

void Edge::reverse()
{
    Port *old_src = this->src;
    this->set_source(this->tar);
    this->set_target(old_src);

    bool reversed = this->getProperty(PROPERTIES::REVERSED);
    this->setProperty(PROPERTIES::REVERSED, !reversed);

    std::reverse(this->bend_points.begin(), this->bend_points.end());
}
