 
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
#include "../core/planningEval.h"
#include "../core/planningState.h"
//#include "../core/AggregaEval.h"

namespace daex {

/*
* @brief Create general parameters related to evaluation (mono and multi-objective).
* @param eoParser used to create parameters.
*/
void do_make_eval_param(eoParser &parser)
{
    unsigned int fitness_weight = parser.createParam( (unsigned int)10, "fitness-weight", 
        "Unknown weight in the feasible and unfeasible fitness computation", 'W', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "fitness_weight" << fitness_weight << std::endl;

    unsigned int fitness_penalty = parser.createParam( (unsigned int)2, "fitness-penalty", 
        "Penalty in the unfeasible fitnesses computation", 'w', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "fitness_penalty" << fitness_penalty << std::endl;
 
    unsigned int b_max_init = parser.createParam( (unsigned int)1e4, "bmax-init", "Number of allowed expanded nodes for the initial computation of b_max", 'B', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_init" << b_max_init << std::endl;

    unsigned int b_max_fixed = parser.createParam( (unsigned int)0, "bmax-fixed", "Fixed number of allowed expanded nodes. Overrides bmaxinit if != 0", 'b', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_fixed" << b_max_fixed << std::endl;

    double b_max_last_weight = parser.createParam( (double)3, "bmax-last-weight",
        "Weighting for the b_max used during the last search towards the end goal (must be strictly positive)", 'T', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_last_weight" << b_max_last_weight << std::endl;
 
    double length_weigth = parser.createParam( (double)1, "length_weigth",
        "Weighting for the optimizing length during the search", 'H', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "length_weigth" << length_weigth << std::endl;

    double cost_weigth = parser.createParam( (double)1, "cost_weigth",
        "Weighting for the optimizing cost during the search", 'U', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "cost_weigth" << cost_weigth << std::endl;	 
    	
    double makespan_max_weigth = parser.createParam( (double)1, "makespan_max_weigth",
        "Weighting for the optimizing makespan_max during the search", 'Y', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "makespan_max_weigth" << makespan_max_weigth << std::endl;	
 	 	
    double makespan_add_weigth = parser.createParam((double)1,"makespan_add_weigth",
         "Weighting for the optimizing  makespan_add during the search", 'V', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "makespan_add_weigth" << makespan_add_weigth << std::endl;
	 
    bool rand_yahsp_seed = parser.createParam((bool)true,"rand_yahsp_seed",
         "Random initilaization of yahsp at each optimization (default : true)", 'X', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "rand_yahsp_seed" << rand_yahsp_seed << std::endl;

    double bmax_increase_coef = parser.createParam((double)2, "bmax-increase-coef", 
        "Multiplier increment for the computation of b_max", 'K', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "bmax-increase-coef" << bmax_increase_coef << std::endl;
  
    double bmax_ratio = parser.createParam(0.01, "bmax-ratio",
        "Satisfying proportion of feasible individuals for the computation of b_max", 'J', "Evaluation").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "bmax-ratio" << bmax_ratio << std::endl;
 
}

/*
* @brief Create general parameters related to multi-objective evaluation.
* @param eoParser used to create parameters.
*/
void do_make_eval_mo_param(eoParser &parser)
{
    double astar_weight = parser.createParam((double)1, "astar-weight", // FIXME default value??
        "A* weight within YAHSP", 'H', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "astar-weight" << astar_weight << std::endl;

    bool cost_max = parser.createParam( (bool)false, "cost-max",
        "Use max cost instead of additive costs as the second objective", 'M', "Multi-Objective" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "cost-max" << cost_max << std::endl;
    
    StrategyType stratType = (StrategyType)parser.createParam((unsigned)0,"strat-eval",
         "Evaluation strategy (0 : Static, 1 : Greedy, 2 : Adaptive, 3 : AutoAdaptive)", 'g', "Multi-Objective").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "strat-eval" << stratType << std::endl;
    
    unsigned nbEval = parser.createParam((unsigned)1,"nb-eval",
         "Number of calls to YAHSP before assigning fitness.", 'e', "Multi-Objective").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "nb-eval" << nbEval << std::endl;
}

/*
 * @brief Create an eoEvalFuncCounter<eoFlowShop> that can later be used to evaluate an individual.
 * @param eoParser& _parser  to get user parameters
 * @param eoState& _state  to store the memory
 */
template <class EOT >
eoEvalFuncCounter< EOT >& do_make_eval_mo(eoParser& _parser, eoState& _state,eoPop< EOT > & _pop, daex::Init< EOT > & _init)
{
    unsigned int b_max_fixed = _parser.valueOf<unsigned int>("bmax-fixed");
    double b_max_last_weight = _parser.valueOf<double>("bmax-last-weight");
    //double b_max_quantile = _parser.valueOf<double>("bmax-quantile");
   
	double astar_weight = _parser.valueOf<double>("astar-weight");
	bool rand_seed = _parser.valueOf<bool>("rand_yahsp_seed");

  	bool cost_max = _parser.valueOf<bool>("cost-max");
  	StrategyType stratType = (StrategyType)_parser.valueOf<unsigned>("strat-eval");
  	unsigned nbEval = _parser.valueOf<unsigned>("nb-eval");
  	
	unsigned int b_max_init = _parser.valueOf<unsigned int>("bmax-init"); 
    unsigned int fitness_weight = _parser.valueOf<unsigned int>("fitness-weight");
    unsigned int fitness_penalty = _parser.valueOf<unsigned int>("fitness-penalty");
    
    std::vector<double> rates;

    rates.resize(NB_YAHSP_STRAT);
    rates[makespan_max] = _parser.valueOf<double>("makespan_max_weigth");
    rates[makespan_add] = _parser.valueOf<double>("makespan_add_weigth");
    rates[cost] = _parser.valueOf<double>("cost_weigth");
    rates[length] = _parser.valueOf<double>("length_weigth");
    
    StrategyInit<EOT> stratInit(stratType, rates);
    
    // Check parameters
    if( b_max_last_weight <= 0 ) 
    {
        std::cout << "bmax-last-weight must be strictly positive (=" << b_max_last_weight << ") type --help for usage." << std::endl;
        exit(1);
    }
    
    // End check paramters

    PlanningEvalInit< EOT > *eval_yahsp_init = new PlanningEvalInit< EOT >(
        stratInit(),
        _pop.size(), 
        _init.l_max(), 
        b_max_init, 
        b_max_last_weight, 
        fitness_weight, 
        fitness_penalty,
        cost_max,
        nbEval,
        astar_weight,
	    rand_seed      
    );

	_state.storeFunctor(eval_yahsp_init);
 
    ///Strategie incrementale 
    double b_max_increase_coef = _parser.valueOf<double>("bmax-increase-coef");
    double b_max_ratio = _parser.valueOf<double>("bmax-ratio");
    unsigned int b_max_in, b_max_last, goodguys=0, popsize = _pop.size(); 
  
    PlanningEval< EOT >  *eval_yahsp = NULL ;
    _state.storeFunctor(eval_yahsp);
  
    if( b_max_fixed == 0 ) 
    {
        std::cout<< "Apply an incremental computation strategy to fix bmax_last:" << std::endl;
    
        b_max_in = 1;

        while((((double)goodguys/(double)popsize) <= b_max_ratio) && (b_max_in < b_max_init) ) 
        {
	   
	        goodguys=0;
	        b_max_last = static_cast<unsigned int>(std::floor(b_max_in * b_max_last_weight));
	        eval_yahsp = new PlanningEval< EOT >(
	            stratInit(),
	            _init.l_max(), 
	            b_max_in, 
	            b_max_last, 
	            fitness_weight, 
	            fitness_penalty,
	            cost_max,
	            nbEval,
	            astar_weight,
	            rand_seed
	        );
// in non multi-threaded version, use the plan dumper
//#ifndef SINGLE_EVAL_ITER_DUMP

            apply(*eval_yahsp, _pop);  

            for (size_t i = 0; i < popsize; ++i) 
            {
                // unfeasible individuals are invalidated in order to be re-evaluated 
                // with a larger bmax at the next iteration but we keep the good guys.
                if (_pop[i].state() == Feasible) 
                    goodguys++;
                else 
                    _pop[i].invalidate();
            }
 
            b_max_fixed = b_max_in;
            b_max_in = (unsigned int)ceil(b_max_in*b_max_increase_coef);
        } // while
       //delete temp_yahsp; 
       std::cout << "b_max_fixed : " <<  b_max_fixed << std::endl;
       std::cout << "b_max_in : " <<  b_max_in << std::endl;
    }
    //if we want a fixed b_max for the whole search
    else  
    { // if b_max_fixed != 0 
        std::cout<< "Apply the standard strategy to fix bmax_last:" << std::endl;
        b_max_in = b_max_fixed;
		assert( b_max_in > 0 );
		// The b_max for the very last search towards the end goal
		// is the estimated b_max * a given weight (3 by default)
		b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );
		assert( b_max_last > 0 );
		// eval that uses the correct b_max
		eval_yahsp = new PlanningEval< EOT >(
		    stratInit(),
		    _init.l_max(), 
		    b_max_in, 
		    b_max_last, 
		    fitness_weight, 
		    fitness_penalty,
		    cost_max,
		    nbEval,
		    astar_weight, 
		    rand_seed
        );
		apply(*eval_yahsp, _pop);
	 }

    eoEvalFuncCounter< EOT > *eval_counter = new eoEvalFuncCounter< EOT >( *eval_yahsp, "Eval.\t" );
    _state.storeFunctor(eval_counter);
    std::cout << "End of first evaluation" << std::endl;
    return *eval_counter;	
}

/*
template <class EOT >
eoEvalFuncCounter< EOT >& do_make_eval_aggregation(eoParser& _parser, eoState& _state,eoPop< EOT > & _pop,   daex::Init< EOT > & _init)
{

  	std::string objective =  _parser.valueOf<std::string>("objective");
	unsigned int b_max_init = _parser.valueOf<unsigned int>("bmax-init");
    unsigned int fitness_weight = _parser.valueOf<unsigned int>("fitness-weight");
    unsigned int fitness_penalty = _parser.valueOf<unsigned int>("fitness-penalty");
        
    PlanningAggregaEvalInit *eval_yahsp_init = new PlanningAggregaEvalInit(
        _pop.size(), 
        _init.l_max(), 
        b_max_init, 
        b_max_init, 
        fitness_weight, 
        fitness_penalty,objective
    );

	_state.storeFunctor(eval_yahsp_init);
 
	unsigned int b_max_fixed = _parser.valueOf<unsigned int>("bmax-fixed");
    double b_max_last_weight = _parser.valueOf<double>("bmax-last-weight");
    
   	if( b_max_last_weight <= 0 ) {
        std::cout << "bmax-last-weight must be strictly positive (=" << b_max_last_weight << ") type --help for usage." << std::endl;
        exit(1);
    }
    
    double b_max_quantile = _parser.valueOf<double>("bmax-quantile");
    
    if( b_max_quantile < 0 || b_max_quantile > 1 ) {
        std::cout << "bmax-quantile must be a double in [0,1] (=" << b_max_quantile << ") type --help for usage." << std::endl;
        exit(1);
    }
  
    double lenght_weigth = _parser.valueOf<double>("lenght_weigth");
    double cost_weigth = _parser.valueOf<double>("cost_weigth"); 	
    double makespan_max_weigth = _parser.valueOf<double>("makespan_max_weigth");
 	double makespan_add_weigth = _parser.valueOf<double>("makespan_add_weigth");
    double astar_weight = _parser.valueOf<double>("astar_weigth");
	bool rand_seed = _parser.valueOf<bool>("rand_yahsp_seed");
    double alpha = _parser.valueOf<double>("alpha");
 	double minObj1 = _parser.valueOf<double>("minObj1");
	double maxObj1= _parser.valueOf<double>("maxObj1");
	double minAddObj2 = _parser.valueOf<double>("minAddObj2");
	double maxAddObj2 = _parser.valueOf<double>("maxAddObj2");
	double minMaxObj2 = _parser.valueOf<double>("minMaxObj2");
	double maxMaxObj2 = _parser.valueOf<double>("minMaxObj2");
    bool normalize = _parser.valueOf<bool>("normalize");
    std::string strategy_level = _parser.valueOf<std::string>("strategy");
	double proba_strateg_indiv = _parser.valueOf<double>("proba_indiv");
	double proba_strateg_goal= _parser.valueOf<double>("proba_goal");
    double b_max_increase_coef = _parser.valueOf<double>("bmax-increase-coef");
    double b_max_ratio = _parser.valueOf<double>("bmax-ratio");
    
    unsigned int b_max_in, b_max_last, goodguys=0, popsize = _pop.size(); 
  
    PlanningAggregaEval  *eval_yahsp = NULL ;
  
    _state.storeFunctor(eval_yahsp);
  
   if(b_max_fixed == 0) 
   {
        std::cout<< "Apply an incremental computation strategy to fix bmax_last:" << std::endl;
    
        b_max_in = 1;

        while( (((double)goodguys/(double)popsize) <= b_max_ratio) && (b_max_in < b_max_init) ) 
        {
	        goodguys=0;
            
	        b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );
	        eval_yahsp = new PlanningAggregaEval( 
	            _init.l_max(), 
	            b_max_in, 
	            b_max_last, 
	            fitness_weight, 		
		        fitness_penalty,
		        objective,
		        lenght_weigth,
		        cost_weigth, 
		        makespan_max_weigth,
		        makespan_add_weigth,
		        astar_weight, 
                rand_seed, 
                alpha,
                minObj1,
                maxObj1,
                minAddObj2,
                maxAddObj2,
                minMaxObj2,
                maxMaxObj2,
                normalize, 		
	  	        strategy_level,
	  	        proba_strateg_indiv,
	  	        proba_strateg_goal
	  	    ); 

// in non multi-threaded version, use the plan dumper
//#ifndef SINGLE_EVAL_ITER_DUMP
            
            apply(*eval_yahsp, _pop);  

            for (size_t i = 0; i < popsize; ++i) 
            {
                // unfeasible individuals are invalidated in order to be re-evaluated 
                // with a larger bmax at the next iteration but we keep the good guys.
                if (_pop[i].is_feasible()) goodguys++;
                else _pop[i].invalidate();
            }
 
            b_max_fixed = b_max_in;
            b_max_in = (unsigned int)ceil(b_max_in*b_max_increase_coef);
        } // while
       //delete temp_yahsp; 
    }
    else  
    { // if b_max_fixed != 0 
        std::cout<< "Apply the standard strategy to fix bmax_last:" << std::endl;
		
        b_max_in = b_max_fixed;
		assert( b_max_in > 0 );
		// The b_max for the very last search towards the end goal
		// is the estimated b_max * a given weight (3 by default)
		b_max_last = static_cast<unsigned int>( std::floor( b_max_in * b_max_last_weight ) );
		assert( b_max_last > 0 );
		// eval that uses the correct b_max
		eval_yahsp = new PlanningAggregaEval ( 
		    _init.l_max(), 
		    b_max_in, 
		    b_max_last, 
		    fitness_weight, 		
		    fitness_penalty,
		    objective,
		    lenght_weigth,
		    cost_weigth, 
		    makespan_max_weigth,
		    makespan_add_weigth,
		    astar_weight, 
		    rand_seed, 
		    alpha, 
		    minObj1, 
		    maxObj1, 
		    minAddObj2,
		    maxAddObj2,
		    minMaxObj2,
		    maxMaxObj2,
		    normalize, 		
            strategy_level,
            proba_strateg_indiv,
            proba_strateg_goal
        ); 
		apply(*eval_yahsp, _pop);
    }
    eoEvalFuncCounter<Planning> *eval_counter = new eoEvalFuncCounter<Planning>( *eval_yahsp, "Eval.\t" );
    	
    _state.storeFunctor(eval_counter);
    	
    return *eval_counter;  	
}
*/
 
} // namespace daex

#endif  /* MAKE_EVAL_DAE_H_*/
