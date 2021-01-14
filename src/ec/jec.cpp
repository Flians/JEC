#include "ec/jec.h"

jec::jec(const string &path_output) : ec(path_output)
{
}

jec::~jec()
{
}

bool jec::assign_PIs_value(vector<vector<Node *>> &layers, size_t i)
{
    if (i == layers[0].size())
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
        if (layers[0][i]->type == _CONSTANT)
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
    if (layers.empty())
    {
        return false;
    }
    size_t len = layers.size() - 1;
    for (size_t level = 1; level < len; level++)
    {
        for (auto &node : layers[level])
        {
            node->calculate();
        }
    }
    for (auto &node : layers.back())
    {
        if (node->calculate() != L)
        {
            return false;
        }
    }
    return true;
}

bool jec::evaluate(const vector<Node *> &nodes)
{
    for (auto &node : nodes)
    {
        node->calculate();
        if (node->val != L && node->outs.empty())
        {
            return false;
        }
    }
    return true;
}

// evaluate from PIs to POs
void jec::evaluate_from_PIs_to_POs(Netlist *miter)
{
    if (miter->isEmpty())
    {
        WARN_Fout("The netlist '" + miter->name + "' is empty!");
        return;
    }
    vector<vector<Node *>> &layers = dynamic_pointer_cast<Field_2V<Node *>>(miter->properties[LAYERS])->get_value();
    size_t index_beg = 0;
    if (layers[0][0]->type == _CLK)
        index_beg = 1;
    // layers[0][0] is clk
    if (assign_PIs_value(layers, index_beg))
    {
        this->fout << "EQ" << endl;
    }
}

// evaluate from POs to PIs
void jec::evaluate_from_POs_to_PIs(Netlist *miter)
{
}

#ifndef WIN
// evaluate from PIs to POs
void jec::evaluate_opensmt(Netlist *miter, bool incremental)
{
    if (miter->isEmpty())
    {
        WARN_Fout("The netlist is empty!");
        return;
    }
    vector<vector<Node *>> &layers = dynamic_pointer_cast<Field_2V<Node *>>(miter->properties[LAYERS])->get_value();
    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(incremental), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "JSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();

    vector<PTRef> nodes(miter->get_num_gates());
    // layers[0][0] is clk
    for (auto &pi : layers[0])
    {
        if (pi->type == _CONSTANT)
        {
            nodes[pi->id] = pi->val == L ? logic.getTerm_false() : logic.getTerm_true();
        }
        else if (pi->type != _CLK)
        {
            nodes[pi->id] = logic.mkBoolVar(pi->name.c_str());
        }
    }
    size_t num_level = layers.size();
    for (size_t i = 1; i < num_level; i++)
    {
        for (auto &node : layers[i])
        {
            vec<PTRef> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (auto &npi : node->ins)
            {
                if (npi->type != _CLK)
                    inputs.push(nodes[npi->id]);
            }
            if (inputs.size() == 0)
            {
                ERROR_Exit_Fout("The inputs is empty! in jec.evaluate_opensmt!");
            }
            PTRef res;
            switch (node->type)
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
                cout << node->name << endl;
            default:
                res = inputs[0];
                break;
            }
            nodes[node->id] = res;
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
        cout << "The miter is not equivalent." << endl;
        this->fout << "NEQ" << endl;
        for (auto &pi : layers[0])
        {
            if (pi->type != _CLK)
            {
                ValPair vp = mainSolver.getValue(nodes[pi->id]);
                this->fout << logic.printTerm(vp.tr) << " " << vp.val << endl;
            }
        }
    }
    else if (reslut == s_False)
    {
        cout << "The miter is equivalent." << endl;
        this->fout << "EQ" << endl;
    }
    else if (reslut == s_Undef)
    {
        cout << "The miter is unknown." << endl;
        this->fout << "unknown" << endl;
    }
    else
    {
        cout << "The miter is error." << endl;
        this->fout << "error" << endl;
    }
    vector<PTRef>().swap(nodes);
}

void jec::build_equation_dfs(Node *cur, Logic &logic, unordered_map<Node *, PTRef> &record)
{
    if (!cur)
    {
        WARN_Fout("The current node is NULL in jec.build_equation_dfs!");
        return;
    }
    if (record.find(cur) != record.end() || cur->type == _CLK)
    {
        return;
    }
    if (cur->type == _CONSTANT)
    {
        record[cur] = cur->val == L ? logic.getTerm_false() : logic.getTerm_true();
    }
    else if (cur->type == _PI)
    {
        record[cur] = logic.mkBoolVar(cur->name.c_str());
    }
    else
    {
        vec<PTRef> inputs;
        for (auto &in : cur->ins)
        {
            build_equation_dfs(in, logic, record);
            if (in->type != _CLK)
            {
                inputs.push(record[in]);
            }
        }
        if (inputs.size() == 0)
        {
            WARN_Fout("The inputs is empty! in jec.build_equation_dfs!");
        }
        PTRef res;
        switch (cur->type)
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

bool jec::evaluate_opensmt(deque<Node *> &cone)
{
    if (cone.empty())
    {
        cout << "The vector POs is empty in jec.evaluate_opensmt!" << endl;
    }

    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(true), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "ConeSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();
    mainSolver.getConfig().setOption(SMTConfig::o_time_queries, SMTOption(false), msg);

    unordered_map<Node *, PTRef> nodes;

    sstat reslut;
    int out_len = cone.size();
    while (out_len--)
    {
        Node *output = cone.back();
        cone.pop_back();
        if (output->type != _EXOR)
        {
            cone.emplace_front(output);
        }
        build_equation_dfs(output, logic, nodes);
        PTRef assert = logic.mkEq(logic.getTerm_true(), nodes[output]);
        mainSolver.push(assert);
        reslut = mainSolver.check();
        if (reslut == s_True)
        {
            if (output->type == _EXOR)
            {
                return false;
            }
            mainSolver.pop();
            assert = logic.mkEq(logic.getTerm_false(), nodes[output]);
            mainSolver.push(assert);
            reslut = mainSolver.check();
            // mainSolver.printFramesAsQuery();
            if (reslut == s_True)
            {
                output->type = _PI;
            }
            else if (reslut == s_False)
            {
                output->type = _CONSTANT;
                output->val = H;
            }
            else
            {
                WARN_Fout("The result2 is unknown in jec.evaluate_opensmt!");
            }
        }
        else if (reslut == s_False)
        {
            output->type = _CONSTANT;
            output->val = L;
        }
        else
        {
            WARN_Fout("The result is unknown in jec.evaluate_opensmt!");
        }
    }
    nodes.clear();
    return true;
}

void jec::evaluate_min_cone(Netlist *miter)
{
    // <level, color>
    vector<pair<size_t, int>> info(miter->get_num_gates(), {0, 0});
    vector<vector<Node *>> &layers = dynamic_pointer_cast<Field_2V<Node *>>(miter->properties[LAYERS])->get_value();
    size_t num_level = layers.size();
    for (size_t i = 0; i < num_level; ++i)
    {
        for (auto &node_ : layers[i])
        {
            info[node_->id].first = i;
            info[node_->id].second = -1;
        }
    }
    size_t num_pis = layers[0].size();
    // the max number of cones is the size of PIs.
    vector<deque<Node *>> cones(num_pis);
    // init cones
    for (size_t i = 0; i < num_pis; ++i)
    {
        info[layers[0][i]->id].second = i;
        if (layers[0][i]->type != _CLK)
        {
            cones[i].emplace_back(layers[0][i]);
        }
    }
    int smt_id = 0;
    vector<size_t> exor_num(num_pis, 0);
    for (size_t i = 1; i < num_level; ++i)
    {
        for (size_t j = 0; j < num_pis; ++j)
        {
            exor_num[j] = 0;
            int cur_len = cones[j].size();
            while (cur_len--)
            {
                Node *cur = cones[j].front();
                cones[j].pop_front();
                if (info[cur->id].first >= i || cur->type == _EXOR)
                {
                    cones[j].emplace_back(cur);
                    if (cur->type == _EXOR)
                        ++exor_num[j];
                    continue;
                }
                for (auto &tout : cur->outs)
                {
                    if (info[tout->id].second == -1)
                    {
                        info[tout->id].second = j;
                        cones[j].emplace_back(tout);
                        if (tout->type == _EXOR)
                            ++exor_num[j];
                    }
                    else
                    {
                        size_t old_color = info[tout->id].second;
                        if (old_color == j)
                        {
                            continue;
                        }
                        while (!cones[old_color].empty())
                        {
                            Node *tmp = cones[old_color].front();
                            cones[old_color].pop_front();
                            info[tmp->id].second = j;
                            if (info[tmp->id].first >= i || tmp->type == _EXOR)
                            {
                                cones[j].emplace_back(tmp);
                                if (tmp->type == _EXOR)
                                    ++exor_num[j];
                            }
                            else
                            {
                                cones[j].emplace_front(tmp);
                                ++cur_len;
                            }
                        }
                    }
                }
            }
        }
        for (size_t j = 0; j < num_pis; ++j)
        {
            size_t num_node = cones[j].size();
            // evaluate cur_cone
            if (!cones[j].empty() && ((num_node == 1 && info[cones[j][0]->id].first == i) || exor_num[j] == num_node))
            {
                cout << ">>> The cone " << (smt_id++) << " is evaluated." << endl;
                if (!evaluate_opensmt(cones[j]))
                {
                    cout << "The miter is not equivalent." << endl;
                    this->fout << "NEQ" << endl;
                    return;
                }
            }
        }
    }
    vector<pair<size_t, int>>().swap(info);
    vector<deque<Node *>>().swap(cones);
    vector<size_t>().swap(exor_num);
    cout << "The miter is equivalent." << endl;
    this->fout << "EQ" << endl;
}

void jec::evaluate_cvc4(Netlist *miter, bool incremental)
{
    if (miter->isEmpty())
    {
        WARN_Fout("The netlist'" + miter->name + "' is empty!");
        return;
    }

    CVC4::ExprManager em;
    CVC4::SmtEngine smt(&em);
    smt.setLogic("QF_UF");
    smt.setTimeLimit(1800000);
    CVC4::Type boolean = em.booleanType();

    vector<CVC4::Expr> nodes(miter->get_num_gates());
    vector<vector<Node *>> &layers = dynamic_pointer_cast<Field_2V<Node *>>(miter->properties[LAYERS])->get_value();
    // layers[0][0] is clk
    for (auto &pi : layers[0])
    {
        if (pi->type == _CONSTANT)
        {
            nodes[pi->id] = pi->val == L ? em.mkConst<bool>(false) : em.mkConst<bool>(true);
        }
        else if (pi->type != _CLK)
        {
            nodes[pi->id] = em.mkVar(pi->name.c_str(), boolean);
        }
    }
    size_t num_level = layers.size();
    for (size_t i = 1; i < num_level; i++)
    {
        for (auto &node : layers[i])
        {
            vector<CVC4::Expr> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (auto &npi : node->ins)
            {
                if (npi->type != _CLK)
                    inputs.emplace_back(nodes[npi->id]);
            }
            if (inputs.size() == 0)
            {
                WARN_Fout("The inputs is empty! in jec.evaluate_opensmt!");
            }
            CVC4::Expr res;
            switch (node->type)
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
            nodes[node->id] = res;
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
        cout << "The miter is not equivalent." << endl;
        this->fout << "NEQ" << endl;
        for (auto &pi : layers[0])
        {
            CVC4::Expr vp = smt.getValue(nodes[pi->id]);
            this->fout << vp.getId() << " " << smt.getValue(nodes[pi->id]) << endl;
        }
    }
    else if (reslut.isSat() == 0)
    {
        cout << "The miter is equivalent." << endl;
        this->fout << "EQ" << endl;
    }
    else
    {
        cout << "The miter is unknown." << endl;
        this->fout << "unknown" << endl;
    }
    vector<CVC4::Expr>().swap(nodes);
}

#endif