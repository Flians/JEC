#include "util/util.h"

void Util::unique_element_in_vector(vector<Node *> &v)
{
    sort(v.begin(), v.end(), [](const Node *A, const Node *B) {
        if (A->id == B->id)
        {
            return A->outs.size() > B->outs.size();
        }
        else
        {
            return A->id < B->id;
        }
    });
    vector<Node *>::iterator vector_iterator = unique(v.begin(), v.end());
    if (vector_iterator != v.end())
    {
        v.erase(vector_iterator, v.end());
    }
}

vector<Node *> Util::vectors_intersection(vector<Node *> v1, vector<Node *> v2)
{
    vector<Node *> v;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
    return v;
}

Node *Util::find_node_by_name(vector<Node *> &nodes, const string &name)
{
    for (auto &node : nodes)
    {
        if (name == node->name)
        {
            return node;
        }
    }
    return nullptr;
}

bool Util::replace_node_by_name(vector<Node *> &nodes, Node *new_node)
{
    for (auto &node : nodes)
    {
        if (new_node->name == node->name)
        {
            node = new_node;
            return true;
        }
    }
    return false;
}

/** make a miter for golden and revised */
Netlist *Util::make_miter(Netlist *&golden, Netlist *&revised)
{
    if (!golden)
    {
        return revised;
    }
    else if (!revised)
    {
        return golden;
    }
    Netlist *miter = golden;
    if (golden->map_PIs.size() != revised->map_PIs.size() || golden->map_POs.size() != revised->map_POs.size())
    {
        JERROR("The golden Verilog has a different number of PIs and POs than the revised Verilog!");
    }
    auto iter = golden->map_PIs.begin(), iter_end = golden->map_PIs.end();
    // merge all inputs
    while (iter != iter_end)
    {
        // cout << iter->first << endl;
        auto pi = revised->map_PIs.find(iter->first);
        if (pi == revised->map_PIs.end())
        {
            JERROR("The input '" + iter->first + "' in the golden Verilog does not exist in the revised Verilog!");
        }
        vector<Node *>::iterator it = revised->gates[pi->second]->outs.begin();
        vector<Node *>::iterator it_end = revised->gates[pi->second]->outs.end();
        while (it != it_end)
        {
            if (!replace_node_by_name((*it)->ins, golden->gates[iter->second]))
            {
                JERROR("There are some troubles in util.make_miter!");
            }
            golden->gates[iter->second]->outs.emplace_back(*it);
            ++it;
        }
        delete revised->gates[pi->second];
        revised->gates[pi->second] = nullptr;
        ++iter;
    }
    revised->map_PIs.clear();
    // merge all outputs
    iter = golden->map_POs.begin();
    iter_end = golden->map_POs.end();
    while (iter != iter_end)
    {
        // cout << iter->first << endl;
        auto po = revised->map_POs.find(iter->first);
        if (po == revised->map_POs.end())
        {
            JERROR("The output '" + po->first + "' in the golden Verilog does not exist in the revised Verilog!");
        }
        golden->gates[iter->second]->type = _EXOR;
        for (auto &tg : revised->gates[po->second]->ins)
        {
            golden->gates[iter->second]->ins.emplace_back(tg);
            tg->outs.emplace_back(golden->gates[iter->second]);
        }
        delete revised->gates[po->second];
        revised->gates[po->second] = nullptr;
        ++iter;
    }
    revised->map_POs.clear();
    size_t num_gate = golden->get_num_gates();
    /** merge gates */
    for (auto gate : revised->gates)
    {
        if (gate)
        {
            gate->id = num_gate++;
            golden->gates.push_back(gate);
        }
    }
    golden->update_num_gates();
    revised->gates.clear();
    delete revised;
    revised = nullptr;
    golden = nullptr;
    return miter;
}

void Util::cycle_break(Netlist *netlist)
{
    vector<pair<Node *, Node *>> reversed;
    size_t num_gate = netlist->gates.size();
    /** indegree values and outdegree values for the nodes; mark for the nodes, inducing an ordering of the nodes. */
    int indeg[num_gate] = {0}, outdeg[num_gate] = {0}, mark[num_gate] = {0};
    /** list of source nodes and sink nodes. */
    queue<Node *> sources, sinks;
    /**
     * Updates indegree and outdegree values of the neighbors of the given node,
     * simulating its removal from the graph. the sources and sinks lists are
     * also updated.
     * 
     * @param node node for which neighbors are updated
     */
    auto updateNeighbors = [&indeg, &outdeg, &sources, &sinks](const Node *node) {
        for (Node *src : node->ins)
        {
            // exclude self-loops
            if (node == src)
            {
                continue;
            }
            int index = src->id;
            outdeg[index] -= 1;
            if (outdeg[index] <= 0 && indeg[index] > 0)
            {
                sinks.emplace(src);
            }
        }
        for (Node *tar : node->outs)
        {
            // exclude self-loops
            if (node == tar)
            {
                continue;
            }
            int index = tar->id;
            indeg[index] -= 1;
            if (indeg[index] <= 0 && outdeg[index] > 0)
            {
                sources.emplace(tar);
            }
        }
    };

    // obtain the indegree and outdegree
    for (auto node : netlist->gates)
    {
        indeg[node->id] = node->ins.size();
        outdeg[node->id] = node->outs.size();
        // collect sources and sinks
        if (outdeg[node->id] == 0)
        {
            sinks.emplace(node);
        }
        else if (indeg[node->id] == 0)
        {
            sources.emplace(node);
        }
    }
    // next rank values used for sinks and sources (from right and from left)
    int nextRight = -1, nextLeft = 1;

    // assign marks to all nodes
    vector<Node *> maxNodes;
    srand(time(0));
    size_t unprocessedNodeCount = num_gate;

    while (unprocessedNodeCount > 0)
    {
        // sinks are put to the right --> assign negative rank, which is later shifted to positive
        while (!sinks.empty())
        {
            Node *sink = sinks.front();
            sinks.pop();
            mark[sink->id] = nextRight--;
            updateNeighbors(sink);
            unprocessedNodeCount--;
        }

        // sources are put to the left --> assign positive rank
        while (!sources.empty())
        {
            Node *source = sources.front();
            sources.pop();
            mark[source->id] = nextLeft++;
            updateNeighbors(source);
            unprocessedNodeCount--;
        }

        // while there are unprocessed nodes left that are neither sinks nor sources...
        if (unprocessedNodeCount > 0)
        {
            int maxOutflow = INT_MIN;

            // find the set of unprocessed node (=> mark == 0), with the largest out flow
            for (Node *node : netlist->gates)
            {
                if (mark[node->id] == 0)
                {
                    int outflow = outdeg[node->id] - indeg[node->id];
                    if (outflow >= maxOutflow)
                    {
                        if (outflow > maxOutflow)
                        {
                            maxNodes.clear();
                            maxOutflow = outflow;
                        }
                        maxNodes.emplace_back(node);
                    }
                }
            }

            // randomly select a node from the ones with maximal outflow and put it left
            Node *maxNode = maxNodes[rand() % maxNodes.size()];
            mark[maxNode->id] = nextLeft++;
            updateNeighbors(maxNode);
            unprocessedNodeCount--;
        }
    }

    // shift negative ranks to positive; this applies to sinks of the graph
    size_t shiftBase = num_gate + 1;
    for (size_t index = 0; index < num_gate; index++)
    {
        if (mark[index] < 0)
        {
            mark[index] += shiftBase;
        }
    }

    // reverse edges that point left
    for (Node *node : netlist->gates)
    {
        // look at the node's outgoing edges
        for (Node *tar : node->outs)
        {
            if (mark[node->id] > mark[tar->id])
            {
                Node *last = nullptr;
                // no considering the splitters in the cycle
                while (node->type == SPL || node->type == SPL3)
                {
                    if (node->ins.size() == 1)
                    {
                        last = node;
                        node = node->ins[0];
                    }
                    else
                    {
                        JWARN("The splitter in the cycle has no input!");
                        last = nullptr;
                        break;
                    }
                }
                if (last == nullptr)
                    continue;
                reversed.emplace_back(make_pair(last, node));
                // reverse the edge
                last->outs.erase(find(last->outs.begin(), last->outs.end(), node));
                node->ins.erase(find(node->ins.begin(), node->ins.end(), last));
                last->ins.emplace_back(node);
                node->outs.emplace_back(last);
            }
        }
    }
    if (!reversed.empty())
    {
        vector<pair<Node *, Node *>> &reversed_edges = netlist->getProperty(PROPERTIES::CYCLE);
        reversed_edges.insert(reversed_edges.end(), reversed.begin(), reversed.end());
    }
}

void Util::cycle_restore(Netlist *netlist)
{
    if (!netlist->hasProperty(PROPERTIES::CYCLE))
        return;
    vector<pair<Node *, Node *>> &reversed = netlist->getProperty(PROPERTIES::CYCLE);
    for (auto &item : reversed)
    {
        // restore the edge
        item.first->ins.erase(find(item.first->ins.begin(), item.first->ins.end(), item.second));
        item.second->outs.erase(find(item.second->outs.begin(), item.second->outs.end(), item.first));
        item.first->outs.emplace_back(item.second);
        item.second->ins.emplace_back(item.first);
    }
    vector<pair<Node *, Node *>>().swap(reversed);
    netlist->removeProperty(PROPERTIES::CYCLE);
}

bool Util::path_balance(Netlist *netlist)
{
    if (netlist->isEmpty())
        return true;
    size_t num_gate = netlist->gates.size();
    double INTERVAL = 1.0 / num_gate;
    double level[num_gate];
    std::fill_n(level, num_gate, -1.0);
    queue<Node *> bfs;
    for (auto pi : netlist->map_PIs)
    {
        bfs.emplace(netlist->gates[pi.second]);
        level[pi.second] = 0;
    }
    while (!bfs.empty())
    {
        Node *cur = bfs.front();
        bfs.pop();
        for (Node *tar : cur->outs)
        {
            if (level[tar->id] == -1 || level[cur->id] >= level[tar->id])
            {
                if (tar->containCLK())
                {
                    level[tar->id] = floor(level[cur->id]) + 1;
                }
                else
                {
                    level[tar->id] = level[cur->id] + INTERVAL;
                }
                bfs.push(tar);
            }
        }
    }
    double maxLL = 0;
    bool vis[num_gate] = {0};
    for (auto po : netlist->map_POs)
    {
        vis[po.second] = 1;
        maxLL = max(level[po.second], maxLL);
        bfs.push(netlist->gates[po.second]);
    }
    while (!bfs.empty())
    {
        Node *cur = bfs.front();
        bfs.pop();
        for (Node *src : cur->ins)
        {
            if (level[src->id] == -1 || level[cur->id] <= level[src->id])
            {
                /*
                if (!layeredGraph.getProperty(InternalProperties.CYCLIC))
                    System.err.println("\nThere are some wrong in PathBalanceLayer.assignLayers");
                */
                if (src->containCLK())
                {
                    level[src->id] = floor(level[cur->id]) - (cur->containCLK() ? 1 : 0);
                }
                else
                {
                    level[src->id] = level[cur->id] - INTERVAL;
                }
                bfs.push(src);
            }
            if (!vis[src->id])
            {
                vis[src->id] = 1;
                bfs.push(src);
            }
        }
        if (cur->type == SPL || cur->type == SPL3)
        {
            double minChildLL = DBL_MAX;
            for (auto tar : cur->outs)
            {
                minChildLL = min(minChildLL, level[tar->id]);
            }
            level[cur->id] = minChildLL - INTERVAL;
        }
    }
    map<double, vector<Node *>> groups;
    bool path_balanced = true;
    for (size_t i = 0; i < num_gate; ++i)
    {
        for (auto src : netlist->gates[i]->ins)
        {
            if (level[i] - level[src->id] > 1 && src->type != _CLK)
            {
                JWARN("The path balance condition is not satisfied between node '" + src->name + "' and node '" + netlist->gates[i]->name + "'!");
                path_balanced = false;
            }
        }
        if (groups.find(level[i]) == groups.end())
        {
            groups.insert(make_pair(level[i], vector<Node *>()));
        }
        groups[level[i]].emplace_back(netlist->gates[i]);
    }
    vector<vector<Node *>> &layers = netlist->getProperty(PROPERTIES::LAYERS);
    for (auto item : groups)
    {
        layers.emplace_back(item.second);
    }
    groups.clear();
    if (!path_balanced)
    {
        netlist->setProperty<bool>(PROPERTIES::PATH_BALANCED, false);
    }
    return path_balanced;
}
