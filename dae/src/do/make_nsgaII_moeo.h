 

#ifndef MAKE_NSGAII_MOEO_H_
#define MAKE_NSGAII_MOEO_H_


#include <stdlib.h>
#include <eoContinue.h>
#include <eoEvalFunc.h>
#include <eoGeneralBreeder.h>
#include <eoGenOp.h>
#include <utils/eoParser.h>
#include <utils/eoState.h>

#include <algo/moeoEA.h>
#include <algo/moeoEasyEA.h>
#include <algo/moeoNSGAII.h>
 



/**
 * This functions allows to build a moeoEA from the parser
 * @param _parser the parser
 * @param _state to store allocated objects
 * @param _eval the funtions evaluator
 * @param _continue the stopping crietria
 * @param _op the variation operators
 * @param _archive the archive of non-dominated solutions
 */
template < class MOEOT >
moeoNSGAII < MOEOT > & do_make_nsgaII_moeo(eoParser & _parser, eoState & _state, eoEvalFunc < MOEOT > & _eval, eoContinue < MOEOT > & _continue, eoGenOp < MOEOT > & _op, moeoArchive < MOEOT > & _archive)
{

  /* the objective vector type */
  typedef typename MOEOT::ObjectiveVector ObjectiveVector;

  // the eoEasyEA
  moeoNSGAII < MOEOT > * algo = new  moeoNSGAII < MOEOT > (_continue, _eval, _op);
  _state.storeFunctor(algo);
  return *algo;

}

#endif /*MAKE_NSGAII_MOEO_H_*/
