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
    // c->setOption(SMTConfig::o_time_queries, SMTOption(true), msg);
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
            case WIRE:
            case SPL:
            case SPL3:
                cout << layers[i][j]->name << endl;
            default:
                res = inputs[0];
                break;
            }
            nodes[layers[i][j]->id] = res;
        }
    }
    sstat reslut;
    if (!incremental) {
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

#endif

void jec::evaluate_cadical(vector<vector<Node *>> &layers) {

}

void jec::evaluate_cvc4(vector<vector<Node *>> &layers, bool incremental) {
    if (layers.empty())
    {
        cerr << "The vector layers is empty!" << endl;
        exit(-1);
    }

    CVC4::ExprManager em;
    CVC4::SmtEngine smt(&em);
    smt.setLogic("QF_UF");
    smt.setTimeLimit(1800000);
    CVC4::Type boolean = em.booleanType();

    vector<CVC4::Expr> nodes(init_id);
    // layers[0][0] is clk
    for (size_t i = 0; i < layers[0].size(); i++)
    {
        if (layers[0][i]->cell == _CONSTANT)
        {
            nodes[layers[0][i]->id] = layers[0][i]->val == L ? em.mkConst<bool>(false) : em.mkConst<bool>(true);
        }
        else if (layers[0][i]->cell != CLK)
        {
            nodes[layers[0][i]->id] = em.mkVar(layers[0][i]->name.c_str(), boolean);
        }
    }

    for (size_t i = 1; i < layers.size(); i++)
    {
        for (size_t j = 0; j < layers[i].size(); j++)
        {
            vector<CVC4::Expr> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (size_t k = 0; k < layers[i][j]->ins.size(); k++)
            {
                if (layers[i][j]->ins[k]->cell != CLK)
                    inputs.emplace_back(nodes[layers[i][j]->ins[k]->id]);
            }
            if (inputs.size() == 0)
            {
                error_fout("The inputs is empty! in jec.evaluate_opensmt!");
            }
            CVC4::Expr res;
            switch (layers[i][j]->cell)
            {
            case AND:
                res = em.mkExpr(CVC4::kind::AND, inputs);
                break;
            case OR:
            case CB:
            case CB3:
                res = em.mkExpr(CVC4::kind::OR, inputs);
                break;
            case XOR:
                res = em.mkExpr(CVC4::kind::XOR, inputs);
                break;
            case INV:
                res = em.mkExpr(CVC4::kind::NOT, inputs);
                break;
            case _EXOR:
                res = em.mkExpr(CVC4::kind::XOR, inputs);
                break;
            default:
                res = inputs[0];
                break;
            }
            nodes[layers[i][j]->id] = res;
        }
    }
    CVC4::Result reslut;
    if (!incremental) {
        vector<CVC4::Expr> outputs;
        for (auto &output : layers.back())
        {
            outputs.emplace_back(nodes[output->id]);
        }
        CVC4::Expr assert = em.mkExpr(CVC4::kind::EQUAL, em.mkConst<bool>(true), em.mkExpr(CVC4::kind::OR, outputs));
        smt.assertFormula(assert);
        reslut = smt.checkSat();
    } else {
        for (auto &output : layers.back())
        {
            CVC4::Expr assert = em.mkExpr(CVC4::kind::EQUAL, em.mkConst<bool>(true), nodes[output->id]);
            smt.assertFormula(assert);
            reslut = smt.checkSat();
            if (reslut.isSat())
                break;
        }
    }
    cout << "The prover is CVC4." << endl;

    if (reslut.isSat() == 1)
    {
        this->fout << "NEQ" << endl;
        for (size_t i = 1; i < layers.front().size(); i++)
        {
            CVC4::Expr vp = smt.getValue(nodes[layers[0][i]->id]);
            this->fout << vp.getId() << " " << smt.getValue(nodes[layers[0][i]->id]) << endl;
        }
    }
    else if (reslut.isSat() == 0)
    {
        this->fout << "EQ" << endl;
    }
    else
    {
        this->fout << "unknown" << endl;
    }
}