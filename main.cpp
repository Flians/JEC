#include "ec/cec.h"
#include "ec/jec.h"
#include <iomanip>
#include <unistd.h>

using namespace std;

enum SMT
{
    _FSM,
    _OPENSMT,
    _CONE,
    _CVC4,
    _NONE
};

const std::unordered_map<string, SMT> Str_SMT = {
    {"FSM", _FSM},
    {"OPENSMT", _OPENSMT},
    {"CONE", _CONE},
    {"CVC4", _CVC4}};

void print_netlist(const string &output_path, const string &input_path)
{
    ofstream golden(output_path);
    Netlist gf(input_path);
    gf.clean_spl(0);
    golden << gf << endl;
    golden.close();
}

vector<double> workflow(const char *golden, const char *revise, const char *output, bool clean_dff, bool clean_spl, bool merge, SMT smt, bool incremental)
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
    miter.clean_spl(clean_spl, clean_dff);
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
    if (smt == _NONE)
        return times;
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

void evaluate(string root_path, int batch, bool clean_dff, bool clean_spl, bool merge, SMT smt, bool incremental)
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
    size_t num_case = cases.size();
    vector<vector<double>> avg(num_case, vector<double>(6, 0.0));
    for (int i = 0; i < batch; ++i)
    {
        cout << ">>> Iterator #" << i + 1 << endl;
        for (size_t j = 0; j < num_case; ++j)
        {
            cout << "    >>> case " << cases[j] << endl;
            auto runtimes = workflow((root_path + "/golden/gf_" + cases[j] + ".v").c_str(), (root_path + "/revise/rf_" + cases[j] + ".v").c_str(), (root_path + "/output/output_" + cases[j] + ".txt").c_str(), clean_dff, clean_spl, merge, smt, incremental);
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
            cout << "\t" << item / batch;
        }
        cout << endl;
    }
}

// cd build && cmake -G"Unix Makefiles && make" ../
int main(int argc, char *argv[])
{
    int opt = 0;
    char golden[100], revise[100], output[100], root_path[100];
    SMT smt = _NONE;
    bool clean_dff = false, clean_spl = false, incremental = false, merge = false, help = false, is_batch = false;
    int batch = 100;
    std::string str_help;
    str_help.append("Please input parameters:\n")
        .append("\t-h: help;\n")
        .append("\t-b: the root directory which includes the godlen directory and the revise directory;\n")
        .append("\t-n: the batch, the default is 100;\n")
        .append("\t-p: the batch task;\n")
        .append("\t-g: the path of golden file;\n")
        .append("\t-r: the path of revised file;\n")
        .append("\t-o: the path of output file;\n")
        .append("\t-m: merge the equivalent nodes;\n")
        .append("\t-d: clean DFF;\n")
        .append("\t-s: clean Splitter;\n")
        .append("\t-i: whether to solve iteratively;\n")
        .append("\t-e: the type fo SMT solver, including FSM, OPENSMT, CONE and CVC4;\n")
        .append("For example, \"./JEC -g <golden.v> -r <revised.v> -o <output> -e <FSM|OPENSMT|CONE|CVC4> <-i> <-m> <-s> <-d>\".");
    while ((opt = getopt(argc, argv, "dhimpsb:g:r:o:e:n:")) != -1)
    {
        switch (opt)
        {
        case 'd':
            clean_dff = true;
            break;
        case 'i':
            incremental = 1;
            break;
        case 'm':
            merge = 1;
            break;
        case 'p':
            is_batch = 1;
            break;
        case 's':
            clean_spl = 1;
            break;
        case 'b':
            strcpy(root_path, optarg);
            break;
        case 'g':
            strcpy(golden, optarg);
            break;
        case 'r':
            strcpy(revise, optarg);
            break;
        case 'o':
            strcpy(output, optarg);
            break;
        case 'e':
            smt = Str_SMT.at(optarg);
            break;
        case 'n':
        {
            int tmp = atoi(optarg);
            if (tmp > 0)
            {
                batch = tmp;
            }
            break;
        }
        default:
            help = true;
        }
    }

    if (help)
    {
        printf("%s\n", str_help.c_str());
    }
    else if (is_batch)
    {
        evaluate(root_path, batch, clean_dff, clean_spl, merge, smt, incremental);
    }
    else
    {
        workflow(golden, revise, output, clean_dff, clean_spl, merge, smt, incremental);
    }

    return 0;
}
