#ifndef _JEC_H_
#define _JEC_H_

#include "ec.h"

#if __linux__ || __unix__
    #include <opensmt/opensmt2.h>
#endif

class jec : public ec
{
private:
    // assign values to the i-th element in the PIs
    bool assign_PIs_value(vector<vector<Node *>> &layers, int i);
    // Calculate all nodes according to PIs
    bool evaluate(vector<vector<Node *>> &layers);
    bool evaluate(vector<Node *> &nodes);

public:
    jec(const string &path_output);
    virtual ~jec();
    // evaluate from PIs to POs
    void evaluate_from_PIs_to_POs(vector<vector<Node *>> &layers);
    // evaluate from POs to PIs
    void evaluate_from_POs_to_PIs(vector<vector<Node *>> &layers);
#if __linux__ || __unix__
    // evaluate by using opensmt
    void evaluate_opensmt(vector<vector<Node *>> &layers);
#endif
};

#endif