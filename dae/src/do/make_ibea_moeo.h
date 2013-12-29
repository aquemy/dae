 
#ifndef MAKE_IBEA_MOEO_H_
#define MAKE_IBEA_MOEO_H_

#include <stdlib.h>
#include <eoContinue.h>
#include <eoEvalFunc.h>
#include <eoGeneralBreeder.h>
#include <eoGenOp.h>
#include <utils/eoParser.h>
#include <utils/eoState.h>

#include <algo/moeoEA.h>
#include <algo/moeoEasyEA.h>
#include <algo/moeoIBEA.h>
 
 


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
moeoIBEA < MOEOT > & do_make_ibea_moeo(eoParser & _parser, eoState & _state, eoEvalFunc < MOEOT > & _eval, eoContinue < MOEOT > & _continue, eoGenOp < MOEOT > & _op)
{

  /* the objective vector type */
  typedef typename MOEOT::ObjectiveVector ObjectiveVector;


  /* the fitness assignment strategy */
  std::string & indicatorParam = _parser.createParam(std::string("Epsilon"), "indicator",
                                 "Binary indicator for IndicatorBased: Epsilon, Hypervolume", 'i',
                                 "Evolution Engine").value();
  
  double rho = _parser.createParam(1.1, "rho", "reference point for the hypervolume indicator", '\0',
                                   "Evolution Engine").value();
  double kappa = _parser.createParam(0.05, "kappa", "Scaling factor kappa for IndicatorBased", 'k',
                                     "Evolution Engine").value();
  // metric
  moeoNormalizedSolutionVsSolutionBinaryMetric < ObjectiveVector, double > *metric;
  if (indicatorParam == std::string("Epsilon"))
        {
          metric = new moeoAdditiveEpsilonBinaryMetric < ObjectiveVector >;
        }
      else if (indicatorParam == std::string("Hypervolume"))
        {
          metric = new moeoHypervolumeBinaryMetric < ObjectiveVector > (rho);
        }
      else
        {
          std::string stmp = std::string("Invalid binary quality indicator: ") + indicatorParam;
          throw std::runtime_error(stmp.c_str());
        }
       
    
     // _state.storeFunctor(metric);
 
    /// the moeoIBEA
 
   moeoIBEA < MOEOT > * algo = new moeoIBEA < MOEOT > (_continue, _eval, _op,  *metric, kappa);
  
  
   //_state.storeFunctor(algo);
  
   return *algo;

}

#endif /*MAKE_EA_MOEO_H_*/