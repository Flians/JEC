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
        for (size_t j = 0, num_layer_level = layers[level].size(); j < num_layer_level; ++j)
        {
            layers[level][j]->calculate();
        }
    }
    for (size_t i = 0, len = layers.back().size(); i < len; ++i)
    {
        auto &node = layers.back()[i];
        if (node->calculate() != L)
        {
            return false;
        }
    }
    return true;
}

bool jec::evaluate(const vector<Node *> &nodes)
{
    for (size_t i = 0, len = nodes.size(); i < len; ++i)
    {
        auto &node = nodes[i];
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
        JWARN("The netlist '" + miter->name + "' is empty!");
        return;
    }
    vector<vector<Node *>> &layers = miter->getProperty(PROPERTIES::LAYERS);
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

void jec::create_expr_of_opensmt(Netlist *miter, Logic &logic, vector<PTRef> &exprs)
{
    vector<vector<Node *>> &layers = miter->getProperty(PROPERTIES::LAYERS);
    exprs.resize(miter->get_num_gates(), logic.getTerm_false());
    // layers[0][0] is clk
    for (size_t i = 0, num_level = layers.size(); i < num_level; i++)
    {
        auto &layer = layers[i];
        for (size_t j = 0, num_layer_i = layer.size(); j < num_layer_i; ++j)
        {
            auto &node = layer[j];
            vec<PTRef> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (size_t k = 0, num_node_ins = node->ins.size(); k < num_node_ins; ++k)
            {
                auto &npi = node->ins[k];
                if (npi->type != _CLK)
                    inputs.push(exprs[npi->id]);
            }
            if (inputs.size() == 0 && node->type > _PI)
            {
                JERROR("The inputs is empty! in jec.evaluate_opensmt!");
            }
            PTRef res;
            switch (node->type)
            {
            case _CONSTANT:
                res = node->val == L ? logic.getTerm_false() : logic.getTerm_true();
                break;
            case _CLK:
                break;
            case _PI:
                res = logic.mkBoolVar(node->name.c_str());
                break;
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
            case _ANDF:
                res = logic.mkOr(inputs[0], logic.mkAnd(inputs[1], exprs[node->id]));
                break;
            case WIRE:
            case SPL:
            case SPL3:
                // cout << node->name << endl;
            default:
                res = inputs[0];
                break;
            }
            exprs[node->id] = res;
        }
    }
}

bool jec::print_result_of_opensmt(Netlist *miter, vector<PTRef> &exprs, Opensmt &osmt, sstat &reslut)
{
    if (reslut == s_True)
    {
        Logic &logic = osmt.getLogic();
        MainSolver &mainSolver = osmt.getMainSolver();
        JWARN("The miter '" + miter->name + "' is not equivalent.");
        this->fout << "NEQ" << endl;
        miter->setProperty(PROPERTIES::EQ, false);
        for (auto iter = miter->map_PIs.begin(), iter_end = miter->map_PIs.end(); iter != iter_end; ++iter)
        {
            auto &pi = iter->second;
            if (pi->type != _CLK)
            {
                ValPair vp = mainSolver.getValue(exprs[pi->id]);
                this->fout << logic.printTerm(vp.tr) << " " << vp.val << endl;
            }
        }
    }
    else if (reslut == s_False)
    {
        JWARN("The miter '" + miter->name + "' is equivalent.");
        this->fout << "EQ" << endl;
        miter->setProperty(PROPERTIES::EQ, true);
        return true;
    }
    else if (reslut == s_Undef)
    {
        JWARN("The miter '" + miter->name + "' is unknown.");
        this->fout << "unknown" << endl;
    }
    else
    {
        JWARN("The miter '" + miter->name + "' is error.");
        this->fout << "error" << endl;
    }
    return false;
}

// evaluate from PIs to POs
void jec::evaluate_opensmt(Netlist *miter, bool incremental)
{
    if (!miter || miter->isEmpty())
    {
        JWARN("The netlist is empty!");
        return;
    }
    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(incremental), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "JSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();
    vector<PTRef> exprs;
    this->create_expr_of_opensmt(miter, logic, exprs);

    vector<vector<Node *>> &layers = miter->getProperty(PROPERTIES::LAYERS);
    auto &pos = layers.back();
    size_t num_pos = pos.size();

    sstat reslut;
    if (!incremental)
    {
        vec<PTRef> outputs;
        for (size_t i = 0; i < num_pos; ++i)
        {
            outputs.push(exprs[pos[i]->id]);
        }
        PTRef assert = logic.mkEq(logic.getTerm_true(), logic.mkOr(outputs));
        mainSolver.push(assert);
        reslut = mainSolver.check();
    }
    else
    {
        sort(pos.begin(), pos.end(), [&exprs](Node *a, Node *b) {
            return exprs[a->id].x < exprs[b->id].x;
        });
        for (size_t i = 0; i < num_pos; ++i)
        {
            PTRef assert = logic.mkEq(logic.getTerm_true(), exprs[pos[i]->id]);
            mainSolver.push(assert);
            reslut = mainSolver.check();
            if (reslut == s_True)
                break;
        }
    }
    JINFO("The prover is opensmt.");
    this->print_result_of_opensmt(miter, exprs, osmt, reslut);
    vector<PTRef>().swap(exprs);
}

void jec::evaluate_min_cone(Netlist *miter)
{
    if (miter->isEmpty())
    {
        JWARN("The netlist is empty!");
        return;
    }
    auto config = std::unique_ptr<SMTConfig>(new SMTConfig());
    const char *msg;
    config->setOption(SMTConfig::o_incremental, SMTOption(true), msg);
    Opensmt osmt(opensmt_logic::qf_bool, "ConeSolver", std::move(config));
    MainSolver &mainSolver = osmt.getMainSolver();
    Logic &logic = osmt.getLogic();
    mainSolver.getConfig().setOption(SMTConfig::o_time_queries, SMTOption(false), msg);
    vector<PTRef> exprs;
    this->create_expr_of_opensmt(miter, logic, exprs);

    // <level, color>
    vector<pair<size_t, int>> info(miter->get_num_gates(), {0, 0});
    vector<vector<Node *>> &layers = miter->getProperty(PROPERTIES::LAYERS);
    const size_t num_level = layers.size();
    const size_t num_pis = miter->map_PIs.size();
    vector<deque<Node *>> cones(num_pis);
    for (size_t i = 0; i < num_level; ++i)
    {
        for (size_t j = 0, num_layer_i = layers[i].size(); j < num_layer_i; ++j)
        {
            auto &node_ = layers[i][j];
            info[node_->id].first = i;
            info[node_->id].second = -1;
            // init cones. The max number of cones is the size of PIs.
            if (i == 0 && node_->type != _CLK)
            {
                cones[j].emplace_back(node_);
            }
        }
    }
    int smt_id = 0;
    sstat reslut = s_False;
    for (size_t i = 1; i < num_level; ++i)
    {
        for (size_t j = 0; j < num_pis; ++j)
        {
            auto &cur_cone = cones[j];
            size_t cur_len = cur_cone.size();
            while (cur_len--)
            {
                Node *cur = cur_cone.front();
                cur_cone.pop_front();
                info[cur->id].second = j;
                if (info[cur->id].first >= i || cur->type == _EXOR)
                {
                    cur_cone.emplace_back(cur);
                    continue;
                }
                for (size_t k = 0, num_cur_outs = cur->outs.size(); k < num_cur_outs; ++k)
                {
                    auto &tout = cur->outs[k];
                    if (info[tout->id].second == -1)
                    {
                        info[tout->id].second = j;
                        cur_cone.emplace_back(tout);
                    }
                    else
                    {
                        size_t old_color = info[tout->id].second;
                        if (old_color == j)
                        {
                            continue;
                        }
                        auto &other_cone = cones[old_color];
                        cur_len += other_cone.size();
                        cur_cone.insert(cur_cone.begin(), other_cone.begin(), other_cone.end());
                        std::deque<Node *>().swap(other_cone);
                    }
                }
            }
        }
        for (size_t j = 0; j < num_pis; ++j)
        {
            auto &cur_cone = cones[j];
            size_t num_node = cur_cone.size();
            // evaluate cur_cone
            if (num_node > 0 && ((num_node == 1 && info[cur_cone[0]->id].first == i) || i == num_level - 1))
            {
                cout << ">>> The cone " << (smt_id++) << " is evaluated." << endl;
                for (auto it = cur_cone.begin(), it_end = cur_cone.end(); it != it_end; ++it)
                {
                    auto &expr = exprs[(*it)->id];
                    mainSolver.push(logic.mkEq(logic.getTerm_true(), expr));
                    reslut = mainSolver.check();
                    if (reslut == s_True)
                    {
                        if ((*it)->type == _EXOR)
                        {
                            this->print_result_of_opensmt(miter, exprs, osmt, reslut);
                            return;
                        }
                        mainSolver.pop();
                        mainSolver.push(logic.mkEq(logic.getTerm_false(), expr));
                        reslut = mainSolver.check();
                        // mainSolver.printFramesAsQuery();
                        if (reslut == s_True)
                        {
                            (*it)->type = _PI;
                        }
                        else if (reslut == s_False)
                        {
                            (*it)->type = _CONSTANT;
                            (*it)->val = H;
                        }
                        else
                        {
                            JWARN("The result2 is", reslut == s_Undef ? "unknown" : "error", "in jec.evaluate_min_cone!");
                            this->print_result_of_opensmt(miter, exprs, osmt, reslut);
                            return;
                        }
                    }
                    else if (reslut == s_False)
                    {
                        (*it)->type = _CONSTANT;
                        (*it)->val = L;
                    }
                    else
                    {
                        JWARN("The result is", reslut == s_Undef ? "unknown" : "error", "in jec.evaluate_min_cone!");
                        this->print_result_of_opensmt(miter, exprs, osmt, reslut);
                        return;
                    }
                }
            }
        }
    }
    this->print_result_of_opensmt(miter, exprs, osmt, reslut);
    vector<pair<size_t, int>>().swap(info);
    vector<deque<Node *>>().swap(cones);
}

void jec::evaluate_cvc4(Netlist *miter, bool incremental)
{
    if (miter->isEmpty())
    {
        JWARN("The netlist'" + miter->name + "' is empty!");
        return;
    }

    CVC4::ExprManager em;
    CVC4::SmtEngine smt(&em);
    smt.setLogic("QF_UF");
    smt.setTimeLimit(1800000);
    CVC4::Type boolean = em.booleanType();

    vector<CVC4::Expr> nodes(miter->get_num_gates());
    vector<vector<Node *>> &layers = miter->getProperty(PROPERTIES::LAYERS);
    // layers[0][0] is clk
    for (size_t i = 0, num_pis = layers[0].size(); i < num_pis; ++i)
    {
        auto &pi = layers[0][i];
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
        for (size_t j = 0, num_layer_i = layers[i].size(); j < num_layer_i; ++j)
        {
            auto &node = layers[i][j];
            vector<CVC4::Expr> inputs;
            // layers[i][j]->ins->at(0) is clk
            for (size_t k = 0, num_node_ins = node->ins.size(); k < num_node_ins; ++k)
            {
                auto &npi = node->ins[k];
                if (npi->type != _CLK)
                    inputs.emplace_back(nodes[npi->id]);
            }
            if (inputs.size() == 0)
            {
                JWARN("The inputs is empty! in jec.evaluate_opensmt!");
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
        for (size_t i = 0, num_layers_back = layers.back().size(); i < num_layers_back; ++i)
        {
            outputs.emplace_back(nodes[layers.back()[i]->id]);
        }
        CVC4::Expr assert = em.mkExpr(CVC4::kind::EQUAL, em.mkConst<bool>(true), em.mkExpr(CVC4::kind::OR, outputs));
        smt.assertFormula(assert);
        reslut = smt.checkSat();
    }
    else
    {
        for (size_t i = 0, num_layers_back = layers.back().size(); i < num_layers_back; ++i)
        {
            CVC4::Expr assert = em.mkExpr(CVC4::kind::EQUAL, em.mkConst<bool>(true), nodes[layers.back()[i]->id]);
            smt.assertFormula(assert);
            reslut = smt.checkSat();
            if (reslut.isSat())
                break;
        }
    }
    cout << "The prover is CVC4." << endl;

    if (reslut.isSat() == 1)
    {
        JWARN("The miter '" + miter->name + "' is not equivalent.");
        this->fout << "NEQ" << endl;
        miter->setProperty(PROPERTIES::EQ, false);
        for (size_t j = 0, num_layer_pi = layers[0].size(); j < num_layer_pi; ++j)
        {
            auto &pi = layers[0][j];
            CVC4::Expr vp = smt.getValue(nodes[pi->id]);
            this->fout << vp.getId() << " " << smt.getValue(nodes[pi->id]) << endl;
        }
    }
    else if (reslut.isSat() == 0)
    {
        JWARN("The miter '" + miter->name + "' is equivalent.");
        this->fout << "EQ" << endl;
        miter->setProperty(PROPERTIES::EQ, true);
    }
    else
    {
        cout << "The miter is unknown." << endl;
        this->fout << "unknown" << endl;
    }
    vector<CVC4::Expr>().swap(nodes);
}

#endif
