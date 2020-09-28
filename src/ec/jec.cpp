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
        error_fout("The vector layers is empty!");
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
        error_fout("The vector layers is empty!");
    }

    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(incremental), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "JSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();

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
    if (!incremental)
    {
        vec<PTRef> outputs;
        for (auto &output : layers.back())
        {
            outputs.push(nodes[output->id]);
        }
        PTRef assert = logic.mkEq(logic.getTerm_true(), logic.mkOr(outputs));
        mainSolver.push(assert);
        reslut = mainSolver.check();
    }
    else
    {
        for (auto &output : layers.back())
        {
            PTRef assert = logic.mkEq(logic.getTerm_true(), nodes[output->id]);
            mainSolver.push(assert);
            reslut = mainSolver.check();
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
            ValPair vp = mainSolver.getValue(nodes[layers[0][i]->id]);
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
}

void jec::build_equation_dfs(Node *cur, Logic &logic, unordered_map<Node *, PTRef> &record)
{
    if (!cur)
    {
        error_fout("The current node is NULL in jec.build_equation_dfs!");
    }
    if (record.count(cur) || cur->cell == CLK)
    {
        return;
    }
    if (cur->cell == _CONSTANT)
    {
        record[cur] = cur->val == L ? logic.getTerm_false() : logic.getTerm_true();
    }
    else if (cur->cell == IN)
    {
        record[cur] = logic.mkBoolVar(cur->name.c_str());
    }
    else
    {
        vec<PTRef> inputs;
        for (auto &in : cur->ins)
        {
            build_equation_dfs(in, logic, record);
            if (in->cell != CLK)
            {
                inputs.push(record[in]);
            }
        }
        if (inputs.size() == 0)
        {
            error_fout("The inputs is empty! in jec.build_equation_dfs!");
        }
        PTRef res;
        switch (cur->cell)
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
            cout << "RG " << cur->name << endl;
        default:
            res = inputs[0];
            break;
        }
        record[cur] = res;
    }
}

bool jec::evaluate_opensmt(deque<Node*> &cone)
{
    if (cone.empty())
    {
        cout << "The vector POs is empty in jec.evaluate_opensmt!" << endl;
    }

    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(true), msg);
    config->setOption(SMTConfig::o_time_queries, SMTOption(false), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "ConeSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();

    unordered_map<Node *, PTRef> nodes;

    sstat reslut;
    int out_len =  cone.size();
    while (out_len--)
    {
        Node *output = cone.front();
        cone.pop_front();
        build_equation_dfs(output, logic, nodes);
        PTRef assert = logic.mkEq(logic.getTerm_true(), nodes[output]);
        mainSolver.push(assert);
        reslut = mainSolver.check();
        if (reslut == s_True) {
            if (output->cell == _EXOR) {
                return false;
            }
            output->cell = _CONSTANT;
            output->val = H;
        } else if (reslut == s_False) {
            if (output->cell == _EXOR) {
                continue;
            }
            assert = logic.mkEq(logic.getTerm_false(), nodes[output]);
            mainSolver.push(assert);
            reslut = mainSolver.check();
            if (reslut == s_True) {
                output->cell = _CONSTANT;
                output->val = L;
            } else if (reslut == s_False) {
                output->cell = IN;
            } else {
                error_fout("The result2 is unknown in jec.evaluate_opensmt!");
            }
        } else {
            error_fout("The result is unknown in jec.evaluate_opensmt!");
        }
        if (output->cell != _EXOR) {
            cone.emplace_back(output);
        }
    }
    return true;
}

void jec::evaluate_min_cone(vector<vector<Node *>> &layers)
{
    // <level, color>
    vector<pair<size_t, int>> info(init_id, {0, 0});
    for (size_t i = 0; i < layers.size(); ++i)
    {
        for (auto &node_ : layers[i])
        {
            info[node_->id].first = i;
            info[node_->id].second = -1;
        }
    }
    // the max number of cones is the size of PIs.
    vector<deque<Node*>> cones(layers[0].size());
    // init cones
    for (size_t i = 0; i < layers[0].size(); ++i)
    {
        info[layers[0][i]->id].second = i;
        if (layers[0][i]->cell != CLK) {
            cones[i].emplace_back(layers[0][i]);
        }
    }
    int smt_id = 0;
    for (size_t i = 1; i < layers.size(); ++i) {
        for (size_t j = 0; j < cones.size(); ++j) {
            size_t exor_num = 0;
            int cur_len = cones[j].size();
            while (cur_len--) {
                Node *cur = cones[j].front();
                cones[j].pop_front();
                if (info[cur->id].first >= i || cur->cell == _EXOR) {
                    cones[j].emplace_back(cur);
                    if (cur->cell == _EXOR)
                        ++exor_num;
                    continue;
                }
                for (auto &tout : cur->outs)
                {
                    if (info[tout->id].second == -1) {
                        info[tout->id].second = j;
                        cones[j].emplace_back(tout);
                        if (tout->cell == _EXOR)
                            ++exor_num;
                    } else {
                        size_t old_color = info[tout->id].second;
                        if (old_color == j) {
                            continue;
                        }
                        while (!cones[old_color].empty()) {
                            Node *tmp = cones[old_color].front();
                            cones[old_color].pop_front();
                            info[tmp->id].second = j;
                            if (info[tmp->id].first >= i || tmp->cell == _EXOR) {
                                cones[j].emplace_back(tmp);
                                if (tmp->cell == _EXOR)
                                    ++exor_num;
                            } else {
                                cones[j].emplace_front(tmp);
                                ++cur_len;
                            }
                        }
                    }
                }
            }
            // evaluate cur_cone
            if (!cones[j].empty() && (cones[j].size() == 1 || exor_num == cones[j].size())) {
                cout << ">>> The cone " << (smt_id++) << " is evaluated." << endl;
                if (!evaluate_opensmt(cones[j])) {
                    this->fout << "NEQ" << endl;
                    return;
                }
            }
        }
    }
    this->fout << "EQ" << endl;
}

#endif

void jec::evaluate_cvc4(vector<vector<Node *>> &layers, bool incremental)
{
    if (layers.empty())
    {
        error_fout("The vector layers is empty!");
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
    if (!incremental)
    {
        vector<CVC4::Expr> outputs;
        for (auto &output : layers.back())
        {
            outputs.emplace_back(nodes[output->id]);
        }
        CVC4::Expr assert = em.mkExpr(CVC4::kind::EQUAL, em.mkConst<bool>(true), em.mkExpr(CVC4::kind::OR, outputs));
        smt.assertFormula(assert);
        reslut = smt.checkSat();
    }
    else
    {
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