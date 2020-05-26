#ifndef _JEC_H_
#define _JEC_H_

#include "ec.h"

class jec : public ec
{
private:
    // assign values to the i-th element in the PIs
    bool assign_PIs_value(vector<vector<node *> *> *layers, int i);
    // Calculate all nodes according to PIs
    bool evaluate(vector<node *> *nodes);

public:
    jec();
    jec(const string &path_output);
    virtual ~jec();
    void reduce_repeat_nodes(vector<vector<node *> *> *layers);
    // evaluate from PIs to POs
    void evaluate_from_PIs_to_POs(vector<vector<node *> *> *layers);
    // evaluate from POs to PIs
    void evaluate_from_POs_to_PIs(vector<node *> *POs);
};

#endif