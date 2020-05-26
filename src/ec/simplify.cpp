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

void simplify::id_reassign(vector<node *> *PIs)
{
    if (PIs->empty())
    {
        cout << "PIs is empty in simplify.id_reassign" << endl;
        return;
    }
    vector<bool> visit(init_id, 0);
    queue<node *> bfs_record;
    int i = 0;
    for (auto pi : (*PIs))
    {
        visit[pi->id] = true;
        pi->id = i++;
        bfs_record.push(pi);
    }
    while (!bfs_record.empty())
    {
        node *item = bfs_record.front();
        if (item->outs)
        {
            for (auto out : (*item->outs))
            {
                if (!visit[out->id])
                {
                    visit[out->id] = true;
                    out->id = i++;
                    bfs_record.push(out);
                }
            }
        }
        bfs_record.pop();
    }
    init_id = i;
    vector<bool>().swap(visit);
}

vector<vector<node *> *> *simplify::layer_assignment(vector<node *> *PIs)
{
    vector<vector<node *> *> *layers = new vector<vector<node *> *>;
    if (PIs->empty())
    {
        cout << "PIs is empty in simplify.layer_assignment" << endl;
        return layers;
    }
    layers->push_back(PIs);
    int i = 0;
    node *clk;
    for (i = 0; i<PIs->size(); i++) {
        if (PIs->at(i)->name.find("clk") != string::npos) {
            clk = PIs->at(i);
            swap(PIs->at(0), PIs->at(i));
            break;
        }
    }
    i=0;
    vector<int> visit(init_id, 0);
    vector<int> logic_depth(init_id, 0);
    // layer assignment, and calculate the logic depth of each node
    while (i < layers->size())
    {
        vector<node *> *layer = new vector<node *>;
        for (int j = 0; j < layers->at(i)->size(); j++)
        {
            if (layers->at(i)->at(j)->outs)
            {
                for (int k = 0; k < layers->at(i)->at(j)->outs->size(); k++)
                {
                    visit[layers->at(i)->at(j)->outs->at(k)->id]++;
                    logic_depth[layers->at(i)->at(j)->outs->at(k)->id] = max(logic_depth[layers->at(i)->at(j)->id] + 1, logic_depth[layers->at(i)->at(j)->outs->at(k)->id]);
                    if (layers->at(i)->at(j)->outs->at(k)->ins->size() == visit[layers->at(i)->at(j)->outs->at(k)->id])
                        layer->push_back(layers->at(i)->at(j)->outs->at(k));
                }
            }
        }
        if (!layer->empty())
        {
            layers->push_back(layer);
        }
        i++;
    }
    vector<int>().swap(visit);

    int reduceDFF = 0;
    // path balancing, and reducing the number of DFF
    for (i = 0; i < layers->size(); i++)
    {
        for (int j = 0; j < layers->at(i)->size(); j++)
        {
            if (layers->at(i)->at(j)->outs && layers->at(i)->at(j)->outs->size() > 0)
            {
                if (layers->at(i)->at(j)->cell == IN && layers->at(i)->at(j)->name.find("clk") != string::npos)
                    continue;
                vector<int> child_DFF;
                vector<int> add_DFF;
                // find all children which are DFF, and find all children which do not meet the path balancing
                for (int k = 0; k < layers->at(i)->at(j)->outs->size(); k++)
                {
                    if (logic_depth[layers->at(i)->at(j)->outs->at(k)->id] > i + 1)
                    {
                        add_DFF.push_back(k);
                    }
                    else if (logic_depth[layers->at(i)->at(j)->outs->at(k)->id] < i + 1)
                    {
                        cout << "The logical depth of the parent node is less than its child nodes: " << layers->at(i)->at(j)->outs->at(k)->name << ", " << i << endl;
                    }
                    else
                    {
                        if (layers->at(i)->at(j)->outs->at(k)->cell == DFF)
                            child_DFF.push_back(k);
                    }
                }
                for (int d = child_DFF.size() - 2; d >= 0; d--)
                {
                    // grandson.ins.push(son)
                    layers->at(i)->at(j)->outs->at(child_DFF[d])->outs->at(0)->ins->push_back(layers->at(i)->at(j)->outs->at(child_DFF[child_DFF.size() - 1]));
                    // son.outs.push(grandson)
                    layers->at(i)->at(j)->outs->at(child_DFF[child_DFF.size() - 1])->outs->push_back(layers->at(i)->at(j)->outs->at(child_DFF[d])->outs->at(0));
                    delete layers->at(i)->at(j)->outs->at(child_DFF[d]);
                    child_DFF[child_DFF.size() - 1]--;
                    reduceDFF++;
                }
                if (add_DFF.size() > 0)
                {
                    node *father;
                    if (child_DFF.size() > 0)
                    {
                        father = layers->at(i)->at(j)->outs->at(child_DFF[child_DFF.size() - 1]);
                    }
                    else
                    {
                        reduceDFF--;
                        father = new node(layers->at(i)->at(j)->name + "_child", DFF);
                        father->ins = new vector<node *>[2];
                        father->outs = new vector<node *>[1];
                        father->ins->push_back(clk);
                        father->ins->push_back(layers->at(i)->at(j));
                        layers->at(i)->at(j)->outs->push_back(father);
                        layers->at(i + 1)->push_back(father);
                    }
                    for (int d = add_DFF.size() - 1; d >= 0; d--)
                    {
                        // grandson.ins.push(father)
                        layers->at(i)->at(j)->outs->at(add_DFF[d])->ins->push_back(father);
                        // father.outs.push(grandson)
                        father->outs->push_back(layers->at(i)->at(j)->outs->at(add_DFF[d]));
                        // grandson.ins.erase(grandpa)
                        layers->at(i)->at(j)->outs->at(add_DFF[d])->ins->erase(find(
                            layers->at(i)->at(j)->outs->at(add_DFF[d])->ins->begin(), layers->at(i)->at(j)->outs->at(add_DFF[d])->ins->end(), 
                            layers->at(i)->at(j)));
                        // grandpa.ins.erase(grandson)
                        layers->at(i)->at(j)->outs->erase(layers->at(i)->at(j)->outs->begin() + add_DFF[d]);
                    }
                }
                vector<int>().swap(child_DFF);
                vector<int>().swap(add_DFF);
            }
            else if (!layers->at(i)->at(j)->ins || layers->at(i)->at(j)->ins->empty())
            {
                layers->at(i)->erase(layers->at(i)->begin() + j);
                j--;
            }
        }
    }
    cout << "The number of DFF reduction is " << reduceDFF << endl;
    return layers;
}