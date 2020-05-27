#include "include/ec/cec.h"
#include "include/ec/jec.h"
#include "include/ec/simplify.h"
#include "include/util/parser.h"

using namespace std;
// cd build && cmake -G"Unix Makefiles && make" ../
int main(int argc, char *argv[])
{
    clock_t startTime, endTime;
    startTime = clock();
    if (argc >= 4)
    {
        /* parse Verilog files */
        parser verilog_parser;
        vector<node *> *PIs = nullptr;
        vector<node *> *POs = nullptr;
        verilog_parser.parse(argv[1], argv[2], PIs, POs);
        /*
        cout << ">>> before: " << endl;
        verilog_parser.printG(miter);
        */

        /* simplify the graph */
        simplify sim;
        sim.clean_wire_buf(PIs);
        // merge PIs and constants
        for (auto &con : *verilog_parser.get_constants())
        {
            if (con->outs)
            {
                PIs->insert(PIs->end(), con);
            }
        }
        vector<vector<node *> *> *layers = sim.layer_assignment(PIs);
        sim.reduce_repeat_nodes(layers);
        sim.id_reassign(PIs);
        sim.sort_nodes(layers);
        // PIs->insert(PIs->end(),verilog_parser.get_constants()->begin(),verilog_parser.get_constants()->end());
        /*
        cout << ">>> after: " << endl;
        verilog_parser.printG(miter);
        */

        /* evaluate the graph */
        // cec cec_(argv[3]);
        // cec_.evaluate_from_PIs_to_POs(PIs);
        jec jec_(argv[3]);
        jec_.evaluate_opensmt(layers);
    }
    else
    {
        printf("Please input three parameters, like \"./xec <golden.v> <revised.v> <output>\".");
    }
    endTime = clock();
    cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
    return 0;
}