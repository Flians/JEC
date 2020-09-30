#include "include/ec/cec.h"
#include "include/ec/jec.h"
#include "include/ec/simplify.h"
#include "include/util/parser.h"
#include "include/util/libfile.h"
#include <iomanip>

using namespace std;

enum SMT
{
    _FSM,
    _OPENSMT,
    _CONE,
    _CVC4
};

std::unordered_map<string, SMT> Str_SMT = {
    {"FSM", _FSM},
    {"OPENSMT", _OPENSMT},
    {"CONE", _CONE},
    {"CVC4", _CVC4}};

vector<double> workflow(const char *golden, const char *revise, const char *output, SMT smt, bool incremental = false, bool merge = true)
{
    vector<double> times(4, 0.0);
    clock_t startTime, endTime;
    parser verilog_parser;
    /* parse Verilog files */
    parser miter;
    startTime = clock();
    miter.parse(golden, revise);
    miter.clean_wires();
    miter.clean_spl();
    endTime = clock();
    times[0] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "The parsing time is: " << times[0] << " S" << endl;

    /* simplify the graph */
    simplify sim;
    startTime = clock();
    sim.id_reassign_and_layered(miter.PIs, miter.POs);
    if (merge)
        times[3] = sim.merge_nodes_between_networks();
    endTime = clock();
    times[1] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "The simplify time is: " << times[1] << " S" << endl;

    /* verify the miter */
    jec jec_(output);
    startTime = clock();
    switch (smt)
    {
    case _FSM:
        jec_.evaluate_from_PIs_to_POs(sim.get_layers());
        break;
    case _OPENSMT:
#if __linux__ || __unix__
        jec_.evaluate_opensmt(sim.get_layers(), incremental);
        break;
#endif
    case _CONE:
#if __linux__ || __unix__
        jec_.evaluate_min_cone(sim.get_layers());
        break;
#endif
    default:
        jec_.evaluate_cvc4(sim.get_layers(), incremental);
        break;
    }
    endTime = clock();
    times[2] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    cout << "The simulating time is: " << times[2] << " S" << endl;
    return times;
}

void evaluate(string root_path, SMT smt, bool incremental, bool merge)
{
    vector<string> cases = {
        "c1355",
        "c1908",
        "c3540",
        "c432",
        "c499",
        "c5315",
        // "c6288",
        "c7552",
        "c880",
        "adder",
        "bar",
        "decoder",
        // "divisor",
        // "log2",
        "max",
        // "multiplier",
        "sin"
    };
    int patch = 100;
    size_t num_case = cases.size();
    vector<vector<double>> avg(num_case, vector<double>(4, 0.0));
    for (int i = 0; i < patch; ++i)
    {
        cout << ">>> Iterator #" << i + 1 << endl;
        for (size_t j = 0; j < num_case; ++j)
        {
            cout << "    >>> case " << cases[j] << endl;
            auto runtimes = workflow((root_path + "/golden/gf_" + cases[j] + ".v").c_str(), (root_path + "/revise/rf_" + cases[j] + ".v").c_str(), (root_path + "/output/output_" + cases[j] + ".txt").c_str(), smt, incremental, merge);
            avg[j][0] += runtimes[0];
            avg[j][1] += runtimes[1];
            avg[j][2] += runtimes[2];
            avg[j][3] += runtimes[3];
        }
    }
    cout << ">>> Iterator over!\n"
         << (incremental ? "Incremental" : "Unincremental") << endl;
    for (size_t j = 0; j < num_case; ++j)
    {
        cout << fixed << setprecision(6) << cases[j] << "\t" << avg[j][0] / patch << "\t" << avg[j][1] / patch << "\t" << avg[j][2] / patch << "\t" << avg[j][3] / patch << endl;
    }
}

// cd build && cmake -G"Unix Makefiles && make" ../
int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        evaluate(argv[1], Str_SMT[string(argv[2])], argv[3][0] == 'i', argv[4][0] == 'm');
    }
    else if (argc > 5)
    {
        workflow(argv[1], argv[2], argv[3], Str_SMT[string(argv[4])], argv[5][0] == 'i', argv[6][0] == 'm');
    }
    else
    {
        printf("Please input five parameters, like \"./JEC <golden.v> <revised.v> <output> <FSM|OPENSMT|CVC4> <i> <m>\".");
    }
    return 0;
}