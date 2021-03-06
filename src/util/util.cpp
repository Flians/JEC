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
        auto golden_pi = iter->second->outs.begin()->second;
        // cout << iter->first << endl;
        auto pi = revised->map_PIs.find(iter->first);
        if (pi == revised->map_PIs.end())
        {
            JERROR("The input '", iter->first, "' in the golden Verilog does not exist in the revised Verilog!");
        }
        for (auto &out : pi->second->outs)
        {
            for (auto &o_edge : out.second->out_edges)
            {
                o_edge->set_source(golden_pi);
            }
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
        auto golden_po = iter->second->ins.begin()->second;
        // cout << iter->first << endl;
        auto po = revised->map_POs.find(iter->first);
        if (po == revised->map_POs.end())
        {
            JERROR("The output '", po->first, "' in the golden Verilog does not exist in the revised Verilog!");
        }
        iter->second->type = _EXOR;
        for (auto &in : po->second->outs)
        {
            for (auto &i_edge : in.second->in_edges)
            {
                i_edge->set_target(golden_po);
            }
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
    vector<Edge *> reversed;
    size_t num_gate = netlist->get_num_gates();
    /** indegree values and outdegree values for the nodes */
    int indeg[num_gate] = {0}, outdeg[num_gate] = {0};
    /** mark for the nodes whether */
    bool mark[num_gate] = {0};
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
        auto predecessors = node->get_predecessors();
        for (auto &src : predecessors)
        {
            // exclude self-loops
            if (node == src || mark[src->id])
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
        auto successors = node->get_successors();
        for (auto &tar : successors)
        {
            // exclude self-loops
            if (node == tar || mark[tar->id])
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
        indeg[node->id] = node->get_indegree(true, false);
        outdeg[node->id] = node->get_outdegree(false);
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

    // assign marks to all nodes
    int unprocessedNodeCount = num_gate;
    while (unprocessedNodeCount > 0)
    {
        // sinks are put to the right --> assign negative rank, which is later shifted to positive
        while (!sinks.empty())
        {
            Node *sink = sinks.front();
            sinks.pop();
            mark[sink->id] = 1;
            updateNeighbors(sink);
            unprocessedNodeCount--;
        }

        // sources are put to the left --> assign positive rank
        while (!sources.empty())
        {
            Node *source = sources.front();
            sources.pop();
            mark[source->id] = 1;
            updateNeighbors(source);
            unprocessedNodeCount--;
        }

        // while there are unprocessed nodes left that are neither sinks nor sources...
        if (unprocessedNodeCount > 0)
        {
            // find the set of unprocessed node (=> mark == 0), with the largest out flow
            for (size_t i = 0; i < num_gate; ++i)
            {
                auto &node = netlist->gates[i];
                if (mark[node->id] == 0 && (node->type == CB || node->type == CB3))
                {
                    // reverse the edge
                    auto &edge = node->outs.begin()->second->out_edges[0];
                    reversed.emplace_back(edge);
                    JINFO("The edge <", edge->get_source()->name, ",", edge->get_target()->name, "> is reversed.");
                    edge->reverse();
                    // update neighbors
                    mark[node->id] = 1;
                    updateNeighbors(node);
                    unprocessedNodeCount--;
                    break;
                }
            }
        }
    }

    if (!reversed.empty())
    {
        vector<Edge *> &reversed_edges = netlist->getProperty(PROPERTIES::REVERSED);
        reversed_edges.insert(reversed_edges.end(), reversed.begin(), reversed.end());
    }
}

void Util::cycle_restore(Netlist *netlist)
{
    if (!netlist->hasProperty(PROPERTIES::REVERSED))
        return;
    vector<Edge *> &reversed = netlist->getProperty(PROPERTIES::REVERSED);
    for (auto &item : reversed)
    {
        // restore the edge
        item->reverse();
        JINFO("The edge <", item->get_source()->name, ",", item->get_target()->name, "> is restored.");
    }
    vector<Edge *>().swap(reversed);
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
        auto successors = cur->get_successors();
        for (std::size_t i = 0, num_cur_suc = successors.size(); i < num_cur_suc; ++i)
        {
            auto &tar = successors[i];
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
                bfs.emplace(tar);
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
    bool has_cycle = netlist->hasProperty(PROPERTIES::REVERSED);
    while (!bfs.empty())
    {
        Node *cur = bfs.front();
        bfs.pop();
        if (cur->type == SPL || cur->type == SPL3)
        {
            double minChildLL = DBL_MAX;
            for (auto &out : cur->outs)
            {
                for (auto &o_edge : out.second->out_edges)
                {
                    minChildLL = min(minChildLL, level[o_edge->get_target()->id]);
                }
            }
            level[cur->id] = minChildLL - INTERVAL;
        }
        auto predecessors = cur->get_predecessors();
        for (auto &src : predecessors)
        {
            if (level[src->id] == -1 || level[cur->id] <= level[src->id])
            {
                if (!has_cycle)
                {
                    JWARN("There are some troubles in util.path_balance.");
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
        auto predecessors = cur->get_predecessors();
        for (std::size_t i = 0, num_cur_pre = predecessors.size(); i < num_cur_pre; ++i)
        {
            auto src = predecessors[i];
            if (level[i] - level[src->id] > 1 && src->type != _CLK && (cur->type != _EXOR || cur->type != _PO))
            {
                JWARN("The path balance condition is not satisfied between node '", src->name, "' and node '", cur->name, "'!");
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
