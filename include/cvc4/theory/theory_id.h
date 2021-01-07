/*********************                                                        */
/*! \file theory_id.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Aina Niemetz, Dejan Jovanovic, Mathias Preiner
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief [[ Add one-line brief description here ]]
 **
 ** [[ Add lengthier description here ]]
 ** \todo document this file
 **/

#include <cvc4/cvc4_public.h>

#ifndef CVC4__THEORY__THEORY_ID_H
#define CVC4__THEORY__THEORY_ID_H

#include <iostream>

namespace CVC4 {

namespace theory {

/**
 * IMPORTANT: The order of the theories is important. For example, strings
 *            depends on arith, quantifiers needs to come as the very last.
 *            Do not change this order.
 */
enum TheoryId
{
  THEORY_BUILTIN,
  THEORY_BOOL,
  THEORY_UF,
  THEORY_ARITH,
  THEORY_BV,
  THEORY_FP,
  THEORY_ARRAYS,
  THEORY_DATATYPES,
  THEORY_SEP,
  THEORY_SETS,
  THEORY_STRINGS,
  THEORY_QUANTIFIERS,

  THEORY_LAST
};

const TheoryId THEORY_FIRST = static_cast<TheoryId>(0);
const TheoryId THEORY_SAT_SOLVER = THEORY_LAST;

TheoryId& operator++(TheoryId& id) CVC4_PUBLIC;

std::ostream& operator<<(std::ostream& out, TheoryId theoryId);

std::string getStatsPrefix(TheoryId theoryId) CVC4_PUBLIC;

}  // namespace theory
}  // namespace CVC4
#endif
