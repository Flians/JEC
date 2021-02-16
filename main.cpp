#include "circuit/netlist.h"
#include "ec/cec.h"
#include "ec/jec.h"
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
    vector<double> times(6, 0.0);
    clock_t startTime, endTime, tmp;
    startTime = clock();
    /* parse Verilog files */
    Netlist miter(golden, revise);
    endTime = clock();
    times[0] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    JINFO("The parsing time is: " + std::to_string(times[0]) + " S");

    /* simplify the graph */
    startTime = clock();
    miter.clean_spl(false);
    // cout << miter << endl;
    tmp = clock();
    cout << "The cleaning time is: " << (double)(tmp - startTime) / CLOCKS_PER_SEC << " S" << endl;
    if (!Util::path_balance(&miter))
    {
        times[4] = 0;
        JWARN("The netlist '" + miter.name + "' is not path_balanced!");
    }
    else
    {
        times[4] = 1;
        JWARN("The netlist '" + miter.name + "' is path_balanced!");
    }
    cout << "The path balancing time is: " << (double)(clock() - tmp) / CLOCKS_PER_SEC << " S" << endl;
    tmp = clock();
    if (merge)
    {
        times[3] = miter.merge_nodes_between_networks();
        cout << "The merging time is: " << (double)(clock() - tmp) / CLOCKS_PER_SEC << " S" << endl;
    }
    endTime = clock();
    times[1] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    JINFO("The simplify time is: " + std::to_string(times[1]) + " S");

    /* verify the miter */
    jec jec_(output);
    startTime = clock();
    switch (smt)
    {
#ifndef WIN
    case _OPENSMT:
        jec_.evaluate_opensmt(&miter, incremental);
        break;
    case _CONE:
        jec_.evaluate_min_cone(&miter);
        break;
    case _CVC4:
        jec_.evaluate_cvc4(&miter, incremental);
        break;
#endif
    default:
        jec_.evaluate_from_PIs_to_POs(&miter);
    }
    endTime = clock();
    times[5] = static_cast<double>(miter.getProperty(PROPERTIES::EQ));
    times[2] = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    JINFO("The simulating time is: " + std::to_string(times[2]) + " S");
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
        "c6288",
        "c7552",
        "c880",
        // "adder",
        // "bar",
        // "decoder",
        // "divisor",
        // "log2",
        // "max",
        // "multiplier",
        // "sin"
    };
    int patch = 100;
    size_t num_case = cases.size();
    vector<vector<double>> avg(num_case, vector<double>(6, 0.0));
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
            avg[j][4] += runtimes[4];
            avg[j][5] += runtimes[5];
        }
    }
    cout << ">>> Iterator over!\n"
         << (incremental ? "Incremental" : "Unincremental") << endl;
    for (size_t j = 0; j < num_case; ++j)
    {
        cout << fixed << setprecision(6) << cases[j];
        for (auto &item : avg[j])
        {
            cout << "\t" << item / patch;
        }
        cout << endl;
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
