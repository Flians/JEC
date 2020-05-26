#ifndef _CEC_H_
#define _CEC_H_

#include "ec.h"

class cec : public ec
{
private:
    // assign values to the i-th element in the PIs
    bool assign_PIs_value(vector<node *> *PIs, int i);
    // Calculate all nodes according to PIs
    bool evaluate(vector<node *> *nodes);

public:
    cec();
    cec(const string &path_output);
    virtual ~cec();
    // evaluate from PIs to POs
    void evaluate_from_PIs_to_POs(vector<node *> *PIs);
    // evaluate from POs to PIs
    void evaluate_from_POs_to_PIs(vector<node *> *POs);
};

#endif