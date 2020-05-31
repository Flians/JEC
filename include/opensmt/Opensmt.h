#ifndef OPENSMT_H
#define OPENSMT_H

#include "SMTConfig.h"
#include "Theory.h"
#include "THandler.h"
#include "SimpSMTSolver.h"
#include "MainSolver.h"
#include "Logic.h"

typedef enum
{
    qf_uf         // Uninterpreted Functions
  , qf_cuf        // Uninterpreted Functions for C
  , qf_bv         // BitVectors
  , qf_rdl        // Real difference logics
  , qf_idl        // Integer difference logics
  , qf_lra        // Real linear arithmetic
  , qf_lia        // Integer linear arithmetic
  , qf_ufidl      // UF + IDL
  , qf_uflra      // UF + LRA
  , qf_bool       // Only booleans
  , qf_ct         // Cost 
} opensmt_logic;

class Opensmt
{
public:
    Opensmt(opensmt_logic _logic, const char* name, int bw = 32);
    ~Opensmt();

    SMTConfig& getConfig() { return *config; }
    Logic& getLogic() { return thandler->getLogic(); }
    LRALogic& getLRALogic()
    {
        LRATheory& t = (LRATheory&)thandler->getTheory();
        return t.getLogic();
    }
    LIALogic& getLIALogic()
    {
        LIATheory& t = (LIATheory&)thandler->getTheory();
        return t.getLogic();
    }
    CUFLogic& getCUFLogic() {
        CUFTheory& t = (CUFTheory&)thandler->getTheory();
        return t.getLogic();
    }
    MainSolver& getMainSolver() { return *mainSolver; }
    SimpSMTSolver& getSolver() { return *solver; }
private:
    SMTConfig *config;
    Theory *theory;
    THandler *thandler;
    SimpSMTSolver *solver;
    MainSolver *mainSolver;
};

#endif //OPENSMT_H
