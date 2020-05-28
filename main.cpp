#include "include/ec/cec.h"
#include "include/ec/jec.h"
#include "include/ec/simplify.h"
#include "include/util/parser.h"

using namespace std;
// cd build && cmake -G"Unix Makefiles && make" ../
int main(int argc, char *argv[])
{
    clock_t startTime, endTime;
    if (argc >= 4)
    {
        /* parse Verilog files */
        parser verilog_parser;
        vector<node *> *PIs = nullptr;
        vector<node *> *POs = nullptr;
        startTime = clock();
        verilog_parser.parse(argv[1], argv[2], PIs, POs);
        endTime = clock();
        cout << "The parsing time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
        /*
        cout << ">>> before: " << endl;
        verilog_parser.printG(miter);
        */

        /* simplify the graph */
        simplify sim;
        startTime = clock();
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
        endTime = clock();
        cout << "The simplify time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
        // PIs->insert(PIs->end(),verilog_parser.get_constants()->begin(),verilog_parser.get_constants()->end());
        /*
        cout << ">>> after: " << endl;
        verilog_parser.printG(miter);
        */

        /* evaluate the graph */
        // cec cec_(argv[3]);
        // cec_.evaluate_from_PIs_to_POs(PIs);
        jec jec_(argv[3]);
        startTime = clock();
        jec_.evaluate_opensmt(layers);
        endTime = clock();
        cout << "The simulating time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
    }
    else
    {
        printf("Please input three parameters, like \"./xec <golden.v> <revised.v> <output>\".");
    }
    return 0;
}