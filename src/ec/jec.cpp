#include "jec.h"

jec::jec(const string &path_output) : ec(path_output)
{
}

jec::~jec()
{
}

bool jec::assign_PIs_value(vector<vector<Node *>> &layers, int i)
{
    if (i == (int)layers[0].size())
    {
        if (!evaluate(layers))
        {
            this->fout << "NEQ" << endl;
            print_PIs_value(layers[0], this->fout);
            return false;
        }
    }
    else
    {
        if (layers[0][i]->cell == _CONSTANT)
        {
            if (!assign_PIs_value(layers, i + 1))
                return false;
        }
        else
        {
            for (Value val = L; val < X; val = (Value)(val + 1))
            {
                layers[0][i]->val = val;
                if (!assign_PIs_value(layers, i + 1))
                    return false;
            }
        }
    }
    return true;
}

bool jec::evaluate(vector<vector<Node *>> &layers)
{
    for (size_t level = 1; level < layers.size() - 1; level++)
    {
        for (auto &node : layers[level])
        {
            node->val = calculate(node);
        }
    }
    for (auto node : layers.back())
    {
        if (calculate(node) != L) {
            return false;
        }
    }
    return true;
}

bool jec::evaluate(vector<Node *> &nodes) {
    for (auto &node : nodes)
    {
        node->val = calculate(node);
        if (node->val != L && node->outs.empty()) {
            return false;
        }
    }
    return true;
}

// evaluate from PIs to POs
void jec::evaluate_from_PIs_to_POs(vector<vector<Node *>> &layers)
{
    if (layers.empty())
    {
        cerr << "The vector layers is empty!" << endl;
        exit(-1);
    }
    // layers[0][0] is clk
    if (assign_PIs_value(layers, 0))
    {
        this->fout << "EQ" << endl;
    }
}

// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(vector<vector<Node *>> &layers)
{
}

#if __linux__ || __unix__
// evaluate from PIs to POs
void jec::evaluate_opensmt(vector<vector<Node *>> &layers)
{
    if (layers.empty())
    {
        cerr << "The vector layers is empty!" << endl;
        exit(-1);
    }

    SMTConfig c;
    UFTheory *uftheory = new UFTheory(c);
    THandler *thandler = new THandler(*uftheory);
    SimpSMTSolver *solver = new SimpSMTSolver(c, *thandler);
    MainSolver *mainSolver = new MainSolver(*thandler, c, solver, "test solver");

    Logic &logic = thandler->getLogic();

    vector<PTRef> nodes;
    for (size_t i = 0; i < init_id; i++)
    {
        PTRef v = logic.mkBoolVar(to_string(i).c_str());
        nodes.push_back(v);
    }

    // layers[0][0] is clk
    for (auto &node: layers[0]) {
        if (node->cell==_CONSTANT) {
            nodes[node->id] = node->val==L?logic.getTerm_false():logic.getTerm_true();
        }
    }

    for (size_t i = 1; i < layers.size(); i++)
    {
        for (size_t j = 0; j < layers[i].size(); j++)
        {
            vec<PTRef> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (size_t k = 1; k < layers[i][j]->ins.size(); k++)
            {
                inputs.push(nodes[layers[i][j]->ins[k]->id]);
            }
            PTRef res;
            switch (layers[i][j]->cell)
            {
            case AND:
                res = logic.mkAnd(inputs);
                break;
            case OR:
                res = logic.mkOr(inputs);
                break;
            case XOR:
                res = logic.mkXor(inputs);
                break;
            case INV:
                res = logic.mkNot(inputs);
                break;
            default:
                if (inputs.size() == 0)
                {
                    cerr << "The inputs is empty! in jec.evaluate_opensmt!" << endl;
                    exit(-1);
                }
                res = inputs[0];
                break;
            }
            for (auto &out : layers[i][j]->outs)
            {
                nodes[out->id] = res;
            }
        }
    }

    vec<PTRef> outputs;
    for (auto &output : layers.back())
    {
        outputs.push(nodes[output->id]);
    }
    PTRef result = logic.mkAnd(outputs);
    mainSolver->push(result);
    cout << "Running check!" << endl;
    sstat r = mainSolver->check();

    if (r == s_True)
        this->fout << "EQ" << endl;
    else if (r == s_False)
        this->fout << "NEQ" << endl;
    else if (r == s_Undef)
        this->fout << "unknown" << endl;
    else
        this->fout << "error" << endl;
}
#endif