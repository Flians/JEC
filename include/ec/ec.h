#ifndef _EC_H_
#define _EC_H_

#include "libhead.h"

class ec
{
protected:
    ofstream fout;
public:
    // Calculate all nodes according to PIs
    virtual bool evaluate(vector<node *> nodes) = 0;
    void print_PIs_value(vector<node *> *PIs, ofstream &output);
};

#endif