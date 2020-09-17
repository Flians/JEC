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
        if (calculate(node) != L)
        {
            return false;
        }
    }
    return true;
}

bool jec::evaluate(vector<Node *> &nodes)
{
    for (auto &node : nodes)
    {
        node->val = calculate(node);
        if (node->val != L && node->outs.empty())
        {
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
    int index_beg = 0;
    if (layers[0][0]->cell == CLK)
        index_beg = 1;
    // layers[0][0] is clk
    if (assign_PIs_value(layers, index_beg))
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
void jec::evaluate_opensmt(vector<vector<Node *>> &layers, bool incremental)
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
    MainSolver *mainSolver = new MainSolver(*thandler, c, solver, "JSolver");

    Logic &logic = thandler->getLogic();

    vector<PTRef> nodes(init_id);
    // layers[0][0] is clk
    for (size_t i = 0; i < layers[0].size(); i++)
    {
        if (layers[0][i]->cell == _CONSTANT)
        {
            nodes[layers[0][i]->id] = layers[0][i]->val == L ? logic.getTerm_false() : logic.getTerm_true();
        }
        else if (layers[0][i]->cell != CLK)
        {
            nodes[layers[0][i]->id] = logic.mkBoolVar(layers[0][i]->name.c_str());
        }
    }

    for (size_t i = 1; i < layers.size(); i++)
    {
        for (size_t j = 0; j < layers[i].size(); j++)
        {
            vec<PTRef> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (size_t k = 0; k < layers[i][j]->ins.size(); k++)
            {
                if (layers[i][j]->ins[k]->cell != CLK)
                    inputs.push(nodes[layers[i][j]->ins[k]->id]);
            }
            if (inputs.size() == 0)
            {
                error_fout("The inputs is empty! in jec.evaluate_opensmt!");
            }
            PTRef res;
            switch (layers[i][j]->cell)
            {
            case AND:
                res = logic.mkAnd(inputs);
                break;
            case OR:
            case CB:
            case CB3:
                res = logic.mkOr(inputs);
                break;
            case XOR:
                res = logic.mkXor(inputs);
                break;
            case INV:
                res = logic.mkNot(inputs);
                break;
            case _EXOR:
                res = logic.mkXor(inputs);
                break;
            default:
                res = inputs[0];
                break;
            }
            nodes[layers[i][j]->id] = res;
        }
    }

    
    sstat reslut;
    if (incremental) {
        vec<PTRef> outputs;
        for (auto &output : layers.back())
        {
            outputs.push(nodes[output->id]);
        }
        PTRef assert = logic.mkEq(logic.getTerm_true(), logic.mkOr(outputs));
        mainSolver->push(assert);
        reslut = mainSolver->check();
    } else {
        for (auto &output : layers.back())
        {
            PTRef assert = logic.mkEq(logic.getTerm_true(), nodes[output->id]);
            mainSolver->push(assert);
            reslut = mainSolver->check();
            if (reslut == s_True)
                break;
        }
    }
    cout << "The prover is opensmt." << endl;

    if (reslut == s_True)
    {
        this->fout << "NEQ" << endl;
        for (size_t i = 1; i < layers.front().size(); i++)
        {
            ValPair vp = mainSolver->getValue(nodes[layers[0][i]->id]);
            this->fout << logic.printTerm(vp.tr) << " " << vp.val << endl;
        }
    }
    else if (reslut == s_False)
    {
        this->fout << "EQ" << endl;
    }
    else if (reslut == s_Undef)
    {
        this->fout << "unknown" << endl;
    }
    else
    {
        this->fout << "error" << endl;
    }
    delete uftheory;
    delete thandler;
    delete solver;
    delete mainSolver;
}

void jec::evaluate_cadical(vector<vector<Node *>> &layers) {

}
#endif