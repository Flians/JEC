#include "../include/ec/cec.h"
#include "../include/ec/jec.h"
#include "../include/ec/simplify.h"
#include "../include/util/parser.h"

using namespace std;
// cd build && cmake -G"Unix Makefiles && make" ../
int main(int argc, char *argv[])
{
    clock_t startTime, endTime;
    if (argc >= 4)
    {
        parser verilog_parser;
        startTime = clock();
        /* parse Verilog files */
        parser miter;
        miter.parse(argv[1], argv[2]);
        miter.clean_wires();
        miter.clean_spl();
        endTime = clock();
        cout << "The parsing time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
        
        /* simplify the graph */
        simplify sim;
        sim.id_reassign_and_layered(miter.PIs, miter.POs);
        sim.merge_nodes_between_networks();
        endTime = clock();
        cout << "The simplify time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;

        /* verify the miter */
        jec jec_(argv[3]);
        startTime = clock();
        #if __linux__ || __unix__
            jec_.evaluate_opensmt(sim.get_layers(), false);
            // jec_.evaluate_cvc4(sim.get_layers(), false);
        #else
            jec_.evaluate_from_PIs_to_POs(layers);
        #endif
        endTime = clock();
        cout << "The simulating time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << " S" << endl;
    }
    else
    {
        printf("Please input three parameters, like \"./xec <golden.v> <revised.v> <output>\".");
    }
    return 0;
}