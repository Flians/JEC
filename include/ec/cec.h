#ifndef _CEC_H_
#define _CEC_H_

#include "ec.h"

class cec : public ec
{
private:
    // assign values to the i-th element in the PIs
    bool assign_PIs_value(vector<Node *> &PIs, int i);
    // Calculate all nodes according to PIs
    bool evaluate(vector<Node *> &nodes);

public:
    cec(const string &path_output);
    virtual ~cec();
    // evaluate from PIs to POs
    void evaluate_from_PIs_to_POs(vector<Node *> &PIs);
    // evaluate from POs to PIs
    void evaluate_from_POs_to_PIs(vector<Node *> &POs);
};

#endif