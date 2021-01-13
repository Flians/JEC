#ifndef _EC_H_
#define _EC_H_

#include "util/util.h"
#include "util/libfile.h"
#include "circuit/netlist.h"

class ec
{
protected:
    struct Cone
    {
        vector<Node *> inputs;
        deque<Node *> cur;
        vector<Node *> outputs;
    };

    ofstream fout;

    // return the size of other.cur
    size_t merge_cone(int cur_color, Cone &cur_cone, Cone &other_cone, vector<pair<size_t, int>> &info);

public:
    ec(const string &path_output);
    virtual ~ec();
    // Calculate all nodes according to PIs
    virtual bool evaluate(const vector<Node *> &nodes) = 0;
    void print_PIs_value(vector<Node *> &PIs, ofstream &output);
    void print_PIs_value(vector<Node *> &PIs, FILE *fout);
};

#endif