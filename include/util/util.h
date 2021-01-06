#ifndef _UTIL_H_
#define _UTIL_H_

#include "node.h"

class Util
{
private:
    Util();
    Util(const Util &);
    Util &operator=(const Util &);
    ~Util();

public:
    static void unique_element_in_vector(vector<Node *> &v);

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
};

#endif