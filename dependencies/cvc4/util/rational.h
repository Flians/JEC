/*********************                                                        */
/*! \file rational.h.in
 ** \verbatim
 ** Top contributors (to current version):
 **   Morgan Deters, Tim King
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief A multi-precision rational constant
 **
 ** A multi-precision rational constant.
 **/

// these gestures are used to avoid a public header dependence on cvc4autoconfig.h

#if 0
#  define CVC4_NEED_INT64_T_OVERLOADS
#endif

#if /* use CLN */ 0
#  define CVC4_CLN_IMP
#endif /* 0 */
#if /* use GMP */ 1
#  define CVC4_GMP_IMP
#endif /* 1 */

#ifdef CVC4_CLN_IMP
#  include <cvc4/util/rational_cln_imp.h>
#  if SWIG
     %include <cvc4/util/rational_cln_imp.h>
#  endif /* SWIG */
#endif /* CVC4_CLN_IMP */

#ifdef CVC4_GMP_IMP
#  include <cvc4/util/rational_gmp_imp.h>
#  if SWIG
     %include <cvc4/util/rational_gmp_imp.h>
#  endif /* SWIG */
#endif /* CVC4_GMP_IMP */
