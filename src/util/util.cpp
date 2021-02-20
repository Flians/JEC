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
    for (size_t i = 0, len = nodes.size(); i < len; ++i)
    {
        auto &node = nodes[i];
        if (name == node->name)
        {
            return node;
        }
    }
    return nullptr;
}

bool Util::replace_node_by_name(vector<Node *> &nodes, Node *new_node)
{
    for (size_t i = 0, len = nodes.size(); i < len; ++i)
    {
        auto &node = nodes[i];
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
        for (size_t i = 0, len = pi->second->outs.size(); i < len; ++i)
        {
            auto &it = pi->second->outs[i];
            if (!replace_node_by_name(it->ins, iter->second))
            {
                JERROR("There are some troubles in util.make_miter!");
            }
            iter->second->outs.emplace_back(it);
            ++it;
        }
        revised->gates[pi->second->id] = nullptr;
        delete pi->second;
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
        iter->second->type = _EXOR;
        for (size_t i = 0, num_po_ins = po->second->ins.size(); i < num_po_ins; ++i)
        {
            auto &tg = po->second->ins[i];
            iter->second->ins.emplace_back(tg);
            tg->outs.emplace_back(iter->second);
        }
        revised->gates[po->second->id] = nullptr;
        delete po->second;
        ++iter;
    }
    revised->map_POs.clear();
    size_t num_gate = golden->get_num_gates();
    /** merge gates */
    for (size_t i = 0, num_revised_gates = revised->gates.size(); i < num_revised_gates; ++i)
    {
        auto &gate = revised->gates[i];
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
    const size_t num_gate = netlist->get_num_gates();
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
    auto updateNeighbors = [&indeg, &outdeg, &mark, &sources, &sinks](const Node *node) {
        for (size_t i = 0, num_node_ins = node->ins.size(); i < num_node_ins; ++i)
        {
            auto &src = node->ins[i];
            // exclude self-loops
            if (node == src || mark[src->id] != 0)
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
        for (size_t i = 0, num_node_outs = node->outs.size(); i < num_node_outs; ++i)
        {
            auto &tar = node->outs[i];
            // exclude self-loops
            if (node == tar || mark[tar->id] != 0)
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
    for (size_t i = 0; i < num_gate; ++i)
    {
        auto &node = netlist->gates[i];
        indeg[node->id] = count_if(node->ins.begin(), node->ins.end(), [&node](const Node *src) { return src != node; });
        outdeg[node->id] = count_if(node->outs.begin(), node->outs.end(), [&node](const Node *tar) { return tar != node; });
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
    int unprocessedNodeCount = num_gate;

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
            for (size_t i = 0; i < num_gate; ++i)
            {
                auto &node = netlist->gates[i];
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
    for (size_t i = 0; i < num_gate; ++i)
    {
        auto &node = netlist->gates[i];
        // look at the node's outgoing edges
        for (size_t j = 0, num_node_outs = node->outs.size(); j < num_node_outs; ++j)
        {
            Node *cur = node;
            Node *next = cur->outs[j];
            if (mark[cur->id] > mark[next->id])
            {
                // no considering the splitters in the cycle
                while (cur->type == SPL || cur->type == SPL3)
                {
                    if (cur->ins.size() == 1)
                    {
                        next = cur;
                        cur = cur->ins[0];
                    }
                    else
                    {
                        JWARN("The splitter in the cycle has no input!");
                        next = nullptr;
                        break;
                    }
                }
                if (next == nullptr)
                    continue;
                if (cur == node)
                {
                    --num_node_outs;
                    --j;
                }
                reversed.emplace_back(cur, next);
                // reverse the edge
                auto _find = find(next->ins.begin(), next->ins.end(), cur);
                if (_find != next->ins.end())
                {
                    next->ins.erase(_find);
                }
                _find = find(cur->outs.begin(), cur->outs.end(), next);
                if (_find != cur->outs.end())
                {
                    cur->outs.erase(_find);
                }
                next->outs.emplace_back(cur);
                cur->ins.emplace_back(next);
                JINFO("The edge betweeen '" + cur->name + "' and '" + next->name + "' is reversed.");
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
    for (size_t i = 0, num_reversed = reversed.size(); i < num_reversed; ++i)
    {
        auto &item = reversed[i];
        // restore the edge
        item.first->ins.erase(find(item.first->ins.begin(), item.first->ins.end(), item.second));
        item.second->outs.erase(find(item.second->outs.begin(), item.second->outs.end(), item.first));
        item.first->outs.emplace_back(item.second);
        item.second->ins.emplace_back(item.first);
        JINFO("The edge betweeen '" + item.first->name + "' and '" + item.second->name + "' is restored.");
    }
    vector<pair<Node *, Node *>>().swap(reversed);
    netlist->removeProperty(PROPERTIES::CYCLE);
}

bool Util::path_balance(Netlist *netlist)
{
    if (netlist->isEmpty())
        return true;
    Util::cycle_break(netlist);
    size_t num_gate = netlist->get_num_gates();
    double INTERVAL = 1.0 / num_gate, maxLL = 0;
    double level[num_gate];
    std::fill_n(level, num_gate, -1.0);
    queue<Node *> bfs;
    for (auto &pi : netlist->map_PIs)
    {
        if (pi.second->type != _CLK)
        {
            bfs.emplace(pi.second);
        }
        level[pi.second->id] = 0;
    }
    while (!bfs.empty())
    {
        Node *cur = bfs.front();
        bfs.pop();
        maxLL = max(level[cur->id], maxLL);
        for (size_t i = 0, num_cur_outs = cur->outs.size(); i < num_cur_outs; ++i)
        {
            auto &tar = cur->outs[i];
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
    bool vis[num_gate] = {0};
    for (auto &po : netlist->map_POs)
    {
        vis[po.second->id] = 1;
        level[po.second->id] = maxLL;
        bfs.emplace(po.second);
    }
    bool has_cycle = netlist->hasProperty(PROPERTIES::CYCLE);
    while (!bfs.empty())
    {
        Node *cur = bfs.front();
        bfs.pop();
        if (cur->type == SPL || cur->type == SPL3)
        {
            double minChildLL = DBL_MAX;
            for (size_t i = 0, num_cur_outs = cur->outs.size(); i < num_cur_outs; ++i)
            {
                auto &tar = cur->outs[i];
                minChildLL = min(minChildLL, level[tar->id]);
            }
            level[cur->id] = minChildLL - INTERVAL;
        }
        for (size_t i = 0, num_cur_ins = cur->ins.size(); i < num_cur_ins; ++i)
        {
            auto &src = cur->ins[i];
            if (level[src->id] == -1 || level[cur->id] <= level[src->id])
            {
                if (!has_cycle)
                {
                    JWARN("There are some troubles in util.path_balanced");
                }
                if (src->containCLK())
                {
                    level[src->id] = floor(level[cur->id]) - (cur->containCLK() ? 1 : 0);
                }
                else
                {
                    level[src->id] = level[cur->id] - INTERVAL;
                }
                bfs.emplace(src);
            }
            else if (!vis[src->id])
            {
                bfs.emplace(src);
            }
            vis[src->id] = 1;
        }
    }
    std::map<double, vector<Node *>> groups;
    bool path_balanced = true;
    for (size_t i = 0; i < num_gate; ++i)
    {
        auto &cur = netlist->gates[i];
        for (size_t i = 0, num_cur_ins = cur->ins.size(); i < num_cur_ins; ++i)
        {
            auto &src = cur->ins[i];
            if (level[i] - level[src->id] > 1 && src->type != _CLK && (cur->type != _EXOR || cur->type != _PO))
            {
                JWARN("The path balance condition is not satisfied between node '" + src->name + "' and node '" + cur->name + "'!");
                path_balanced = false;
            }
        }
        auto _find = groups.find(level[i]);
        if (_find == groups.end())
        {
            auto item = vector<Node *>();
            item.emplace_back(cur);
            groups.emplace(level[i], item);
        }
        else
        {
            _find->second.emplace_back(cur);
        }
    }
    vector<vector<Node *>> &layers = netlist->getProperty(PROPERTIES::LAYERS);
    for (auto &item : groups)
    {
        layers.emplace_back(item.second);
    }
    groups.clear();
    netlist->setProperty<bool>(PROPERTIES::PATH_BALANCED, path_balanced);
    Util::cycle_restore(netlist);
    return path_balanced;
}
