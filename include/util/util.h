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
    static void cleanVP(vector<Node *> &vp);
    
};

#endif