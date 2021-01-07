/*********************                                                        */
/*! \file datatype.h
 ** \verbatim
 ** Top contributors (to current version):
 **   Andrew Reynolds, Morgan Deters, Tim King
 ** This file is part of the CVC4 project.
 ** Copyright (c) 2009-2020 by the authors listed in the file AUTHORS
 ** in the top-level source directory) and their institutional affiliations.
 ** All rights reserved.  See the file COPYING in the top-level source
 ** directory for licensing information.\endverbatim
 **
 ** \brief A class representing a Datatype definition
 **
 ** A class representing a Datatype definition for the theory of
 ** inductive datatypes.
 **/

#include <cvc4/cvc4_public.h>

#ifndef CVC4__DATATYPE_H
#define CVC4__DATATYPE_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace CVC4 {
  // messy; Expr needs Datatype (because it's the payload of a
  // CONSTANT-kinded expression), and Datatype needs Expr.
  //class CVC4_PUBLIC Datatype;
  class CVC4_PUBLIC DatatypeIndexConstant;
}/* CVC4 namespace */

#include <cvc4/base/exception.h>
#include <cvc4/expr/expr.h>
#include <cvc4/expr/type.h>
#include <cvc4/util/hash.h>


namespace CVC4 {

class CVC4_PUBLIC ExprManager;

class CVC4_PUBLIC DatatypeConstructor;
class CVC4_PUBLIC DatatypeConstructorArg;

class CVC4_PUBLIC DatatypeConstructorIterator {
  const std::vector<DatatypeConstructor>* d_v;
  size_t d_i;

  friend class Datatype;

  DatatypeConstructorIterator(const std::vector<DatatypeConstructor>& v, bool start) : d_v(&v), d_i(start ? 0 : v.size()) {
  }

public:
  typedef const DatatypeConstructor& value_type;
  const DatatypeConstructor& operator*() const { return (*d_v)[d_i]; }
  const DatatypeConstructor* operator->() const { return &(*d_v)[d_i]; }
  DatatypeConstructorIterator& operator++() { ++d_i; return *this; }
  DatatypeConstructorIterator operator++(int) { DatatypeConstructorIterator i(*this); ++d_i; return i; }
  bool operator==(const DatatypeConstructorIterator& other) const { return d_v == other.d_v && d_i == other.d_i; }
  bool operator!=(const DatatypeConstructorIterator& other) const { return d_v != other.d_v || d_i != other.d_i; }
};/* class DatatypeConstructorIterator */

class CVC4_PUBLIC DatatypeConstructorArgIterator {
  const std::vector<DatatypeConstructorArg>* d_v;
  size_t d_i;

  friend class DatatypeConstructor;

  DatatypeConstructorArgIterator(const std::vector<DatatypeConstructorArg>& v, bool start) : d_v(&v), d_i(start ? 0 : v.size()) {
  }

public:
  typedef const DatatypeConstructorArg& value_type;
  const DatatypeConstructorArg& operator*() const { return (*d_v)[d_i]; }
  const DatatypeConstructorArg* operator->() const { return &(*d_v)[d_i]; }
  DatatypeConstructorArgIterator& operator++() { ++d_i; return *this; }
  DatatypeConstructorArgIterator operator++(int) { DatatypeConstructorArgIterator i(*this); ++d_i; return i; }
  bool operator==(const DatatypeConstructorArgIterator& other) const { return d_v == other.d_v && d_i == other.d_i; }
  bool operator!=(const DatatypeConstructorArgIterator& other) const { return d_v != other.d_v || d_i != other.d_i; }
};/* class DatatypeConstructorArgIterator */

/**
 * An exception that is thrown when a datatype resolution fails.
 */
class CVC4_PUBLIC DatatypeResolutionException : public Exception {
 public:
  inline DatatypeResolutionException(std::string msg);
};/* class DatatypeResolutionException */

/**
 * A holder type (used in calls to DatatypeConstructor::addArg())
 * to allow a Datatype to refer to itself.  Self-typed fields of
 * Datatypes will be properly typed when a Type is created for the
 * Datatype by the ExprManager (which calls Datatype::resolve()).
 */
class CVC4_PUBLIC DatatypeSelfType {
};/* class DatatypeSelfType */

class DTypeSelector;

/**
 * An unresolved type (used in calls to
 * DatatypeConstructor::addArg()) to allow a Datatype to refer to
 * itself or to other mutually-recursive Datatypes.  Unresolved-type
 * fields of Datatypes will be properly typed when a Type is created
 * for the Datatype by the ExprManager (which calls
 * Datatype::resolve()).
 */
class CVC4_PUBLIC DatatypeUnresolvedType {
  std::string d_name;
public:
  inline DatatypeUnresolvedType(std::string name);
  inline std::string getName() const;
};/* class DatatypeUnresolvedType */

/**
 * A Datatype constructor argument (i.e., a Datatype field).
 */
class CVC4_PUBLIC DatatypeConstructorArg {
  friend class DatatypeConstructor;
  friend class Datatype;

 public:
  /** Get the name of this constructor argument. */
  std::string getName() const;

  /**
   * Get the selector for this constructor argument; this call is
   * only permitted after resolution.
   */
  Expr getSelector() const;

  /**
   * Get the associated constructor for this constructor argument;
   * this call is only permitted after resolution.
   */
  Expr getConstructor() const;

  /**
   * Get the type of the selector for this constructor argument;
   * this call is only permitted after resolution.
   */
  SelectorType getType() const;

  /**
   * Get the range type of this argument.
   */
  Type getRangeType() const;

  /**
   * Returns true iff this constructor argument has been resolved.
   */
  bool isResolved() const;

  /** prints this datatype constructor argument to stream */
  void toStream(std::ostream& out) const;

 private:
  /** The internal representation */
  std::shared_ptr<DTypeSelector> d_internal;
  /** The selector */
  Expr d_selector;
  /** is this selector unresolved? */
  bool isUnresolvedSelf() const;
  /** constructor */
  DatatypeConstructorArg(std::string name, Expr selector);
};/* class DatatypeConstructorArg */

class Printer;

/** sygus datatype constructor printer
 *
 * This is a virtual class that is used to specify
 * a custom printing callback for sygus terms. This is
 * useful for sygus grammars that include defined
 * functions or let expressions.
 */
class CVC4_PUBLIC SygusPrintCallback
{
 public:
  SygusPrintCallback() {}
  virtual ~SygusPrintCallback() {}
  /**
   * Writes the term that sygus datatype expression e
   * encodes to stream out. p is the printer that
   * requested that expression e be written on output
   * stream out. Calls may be made to p to print
   * subterms of e.
   */
  virtual void toStreamSygus(const Printer* p,
                             std::ostream& out,
                             Expr e) const = 0;
};

class DTypeConstructor;

/**
 * A constructor for a Datatype.
 */
class CVC4_PUBLIC DatatypeConstructor {
  friend class Datatype;

 public:
  /** The type for iterators over constructor arguments. */
  typedef DatatypeConstructorArgIterator iterator;
  /** The (const) type for iterators over constructor arguments. */
  typedef DatatypeConstructorArgIterator const_iterator;

  /**
   * Create a new Datatype constructor with the given name for the
   * constructor.  The actual constructor and tester (meaning, the Exprs
   * representing operators for these entities) aren't created until
   * resolution time.
   * weight is the value that this constructor carries when computing size.
   * For example, if A, B, C have weights 0, 1, and 3 respectively, then
   * C( B( A() ), B( A() ) ) has size 5.
   */
  explicit DatatypeConstructor(std::string name, unsigned weight = 1);

  ~DatatypeConstructor() {}
  /**
   * Add an argument (i.e., a data field) of the given name and type
   * to this Datatype constructor.  Selector names need not be unique;
   * they are for convenience and pretty-printing only.
   */
  void addArg(std::string selectorName, Type selectorType);

  /**
   * Add an argument (i.e., a data field) of the given name to this
   * Datatype constructor that refers to an as-yet-unresolved
   * Datatype (which may be mutually-recursive).  Selector names need
   * not be unique; they are for convenience and pretty-printing only.
   */
  void addArg(std::string selectorName, DatatypeUnresolvedType selectorType);

  /**
   * Add a self-referential (i.e., a data field) of the given name
   * to this Datatype constructor that refers to the enclosing
   * Datatype.  For example, using the familiar "nat" Datatype, to
   * create the "pred" field for "succ" constructor, one uses
   * succ::addArg("pred", DatatypeSelfType())---the actual Type
   * cannot be passed because the Datatype is still under
   * construction.  Selector names need not be unique; they are for
   * convenience and pretty-printing only.
   *
   * This is a special case of
   * DatatypeConstructor::addArg(std::string, DatatypeUnresolvedType).
   */
  void addArg(std::string selectorName, DatatypeSelfType);

  /** Get the name of this Datatype constructor. */
  std::string getName() const;

  /**
   * Get the constructor operator of this Datatype constructor.  The
   * Datatype must be resolved.
   */
  Expr getConstructor() const;

  /**
   * Get the tester operator of this Datatype constructor.  The
   * Datatype must be resolved.
   */
  Expr getTester() const;

  /** get sygus op
   *
   * This method returns the operator or
   * term that this constructor represents
   * in the sygus encoding. This may be a
   * builtin operator, defined function, variable,
   * or constant that this constructor encodes in this
   * deep embedding.
   */
  Expr getSygusOp() const;
  /** is this a sygus identity function?
   *
   * This returns true if the sygus operator of this datatype constructor is
   * of the form (lambda (x) x).
   */
  bool isSygusIdFunc() const;
  /** get sygus print callback
   *
   * This class stores custom ways of printing
   * sygus datatype constructors, for instance,
   * to handle defined or let expressions that
   * appear in user-provided grammars.
   */
  std::shared_ptr<SygusPrintCallback> getSygusPrintCallback() const;
  /** get weight
   *
   * Get the weight of this constructor. This value is used when computing the
   * size of datatype terms that involve this constructor.
   */
  unsigned getWeight() const;

  /**
   * Get the number of arguments (so far) of this Datatype constructor.
   */
  size_t getNumArgs() const;

  /**
   * Get the specialized constructor type for a parametric
   * constructor; this call is only permitted after resolution.
   * Given a (concrete) returnType, the constructor's concrete
   * type in this parametric datatype is returned.
   *
   * For instance, if the datatype is list[T], with constructor
   * "cons[T]" of type "T -> list[T] -> list[T]", then calling
   * this function with "list[int]" will return the concrete
   * "cons" constructor type for lists of int---namely,
   * "int -> list[int] -> list[int]".
   */
  Type getSpecializedConstructorType(Type returnType) const;

  /**
   * Return the cardinality of this constructor (the product of the
   * cardinalities of its arguments).
   */
  Cardinality getCardinality(Type t) const;

  /**
   * Return true iff this constructor is finite (it is nullary or
   * each of its argument types are finite).  This function can
   * only be called for resolved constructors.
   */
  bool isFinite(Type t) const;
  /**
   * Return true iff this constructor is finite (it is nullary or
   * each of its argument types are finite) under assumption
   * uninterpreted sorts are finite.  This function can
   * only be called for resolved constructors.
   */
  bool isInterpretedFinite(Type t) const;

  /**
   * Returns true iff this Datatype constructor has already been
   * resolved.
   */
  bool isResolved() const;

  /** Get the beginning iterator over DatatypeConstructor args. */
  iterator begin();
  /** Get the ending iterator over DatatypeConstructor args. */
  iterator end();
  /** Get the beginning const_iterator over DatatypeConstructor args. */
  const_iterator begin() const;
  /** Get the ending const_iterator over DatatypeConstructor args. */
  const_iterator end() const;

  /** Get the ith DatatypeConstructor arg. */
  const DatatypeConstructorArg& operator[](size_t index) const;

  /**
   * Get the DatatypeConstructor arg named.  This is a linear search
   * through the arguments, so in the case of multiple,
   * similarly-named arguments, the first is returned.
   */
  const DatatypeConstructorArg& operator[](std::string name) const;

  /**
   * Get the selector named.  This is a linear search
   * through the arguments, so in the case of multiple,
   * similarly-named arguments, the selector for the first
   * is returned.
   */
  Expr getSelector(std::string name) const;
  /**
   * Get argument type. Returns the return type of the i^th selector of this
   * constructor.
   */
  Type getArgType(unsigned i) const;

  /** get selector internal
   *
   * This gets selector for the index^th argument
   * of this constructor. The type dtt is the datatype
   * type whose datatype is the owner of this constructor,
   * where this type may be an instantiated parametric datatype.
   *
   * If shared selectors are enabled,
   * this returns a shared (constructor-agnotic) selector, which
   * in the terminology of "Datatypes with Shared Selectors", is:
   *   sel_{dtt}^{T,atos(T,C,index)}
   * where C is this constructor, and T is the type
   * of the index^th field of this constructor.
   * The semantics of sel_{dtt}^{T,n}( t ) is the n^th field of
   * type T of constructor term t if one exists, or is
   * unconstrained otherwise.
   */
  Expr getSelectorInternal(Type dtt, size_t index) const;

  /** get selector index internal
   *
   * This gets the argument number of this constructor
   * that the selector sel accesses. It returns -1 if the
   * selector sel is not a selector for this constructor.
   *
   * In the terminology of "Datatypes with Shared Selectors",
   * if sel is sel_{dtt}^{T,index} for some (T, index), where
   * dtt is the datatype type whose datatype is the owner
   * of this constructor, then this method returns
   *   stoa(T,C,index)
   */
  int getSelectorIndexInternal( Expr sel ) const;

  /** involves external type
   *
   * Get whether this constructor has a subfield
   * in any constructor that is not a datatype type.
   */
  bool involvesExternalType() const;
  /** involves external type
   *
   * Get whether this constructor has a subfield
   * in any constructor that is an uninterpreted type.
   */
  bool involvesUninterpretedType() const;

  /** set sygus
   *
   * Set that this constructor is a sygus datatype constructor that encodes
   * operator op. spc is the sygus callback of this datatype constructor,
   * which is stored in a shared pointer.
   */
  void setSygus(Expr op, std::shared_ptr<SygusPrintCallback> spc);

  /**
   * Get the list of arguments to this constructor.
   */
  const std::vector<DatatypeConstructorArg>* getArgs() const;

  /** prints this datatype constructor to stream */
  void toStream(std::ostream& out) const;

 private:
  /** The internal representation */
  std::shared_ptr<DTypeConstructor> d_internal;
  /** The constructor */
  Expr d_constructor;
  /** the arguments of this constructor */
  std::vector<DatatypeConstructorArg> d_args;
  /** sygus print callback */
  std::shared_ptr<SygusPrintCallback> d_sygus_pc;
};/* class DatatypeConstructor */

class DType;

/**
 * The representation of an inductive datatype.
 *
 * This is far more complicated than it first seems.  Consider this
 * datatype definition:
 *
 *   DATATYPE nat =
 *     succ(pred: nat)
 *   | zero
 *   END;
 *
 * You cannot define "nat" until you have a Type for it, but you
 * cannot have a Type for it until you fill in the type of the "pred"
 * selector, which needs the Type.  So we have a chicken-and-egg
 * problem.  It's even more complicated when we have mutual recursion
 * between datatypes, since the CVC presentation language does not
 * require forward-declarations.  Here, we define trees of lists that
 * contain trees of lists (etc):
 *
 *   DATATYPE
 *     tree = node(left: tree, right: tree) | leaf(list),
 *     list = cons(car: tree, cdr: list) | nil
 *   END;
 *
 * Note that while parsing the "tree" definition, we have to take it
 * on faith that "list" is a valid type.  We build Datatype objects to
 * describe "tree" and "list", and their constructors and constructor
 * arguments, but leave any unknown types (including self-references)
 * in an "unresolved" state.  After parsing the whole DATATYPE block,
 * we create a DatatypeType through
 * ExprManager::mkMutualDatatypeTypes().  The ExprManager creates a
 * DatatypeType for each, but before "releasing" this type into the
 * wild, it does a round of in-place "resolution" on each Datatype by
 * calling Datatype::resolve() with a map of string -> DatatypeType to
 * allow the datatype to construct the necessary testers and
 * selectors.
 *
 * An additional point to make is that we want to ease the burden on
 * both the parser AND the users of the CVC4 API, so this class takes
 * on the task of generating its own selectors and testers, for
 * instance.  That means that, after reifying the Datatype with the
 * ExprManager, the parser needs to go through the (now-resolved)
 * Datatype and request the constructor, selector, and tester terms.
 * See src/parser/parser.cpp for how this is done.  For API usage
 * ideas, see test/unit/util/datatype_black.h.
 *
 * Datatypes may also be defined parametrically, such as this example:
 *
 *  DATATYPE
 *    list[T] = cons(car : T, cdr : list[T]) | null,
 *    tree = node(children : list[tree]) | leaf
 *  END;
 *
 * Here, the definition of the parametric datatype list, where T is a type variable.
 * In other words, this defines a family of types list[C] where C is any concrete
 * type.  Datatypes can be parameterized over multiple type variables using the
 * syntax sym[ T1, ..., Tn ] = ...,
 *
 */
class CVC4_PUBLIC Datatype {
  friend class DatatypeConstructor;
  friend class ExprManager;  // for access to resolve()
  friend class NodeManager;  // temporary, for access to d_internal
 public:
  /**
   * Get the datatype of a constructor, selector, or tester operator.
   */
  static const Datatype& datatypeOf(Expr item) CVC4_PUBLIC;

  /**
   * Get the index of a constructor or tester in its datatype, or the
   * index of a selector in its constructor.  (Zero is always the
   * first index.)
   */
  static size_t indexOf(Expr item) CVC4_PUBLIC;

  /**
   * Get the index of constructor corresponding to selector.  (Zero is
   * always the first index.)
   */
  static size_t cindexOf(Expr item) CVC4_PUBLIC;

  /**
   * Same as above, but without checks. These methods should be used by
   * internal (Node-level) code.
   */
  static size_t indexOfInternal(Expr item);
  static size_t cindexOfInternal(Expr item);

  /** The type for iterators over constructors. */
  typedef DatatypeConstructorIterator iterator;
  /** The (const) type for iterators over constructors. */
  typedef DatatypeConstructorIterator const_iterator;

  /** Create a new Datatype of the given name. */
  explicit Datatype(ExprManager* em, std::string name, bool isCo = false);

  /**
   * Create a new Datatype of the given name, with the given
   * parameterization.
   */
  Datatype(ExprManager* em,
           std::string name,
           const std::vector<Type>& params,
           bool isCo = false);

  ~Datatype();

  /** Add a constructor to this Datatype.
   *
   * Notice that constructor names need not
   * be unique; they are for convenience and pretty-printing only.
   */
  void addConstructor(const DatatypeConstructor& c);

  /** set sygus
   *
   * This marks this datatype as a sygus datatype.
   * A sygus datatype is one that represents terms of type st
   * via a deep embedding described in Section 4 of
   * Reynolds et al. CAV 2015. We say that this sygus datatype
   * "encodes" its sygus type st in the following.
   *
   * st : the type this datatype encodes (this can be Int, Bool, etc.),
   * bvl : the list of arguments for the synth-fun
   * allow_const : whether all constants are (implicitly) allowed by the
   * datatype
   * allow_all : whether all terms are (implicitly) allowed by the datatype
   *
   * Notice that allow_const/allow_all do not reflect the constructors
   * for this datatype, and instead are used solely for relaxing constraints
   * when doing solution reconstruction (Figure 5 of Reynolds et al.
   * CAV 2015).
   */
  void setSygus( Type st, Expr bvl, bool allow_const, bool allow_all );
  /** add sygus constructor
   *
   * This adds a sygus constructor to this datatype, where
   * this datatype should be currently unresolved.
   *
   * op : the builtin operator, constant, or variable that
   *      this constructor encodes
   * cname : the name of the constructor (for printing only)
   * cargs : the arguments of the constructor
   * spc : an (optional) callback that is used for custom printing. This is
   *       to accomodate user-provided grammars in the sygus format.
   *
   * It should be the case that cargs are sygus datatypes that
   * encode the arguments of op. For example, a sygus constructor
   * with op = PLUS should be such that cargs.size()>=2 and
   * the sygus type of cargs[i] is Real/Int for each i.
   *
   * weight denotes the value added by the constructor when computing the size
   * of datatype terms. Passing a value <0 denotes the default weight for the
   * constructor, which is 0 for nullary constructors and 1 for non-nullary
   * constructors.
   */
  void addSygusConstructor(Expr op,
                           const std::string& cname,
                           const std::vector<Type>& cargs,
                           std::shared_ptr<SygusPrintCallback> spc = nullptr,
                           int weight = -1);
  /**
   * Same as above, with builtin kind k.
   */
  void addSygusConstructor(Kind k,
                           const std::string& cname,
                           const std::vector<Type>& cargs,
                           std::shared_ptr<SygusPrintCallback> spc = nullptr,
                           int weight = -1);

  /** set that this datatype is a tuple */
  void setTuple();

  /** set that this datatype is a record */
  void setRecord();

  /** Get the name of this Datatype. */
  std::string getName() const;

  /** Get the number of constructors (so far) for this Datatype. */
  size_t getNumConstructors() const;

  /** Is this datatype parametric? */
  bool isParametric() const;

  /** Get the nubmer of type parameters */
  size_t getNumParameters() const;

  /** Get parameter */
  Type getParameter(unsigned int i) const;

  /** Get parameters */
  std::vector<Type> getParameters() const;

  /** is this a co-datatype? */
  bool isCodatatype() const;

  /** is this a sygus datatype? */
  bool isSygus() const;

  /** is this a tuple datatype? */
  bool isTuple() const;

  /** is this a record datatype? */
  bool isRecord() const;

  /** get the record representation for this datatype */
  Record* getRecord() const;

  /**
   * Return the cardinality of this datatype.
   * The Datatype must be resolved.
   *
   * The version of this method that takes Type t is required
   * for parametric datatypes, where t is an instantiated
   * parametric datatype type whose datatype is this class.
   */
  Cardinality getCardinality(Type t) const;
  Cardinality getCardinality() const;

  /**
   * Return true iff this Datatype has finite cardinality. If the
   * datatype is not well-founded, this method returns false. The
   * Datatype must be resolved or an exception is thrown.
   *
   * The version of this method that takes Type t is required
   * for parametric datatypes, where t is an instantiated
   * parametric datatype type whose datatype is this class.
   */
  bool isFinite(Type t) const;
  bool isFinite() const;

  /**
   * Return true iff this  Datatype is finite (all constructors are
   * finite, i.e., there  are finitely  many ground terms) under the
   * assumption unintepreted sorts are finite. If the
   * datatype is  not well-founded, this method returns false.  The
   * Datatype must be resolved or an exception is thrown.
   *
   * The versions of these methods that takes Type t is required
   * for parametric datatypes, where t is an instantiated
   * parametric datatype type whose datatype is this class.
   */
  bool isInterpretedFinite(Type t) const;
  bool isInterpretedFinite() const;

  /** is well-founded
   *
   * Return true iff this datatype is well-founded (there exist finite
   * values of this type).
   * This datatype must be resolved or an exception is thrown.
   */
  bool isWellFounded() const;
  /** has nested recursion
   *
   * Return true iff this datatype has nested recursion.
   * This datatype must be resolved or an exception is thrown.
   */
  bool hasNestedRecursion() const;

  /** is recursive singleton
   *
   * Return true iff this datatype is a recursive singleton
   * (a recursive singleton is a recursive datatype with only
   * one infinite value). For details, see Reynolds et al. CADE 2015.
   *
   * The versions of these methods that takes Type t is required
   * for parametric datatypes, where t is an instantiated
   * parametric datatype type whose datatype is this class.
   */
  bool isRecursiveSingleton(Type t) const;
  bool isRecursiveSingleton() const;

  /** recursive single arguments
   *
   * Get recursive singleton argument types (uninterpreted sorts that the
   * cardinality of this datatype is dependent upon). For example, for :
   *   stream :=  cons( head1 : U1, head2 : U2, tail : stream )
   * Then, the recursive singleton argument types of stream are { U1, U2 },
   * since if U1 and U2 have cardinality one, then stream has cardinality
   * one as well.
   *
   * The versions of these methods that takes Type t is required
   * for parametric datatypes, where t is an instantiated
   * parametric datatype type whose datatype is this class.
  */
  unsigned getNumRecursiveSingletonArgTypes(Type t) const;
  Type getRecursiveSingletonArgType(Type t, unsigned i) const;
  unsigned getNumRecursiveSingletonArgTypes() const;
  Type getRecursiveSingletonArgType(unsigned i) const;

  /**
   * Construct and return a ground term of this Datatype.  The
   * Datatype must be both resolved and well-founded, or else an
   * exception is thrown.
   *
   * This method takes a Type t, which is a datatype type whose
   * datatype is this class, which may be an instantiated datatype
   * type if this datatype is parametric.
   */
  Expr mkGroundTerm(Type t) const;
  /** Make ground value
   *
   * Same as above, but constructs a constant value instead of a ground term.
   * These two notions typically coincide. However, for uninterpreted sorts,
   * they do not: mkGroundTerm returns a fresh variable whereas mkValue returns
   * an uninterpreted constant. The motivation for mkGroundTerm is that
   * unintepreted constants should never appear in lemmas. The motivation for
   * mkGroundValue is for things like type enumeration and model construction.
   */
  Expr mkGroundValue(Type t) const;

  /**
   * Get the DatatypeType associated to this Datatype.  Can only be
   * called post-resolution.
   */
  DatatypeType getDatatypeType() const;

  /**
   * Get the DatatypeType associated to this (parameterized) Datatype.  Can only be
   * called post-resolution.
   */
  DatatypeType getDatatypeType(const std::vector<Type>& params) const;

  /**
   * Return true iff the two Datatypes are the same.
   *
   * We need == for mkConst(Datatype) to properly work---since if the
   * Datatype Expr requested is the same as an already-existing one,
   * we need to return that one.  For that, we have a hash and
   * operator==.  We provide != for symmetry.  We don't provide
   * operator<() etc. because given two Datatype Exprs, you could
   * simply compare those rather than the (bare) Datatypes.  This
   * means, though, that Datatype cannot be stored in a sorted list or
   * RB tree directly, so maybe we can consider adding these
   * comparison operators later on.
   */
  bool operator==(const Datatype& other) const;
  /** Return true iff the two Datatypes are not the same. */
  bool operator!=(const Datatype& other) const;

  /** Return true iff this Datatype has already been resolved. */
  bool isResolved() const;

  /** Get the beginning iterator over DatatypeConstructors. */
  iterator begin();
  /** Get the ending iterator over DatatypeConstructors. */
  iterator end();
  /** Get the beginning const_iterator over DatatypeConstructors. */
  const_iterator begin() const;
  /** Get the ending const_iterator over DatatypeConstructors. */
  const_iterator end() const;

  /** Get the ith DatatypeConstructor. */
  const DatatypeConstructor& operator[](size_t index) const;

  /**
   * Get the DatatypeConstructor named.  This is a linear search
   * through the constructors, so in the case of multiple,
   * similarly-named constructors, the first is returned.
   */
  const DatatypeConstructor& operator[](std::string name) const;
 
  /**
   * Get the constructor operator for the named constructor.
   * This is a linear search through the constructors, so in
   * the case of multiple, similarly-named constructors, the
   * first is returned.
   *
   * This Datatype must be resolved.
   */
  Expr getConstructor(std::string name) const;

  /** get sygus type
   * This gets the built-in type associated with
   * this sygus datatype, i.e. the type of the
   * term that this sygus datatype encodes.
   */
  Type getSygusType() const;

  /** get sygus var list
   * This gets the variable list of the function
   * to synthesize using this sygus datatype.
   * For example, if we are synthesizing a binary
   * function f where solutions are of the form:
   *   f = (lambda (xy) t[x,y])
   * In this case, this method returns the
   * bound variable list containing x and y.
   */
  Expr getSygusVarList() const;
  /** get sygus allow constants
   *
   * Does this sygus datatype allow constants?
   * Notice that this is not a property of the
   * constructors of this datatype. Instead, it is
   * an auxiliary flag (provided in the call
   * to setSygus).
   */
  bool getSygusAllowConst() const;
  /** get sygus allow all
   *
   * Does this sygus datatype allow all terms?
   * Notice that this is not a property of the
   * constructors of this datatype. Instead, it is
   * an auxiliary flag (provided in the call
   * to setSygus).
   */
  bool getSygusAllowAll() const;

  /** involves external type
   * Get whether this datatype has a subfield
   * in any constructor that is not a datatype type.
   */
  bool involvesExternalType() const;
  /** involves uninterpreted type
   * Get whether this datatype has a subfield
   * in any constructor that is an uninterpreted type.
   */
  bool involvesUninterpretedType() const;

  /**
   * Get the list of constructors.
   */
  const std::vector<DatatypeConstructor>* getConstructors() const;

  /** prints this datatype to stream */
  void toStream(std::ostream& out) const;

 private:
  /** The expression manager that created this datatype */
  ExprManager* d_em;
  /** The internal representation */
  std::shared_ptr<DType> d_internal;
  /** self type */
  Type d_self;
  /** the data of the record for this datatype (if applicable) */
  std::shared_ptr<Record> d_record;
  /** whether the datatype is a record */
  bool d_isRecord;
  /** the constructors of this datatype */
  std::vector<DatatypeConstructor> d_constructors;
  /**
   * Datatypes refer to themselves, recursively, and we have a
   * chicken-and-egg problem.  The DatatypeType around the Datatype
   * cannot exist until the Datatype is finalized, and the Datatype
   * cannot refer to the DatatypeType representing itself until it
   * exists.  resolve() is called by the ExprManager when a Type is
   * ultimately requested of the Datatype specification (that is, when
   * ExprManager::mkDatatypeType() or ExprManager::mkMutualDatatypeTypes()
   * is called).  Has the effect of freezing the object, too; that is,
   * addConstructor() will fail after a call to resolve().
   *
   * The basic goal of resolution is to assign constructors, selectors,
   * and testers.  To do this, any UnresolvedType/SelfType references
   * must be cleared up.  This is the purpose of the "resolutions" map;
   * it includes any mutually-recursive datatypes that are currently
   * under resolution.  The four vectors come in two pairs (so, really
   * they are two maps).  placeholders->replacements give type variables
   * that should be resolved in the case of parametric datatypes.
   *
   * @param resolutions a map of strings to DatatypeTypes currently under
   * resolution
   * @param placeholders the types in these Datatypes under resolution that must
   * be replaced
   * @param replacements the corresponding replacements
   * @param paramTypes the sort constructors in these Datatypes under resolution
   * that must be replaced
   * @param paramReplacements the corresponding (parametric) DatatypeTypes
   */
  void resolve(const std::map<std::string, DatatypeType>& resolutions,
               const std::vector<Type>& placeholders,
               const std::vector<Type>& replacements,
               const std::vector<SortConstructorType>& paramTypes,
               const std::vector<DatatypeType>& paramReplacements);
};/* class Datatype */

/**
 * A hash function for Datatypes.  Needed to store them in hash sets
 * and hash maps.
 */
struct CVC4_PUBLIC DatatypeHashFunction {
  inline size_t operator()(const Datatype& dt) const {
    return std::hash<std::string>()(dt.getName());
  }
  inline size_t operator()(const Datatype* dt) const {
    return std::hash<std::string>()(dt->getName());
  }
  inline size_t operator()(const DatatypeConstructor& dtc) const {
    return std::hash<std::string>()(dtc.getName());
  }
  inline size_t operator()(const DatatypeConstructor* dtc) const {
    return std::hash<std::string>()(dtc->getName());
  }
};/* struct DatatypeHashFunction */



/* stores an index to Datatype residing in NodeManager */
class CVC4_PUBLIC DatatypeIndexConstant {
 public:
  DatatypeIndexConstant(unsigned index);

  unsigned getIndex() const { return d_index; }
  bool operator==(const DatatypeIndexConstant& uc) const
  {
    return d_index == uc.d_index;
  }
  bool operator!=(const DatatypeIndexConstant& uc) const
  {
    return !(*this == uc);
  }
  bool operator<(const DatatypeIndexConstant& uc) const
  {
    return d_index < uc.d_index;
  }
  bool operator<=(const DatatypeIndexConstant& uc) const
  {
    return d_index <= uc.d_index;
  }
  bool operator>(const DatatypeIndexConstant& uc) const
  {
    return !(*this <= uc);
  }
  bool operator>=(const DatatypeIndexConstant& uc) const
  {
    return !(*this < uc);
  }
private:
  const unsigned d_index;
};/* class DatatypeIndexConstant */

std::ostream& operator<<(std::ostream& out, const DatatypeIndexConstant& dic) CVC4_PUBLIC;

struct CVC4_PUBLIC DatatypeIndexConstantHashFunction {
  inline size_t operator()(const DatatypeIndexConstant& dic) const {
    return IntegerHashFunction()(dic.getIndex());
  }
};/* struct DatatypeIndexConstantHashFunction */



// FUNCTION DECLARATIONS FOR OUTPUT STREAMS

std::ostream& operator<<(std::ostream& os, const Datatype& dt) CVC4_PUBLIC;
std::ostream& operator<<(std::ostream& os, const DatatypeConstructor& ctor) CVC4_PUBLIC;
std::ostream& operator<<(std::ostream& os, const DatatypeConstructorArg& arg) CVC4_PUBLIC;

// INLINE FUNCTIONS

inline DatatypeResolutionException::DatatypeResolutionException(std::string msg) :
  Exception(msg) {
}

inline DatatypeUnresolvedType::DatatypeUnresolvedType(std::string name) :
  d_name(name) {
}

inline std::string DatatypeUnresolvedType::getName() const { return d_name; }


}/* CVC4 namespace */

#endif /* CVC4__DATATYPE_H */
