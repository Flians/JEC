#ifndef _UTIL_H_
#define _UTIL_H_

#include <roaring.hh>
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
};

#endif