#include "jec.h"

jec::jec(/* args */)
{
}

jec::jec(const string &path_output)
{
    this->fout.open(path_output, ios::out);
}

jec::~jec()
{
    this->fout.flush();
    this->fout.close();
}

bool jec::assign_PIs_value(vector<vector<node *> *> *layers, int i)
{
    if (i == layers->at(0)->size())
    {
        bool res = true;
        for (int level = 1; level < layers->size(); level++)
        {
            res = evaluate(layers->at(level));
        }
        if (!res)
        {
            this->fout << "NEQ" << endl;
            print_PIs_value(layers->at(0), this->fout);
            return false;
        }
    }
    else
    {
        if (layers->at(0)->at(i)->cell == _CONSTANT)
        {
            if (!assign_PIs_value(layers, i + 1))
                return false;
        }
        else
        {
            for (Value val = L; val < X; val = (Value)(val + 1))
            {
                layers->at(0)->at(i)->val = val;
                if (!assign_PIs_value(layers, i + 1))
                    return false;
            }
        }
    }
    return true;
}

bool jec::evaluate(vector<node *> *nodes)
{
    bool res = false;
    for (auto node : (*nodes))
    {
        res |= calculate(node);
    }
    return true;
}

// evaluate from PIs to POs
void jec::evaluate_from_PIs_to_POs(vector<vector<node *> *> *layers)
{
    if (!layers || layers->size() == 0)
    {
        cerr << "The vector layers is empty!" << endl;
        exit(-1);
    }
    // layers[0][0] is clk
    if (assign_PIs_value(layers, 1))
    {
        this->fout << "EQ" << endl;
    }
}

// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(vector<node *> *POs)
{
}

// evaluate from PIs to POs
void jec::evaluate_opensmt(vector<vector<node *> *> *layers)
{
    if (!layers || layers->size() == 0)
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
    for (int i = 0; i < init_id; i++)
    {
        PTRef v = logic.mkBoolVar(to_string(i).c_str());
        nodes.push_back(v);
    }

    // layers[0][0] is clk
    for (int i = 1; i < layers->size(); i++)
    {
        vector<node *> *layer = layers->at(i);
        for (int j = 0; j < layer->size(); j++)
        {
            vec<PTRef> inputs;
            // ayer->at(j)->ins->at(0) is clk
            for (int k = 1; k < layer->at(j)->ins->size(); k++)
            {
                inputs.push(nodes[layer->at(j)->ins->at(k)->id]);
            }
            PTRef res;
            switch (layer->at(j)->cell)
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
            if (layer->at(j)->outs)
            {
                for (auto &out : (*layer->at(j)->outs))
                {
                    nodes[out->id] = res;
                }
            }
        }
    }

    vec<PTRef> outputs;
    for (auto &output : (*layers->back()))
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