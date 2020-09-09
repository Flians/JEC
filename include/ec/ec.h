#ifndef _EC_H_
#define _EC_H_

#include "libhead.h"

class ec
{
protected:
    ofstream fout;

public:
    ec(const string &path_output);
    virtual ~ec();
    // Calculate all nodes according to PIs
    virtual bool evaluate(vector<Node *> &nodes) = 0;
    void print_PIs_value(vector<Node *> &PIs, ofstream &output);
    void print_PIs_value(vector<Node *> &PIs, FILE *fout);
};

#endif