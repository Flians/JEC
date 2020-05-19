#include "simplify.h"

simplify::simplify(/* args */)
{
}

simplify::~simplify()
{
}

bool simplify::replace_node_by_id(vector<node *> *nodes, node *new_node, int id)
{
    for (auto &node : *nodes)
    {
        if (id == node->id)
        {
            node = new_node;
            return true;
        }
    }
    return false;
}

/**
 * clean all wires, bufs and splitters
 * from PIs to POs
 */
void simplify::clean_wire_buf(vector<node *> *miter)
{
    if (!miter || miter->size() == 0)
        return;
    int len = miter->size();
    for (int i = 0; i < len; ++i)
    {
        node *pi = miter->at(i);
        if (!(pi->outs) || pi->outs->size() == 0)
        {
            continue;
        }

        if (pi->cell == WIRE || pi->cell == BUF ||
            pi->cell == SPL || pi->cell == SPL3)
        {
            if (pi->ins->size() != 1)
            {
                cerr << pi->name << " WIRE have none or more one inputs in simplify.clean_wire_buf!" << endl;
                exit(-1);
            }
            cout << pi->name << " " << Str_Value[pi->cell] << endl;
            node *tin = pi->ins->at(0);
            vector<node *>::iterator it = pi->outs->begin();
            vector<node *>::iterator it_end = pi->outs->end();
            while (it != it_end)
            {
                vector<node *>::iterator temp_in = (*it)->ins->begin();
                vector<node *>::iterator temp_in_end = (*it)->ins->end();
                while (temp_in != temp_in_end)
                {
                    if (pi == (*temp_in))
                    {
                        (*temp_in) = tin;
                        break;
                    }
                    temp_in++;
                }
                if (temp_in != temp_in_end)
                {
                    tin->outs->push_back(*it);
                }
                else
                {
                    cerr << "There are some wrong in" << pi->name << endl;
                    exit(-1);
                }
                ++it;
            }
            vector<node *>().swap(*(pi->outs));
            delete pi;
            clean_wire_buf(tin->outs);
        }
        // this node has been visited.
        else if (pi->cell != IN && pi->outs->at(0)->cell != WIRE)
        {
            continue;
        }
        else
        {
            clean_wire_buf(pi->outs);
        }
    }
}