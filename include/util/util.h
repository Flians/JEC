#ifndef _UTIL_H_
#define _UTIL_H_

#include <memory>
#include <algorithm>
#include "circuit/node.h"
#include "circuit/netlist.h"

class Node;
class Netlist;

class Util
{
private:
    Util();
    Util(const Util &);
    Util &operator=(const Util &);
    ~Util();

public:
    /** remove duplicate nodes */
    static void unique_element_in_vector(vector<Node *> &v);

    /** intersection of two vectors */
    template <typename T = Node *>
    static vector<Node *> vectors_intersection(vector<T> v1, vector<T> v2)
    {
        vector<T> v;
        sort(v1.begin(), v1.end());
        sort(v2.begin(), v2.end());
        set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));
        return v;
    }
    /** intersection of two maps */
    template <typename T = Node *>
    static std::unordered_map<std::string, T> map_intersection(std::unordered_map<std::string, T> v1, std::unordered_map<std::string, T> v2)
    {
        std::unordered_map<std::string, T> v;
        for (auto &item : v1)
        {
            if (v2.find(item.first) != v2.end())
            {
                v.emplace(item);
            }
        }
        return v;
    }

    template <typename T = Node *>
    static bool contained(std::unordered_map<std::string, T> child_map, std::unordered_map<std::string, T> parent_map)
    {
        for (auto &item : child_map)
        {
            if (parent_map.find(item.first) == parent_map.end())
            {
                return false;
            }
        }
        return true;
    }

    /** clean vector<*>, and release the space */
    template <typename T = Node>
    static void cleanVP(vector<T *> &vp)
    {
        if (vp.empty())
            return;
        typename vector<T *>::iterator it = vp.begin();
        int len = vp.size();
        for (int i = 0; i < len; ++i, ++it)
        {
            if (*it)
            {
                delete *it;
                *it = nullptr;
            }
        }
        vector<T *>().swap(vp);
    }

    // find the node from vector<node *> *nodes by name
    static Node *find_node_by_name(vector<Node *> &nodes, const string &name);

    // replace the node from vector<node *> *nodes with the new_node, which the name of this node is same as the new_node
    static bool replace_node_by_name(vector<Node *> &nodes, Node *new_node);

    /** 
     * make a miter for the golden netlist and the revised netlist
     * @return the miter
     */
    static Netlist *make_miter(Netlist *&golden, Netlist *&revised);

    /**
     * break the cycles, and store the reversed edge into properties[CYCLE]
     * @param netlist the pointer of the netlist
     */
    static void cycle_break(Netlist *netlist);

    /**
     * restore the cycles, and restore the reversed edge from properties[CYCLE]
     * @param netlist the pointer of the netlist
     */
    static void cycle_restore(Netlist *netlist);

    /**
     * calculate the logic level of each node, and judge whether the netlist is path balanced
     * store the layers group by the logic level into properties[LAYERS]
     * @param netlist the pointer of the netlist
     * @return whether the netlist is path balanced
     */
    static bool path_balance(Netlist *netlist);
};

#endif