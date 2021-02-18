#ifndef _JEC_H_
#define _JEC_H_

#include "ec.h"

#ifndef WIN
#include <opensmt/opensmt2.h>
#include <cvc4/cvc4.h>
#endif

class jec : virtual public ec
{
private:
    // assign values to the i-th element in the PIs
    bool assign_PIs_value(vector<vector<Node *>> &layers, size_t i);
    // Calculate all nodes according to PIs
    bool evaluate(vector<vector<Node *>> &layers);
    bool evaluate(const vector<Node *> &nodes);
#ifndef WIN
    void create_expr_of_opensmt(Netlist *miter, Logic &logic, vector<PTRef> &exprs);
    bool print_result_of_opensmt(Netlist *miter, vector<PTRef> &exprs, Opensmt &osmt, sstat &reslut);
#endif

public:
    jec(const string &path_output);
    virtual ~jec();
    // evaluate from PIs to POs
    void evaluate_from_PIs_to_POs(Netlist *miter);
    // evaluate from POs to PIs
    void evaluate_from_POs_to_PIs(Netlist *miter);
#ifndef WIN
    // evaluate by using opensmt
    void evaluate_opensmt(Netlist *miter, bool incremental = false);
    void evaluate_min_cone(Netlist *miter);
    // evaluate by using cvc4
    void evaluate_cvc4(Netlist *miter, bool incremental = false);
#endif
};

#endif