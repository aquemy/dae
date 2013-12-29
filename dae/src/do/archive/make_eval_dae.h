 
//-----------------------------------------------------------------------------
/*
* <make_eval_dae.h>
* Copyright (C) TAO Project-Team, INRIA Saclay-LRI && Thales Group, 2011-2012
* DESCARWIN ANR project 
* Author: <Mostepha R. Khouadjia>
* Copyright: See COPYING file that comes with this distribution
*
*
*///-----------------------------------------------------------------------------
 

#ifndef MAKE_EVAL_DAE_H_
#define	MAKE_EVAL_DAE_H_


#include <utils/eoParser.h>
#include <utils/eoState.h>
#include <eoEvalFuncCounter.h>
#include <daex.h>
#include <evaluation/yahsp.h>
#include <apply.h>
/*
 * This function creates an eoEvalFuncCounter<eoFlowShop> that can later be used to evaluate an individual.
 * @param eoParser& _parser  to get user parameters
 * @param eoState& _state  to store the memory
 */
template<class EOT> 
eoEvalFuncCounter<EOT> &   do_make_eval(eoParser& _parser, eoState& _state,eoPop<EOT> & _pop,   daex::Init<EOT> & _init)
{

 	
	 
	unsigned int b_max_init = _parser.createParam( (unsigned int)1e4, "bmax-init", 
        "Number of allowed expanded nodes for the initial computation of b_max", 'B', "Evaluation" ).value();
        
        unsigned int fitness_weight = _parser.createParam( (unsigned int)10, "fitness-weight", "Unknown weight in the feasible and unfeasible fitness computation", 'W', "Evaluation" ).value();
        
        unsigned int fitness_penalty = _parser.createParam( (unsigned int)2, "fitness-penalty", "Penalty in the unfeasible fitnesses computation", 'w', "Evaluation" ).value();
        
        
        daeYahspEvalInit<EOT> *eval_yahsp_init = new daeYahspEvalInit<EOT> ( _pop.size(), _init.l_max(), b_max_init, b_max_init, fitness_weight, fitness_penalty );

	_state.storeFunctor(eval_yahsp_init);
 

	unsigned int b_max_fixed = _parser.createParam( (unsigned int)0, "bmax-fixed", 
        
        "Fixed number of allowed expanded nodes. Overrides bmaxinit if != 0", 'b', "Evaluation" ).value();
    
         double b_max_last_weight = _parser.createParam( (double)3, "bmax-last-weight",
            "Weighting for the b_max used during the last search towards the end goal (must be strictly positive)", 'T', "Evaluation" ).value();
 
   	 if( b_max_last_weight <= 0 ) {
        std::cout << "bmax-last-weight must be strictly positive (=" << b_max_last_weight << ") type --help for usage." << std::endl;
        exit(1);
    	}
    
    	double b_max_quantile = _parser.createParam( (double)0.5, "bmax-quantile", 
            "Quantile to use for estimating b_max (in [0,1], 0.5=median)", 'Q', "Evaluation" ).value();
    
    	if( b_max_quantile < 0 || b_max_quantile > 1 ) {
        std::cout << "bmax-quantile must be a double in [0,1] (=" << b_max_quantile << ") type --help for usage." << std::endl;
        exit(1);
    	}

    
	unsigned int b_max_in;

    	// if we want to estimate the initial b_max other a first search step
    	if( b_max_fixed == 0 ) {
        // FIRST INIT LOOP FOR B_MAX ESTIMATION
 
        // start the eval on the first random pop
       // eoPopLoopEval<daex::Decomposition> eval_init( _eval_yahsp_init );
        apply(*eval_yahsp_init, _pop);
        //eval_init( _pop, _pop );

        // estimate the b_max from the eval results
        b_max_in = eval_yahsp_init -> estimate_b_max( b_max_quantile );

    	// if we want a fixed b_max for the whole search
    	} else  // if b_max_in != 0
        	b_max_in = b_max_fixed;
        
   

	assert( b_max_in > 0 );
    
    	// The b_max for the very last search towards the end goal
    	// is the estimated b_max * a given weight (3 by default)
    	unsigned int b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );

    	assert( b_max_last > 0 );
    
    // nested evals:

    // eval that uses the correct b_max
    	daeYahspEval<EOT> *eval_yahsp = new daeYahspEval <EOT>( _init.l_max(), b_max_in, b_max_last, fitness_weight, fitness_penalty );
    	
    	_state.storeFunctor(eval_yahsp);
    	
    	
    	// counter, for checkpointing
    	eoEvalFuncCounter<EOT> *eval_counter = new eoEvalFuncCounter<EOT>( *eval_yahsp, "Eval.\t" );
    	
    	_state.storeFunctor(eval_counter);
    	
    	return *eval_counter;
    	
    	
}
 

#endif  MAKE_EVAL_DAE_H_ /* MAKE_EVAL_DAE_H_*/