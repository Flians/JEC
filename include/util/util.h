#ifndef _UTIL_H_
#define _UTIL_H_

#include "node.h"
#include "netlist.h"

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

    /** make a miter for the golden netlist and the revised netlist */
    static Netlist *make_miter(Netlist *golden, Netlist *revised);
};

#endif