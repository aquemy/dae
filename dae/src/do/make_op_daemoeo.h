#ifndef _MAKE_OP_H_
#define	_MAKE_OP_H_
/*
* <make_op_dae.h>
* Copyright (C) TAO Project-Team, INRIA Saclay-LRI && Thales Group, 2011-2012
* DESCARWIN ANR project 
* Author: <Mostepha R. Khouadjia>
* Copyright: See COPYING file that comes with this distribution
*
*
*/

// also need the parser and state includes
#include <utils/eoParser.h>
#include <utils/eoState.h>
#include <daex.h>

namespace daex {

void do_make_variation_param(eoParser &parser)
{
    parser.createParam((unsigned int)2, "radius", 
            "Number of neighbour goals to consider for the addGoal mutation", 'R', "Variation" );
     
    parser.createParam( (double)0.8, "proba-change", 
            "Probability to change an atom for the changeAtom mutation", 'k', "Variation" );

    parser.createParam( (double)0.5, "proba-del-atom", 
            "Average probability to delete an atom for the delAtom mutation", 'p', "Variation" );
     
    parser.createParam( (double)1, "w-delgoal", 
            "Relative weight defining the probability to call the delGoal mutation", 'a', "Variation" ).value();
     
    parser.createParam( (double)1, "w-addgoal", 
           "Relative weight defining the probability to call the addGoal mutation", 'A', "Variation" ).value();
    
    parser.createParam( (double)3, "w-delatom", 
            "Relative weight defining the probability to call the delAtom mutation", 'u', "Variation" ).value();
     
    parser.createParam( (double)1, "w-addatom", 
            "Relative weight defining the probability to call the addAtom mutation", 'd', "Variation" ).value();
            
    parser.createParam( (unsigned int)0, "maxtry-candidate", "Maximum number of atoms to try when searching for a candidate in the changeAtom mutation", 'y', "Variation" );
     
    parser.createParam( (unsigned int)0, "maxtry-mutex", "Maximum number of atoms to try when searching for mutexes in the changeAtom mutation", 'z', "Variation" );

    parser.createParam( (double)0.2, "proba-cross", 
            "Probability to apply a cross-over", 'c', "Variation" );
            
    parser.createParam( (double)0.8, "proba-mut", 
            "Probability to apply one of the mutation", 'm', "Variation" );
}

template <class EOT >
eoGenOp< EOT >  &do_make_op (eoParser& _parser, eoState & _state, daex::pddlLoad & _pddl)
{
    // Crossovers 
    eoQuadOp< EOT > *ptQuad =  new daex::CrossOverTimeFilterHalf< EOT >;
    
    // Store in the state
    _state.storeFunctor (ptQuad);
     

    // Create the CombinedQuadOp
    eoPropCombinedQuadOp< EOT > *ptCombinedQuadOp = new eoPropCombinedQuadOp< EOT >(*ptQuad, 1.0);
     
        
    // don't forget to store the CombinedQuadOp
    _state.storeFunctor(ptCombinedQuadOp);

    // the mutations
    /////////////////
    // the parameters
     // Variation
    
    unsigned int radius = _parser.valueOf<unsigned int>("radius");
    double proba_change = _parser.valueOf<double>("proba-change");
    double proba_del_atom = _parser.valueOf<double>("proba-del-atom");
    double w_delgoal = _parser.valueOf<double>("w-delgoal");
    double w_addgoal = _parser.valueOf<double>("w-addgoal");
    double w_delatom = _parser.valueOf<double>("w-delatom");
    double w_addatom = _parser.valueOf<double>("w-addatom");      
    unsigned int maxtry_candidate = _parser.valueOf<unsigned int>("maxtry-candidate");
    unsigned int maxtry_mutex = _parser.valueOf<unsigned int>("maxtry-mutex");
    
    if ( (proba_change  < 0) || (proba_change  > 1) )
        throw std::runtime_error("Invalid pChange");
    // mutations
    
    
    // Create the CombinedMonOp

    eoMonOp< EOT > *ptMon = new daex::MutationDelGoal< EOT >();
    
    _state.storeFunctor (ptMon);
      
     eoPropCombinedMonOp< EOT > *ptCombinedMonOp = new eoPropCombinedMonOp< EOT >  (*ptMon, w_delgoal); /// à voir
    
//    daex::MutationDelOneAtom delatom;
     ptMon = new  daex::MutationDelAtom< EOT >(proba_del_atom) ;     
    
    
    _state.storeFunctor(ptMon); 
    
      ptCombinedMonOp -> add(*ptMon,   w_delatom  ); 
        
       
    // partition, radius, l_max
     ptMon = new daex::MutationAddGoal< EOT >( _pddl.chronoPartitionAtom() ,radius /*,
     init.l_max()*/);
     
     _state.storeFunctor(ptMon); 
     
     
     ptCombinedMonOp  -> add(*ptMon, w_addgoal);
     
     
      ptMon = new daex::MutationChangeAddAtom< EOT >( _pddl.chronoPartitionAtom(), proba_change, maxtry_candidate, maxtry_mutex );
      
      _state.storeFunctor(ptMon); 
      
      ptCombinedMonOp  -> add(*ptMon, w_addatom); 
      
      _state.storeFunctor(ptCombinedMonOp); 
     

  // now build the eoGenOp:
  // to simulate SGA (crossover with proba pCross + mutation with proba pMut
  // we must construct
  //     a sequential combination of
  //          with proba 1, a proportional combination of
  //                        a QuadCopy and our crossover
  //          with proba pMut, our mutation

  // the crossover - with probability pCross
  
    double proba_cross = _parser.valueOf<double>("proba-cross");
    double proba_mut = _parser.valueOf<double>("proba-mut");
                    
    // minimum check
    if ( (proba_cross  < 0) || (proba_cross  > 1) )
        throw std::runtime_error("Invalid pCross");
      
    if ( (proba_mut  < 0) || (proba_mut  > 1) )
        throw std::runtime_error("Invalid pMut");
      
      
    eoProportionalOp< EOT > * cross = new
  
    eoProportionalOp< EOT > ;
  
    _state.storeFunctor(cross);
  
    ptQuad = new eoQuadCloneOp< EOT >;
  
    _state.storeFunctor(ptQuad);
  
    cross->add(*ptCombinedQuadOp, proba_cross); // user crossover
  
    cross->add(*ptQuad, 1 - proba_cross); // clone operator

  // now the sequential
  
    eoSequentialOp< EOT > *op = new eoSequentialOp< EOT >;
  
    _state.storeFunctor(op);
  
    op->add(*cross, 1.0);  // always crossover (but clone with prob 1-pCross
  
    op->add(*ptCombinedMonOp, proba_mut);

    // that's it!
    return *op;
}

} // namespace daex

#endif // _MAKE_OP_H_
