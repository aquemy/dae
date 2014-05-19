
#ifndef PLANNINGEVAL_H_
#define PLANNINGEVAL_H_

#include <iostream>
#include <utility>
#include <moeo>
#include <typeinfo>
#include <evaluation/yahsp.h>
#include "planning.h"

namespace daex {

/**
 * Evaluation of the objective vector a (multi-objective) Planning object
 */
template <class EOT >
class PlanningEval : public daeYahspEval< EOT >
{
public:

    PlanningEval (
        Strategy<EOT> _strat,
        unsigned int l_max_ = 20,
		unsigned int b_max_in = 10, 
		unsigned int b_max_last = 30,
		double fitness_weight = 10, 
		double fitness_penalty = 1e6,
		std::string _objective="Add",
		unsigned int astar_weigth=3,
		bool _rand_seed = false,
		std::string _level = "Pop"
    ):
        daeYahspEval< EOT >(
            l_max_,
            b_max_in, 
            b_max_last, 
            fitness_weight, 
            fitness_penalty,
            _level
       ),    
       strat(_strat),
       rand_seed(_rand_seed),
       level(_level)
    {
        if (_objective.compare("Add")==0)
       		secondObjective = &PlanningEval::additive_cost;
      	else
     		secondObjective = &PlanningEval::max_cost;
        
	    yahsp_set_weight(astar_weigth);
    }
    
    virtual ~PlanningEval() {};

    virtual void setFitness(EOT & decompo)
    {
	    PlanningObjectiveVector objVector;

     	if (decompo.state() == Feasible)
     	{
     	    objVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
     		objVector[1] = (this->*secondObjective)(decompo);	
      	}
      	else
      	{
      	    if(decompo.state() == UnfeasibleIntermediate)
      	        objVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_intermediate(decompo);
      	    else if(decompo.state() == UnfeasibleFinal)
      	        objVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_final(decompo);
      	    else if(decompo.state() == UnfeasibleTooLong)
      	        objVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_too_long();
      	    //else
      	    //    objVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible(decompo);
      	        
    		objVector[1] = objVector[0];
        }
        
    	decompo.objectiveVector(objVector);
    	decompo.fitness(objVector[0]);
    	
    }

   /**
    * computation of the cost
    * @param _decompo the genotype to evaluate
    */
    double additive_cost(EOT & _decompo)
    {
        return _decompo.plan().cost_add();
    }

    double max_cost(EOT & _decompo)
    {
        return _decompo.plan().cost_max();
    }
   
    void pre_call(EOT & decompo)
    {
    
        Objective strategy;
        
        if(level == "Pop")
            strategy = strat(decompo);
        else if(level == "Indi")
            strategy = decompo.objective();
       
        if (strategy == makespan_max) {
            yahsp_set_optimize_makespan_max(); } 
        else if (strategy == cost)  {
            yahsp_set_optimize_cost();  }
	    else if (strategy == makespan_add)  {
	        yahsp_set_optimize_makespan_add();  }
	    else {
	        yahsp_set_optimize_length();}
         
        if(rand_seed)
            yahsp_set_seed(rng.rand());
        
        
    }
    
    virtual void operator()(EOT& decompo) 
    {
        if (decompo.invalid())
        {
            std::vector<PlanningObjectiveVector> objvectors(NB_YAHSP_STRAT);
            std::vector<PlanningState> stats(NB_YAHSP_STRAT);
            
            PlanningObjectiveVector bestObjVector;
            PlanningState bestState;
            
            /*if(decompo.state() == Feasible)
                std::cerr <<"# Before" << std::endl << decompo.prevObjVector[0] << " " << decompo.prevObjVector[1] << std::endl << std::endl << std::endl ;   */
            
            //pre_call(decompo);
            // Pour chaque objectif
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                Objective strategy = (Objective)i;
                // Choix de la strategy
                if (strategy == makespan_max) {
                    yahsp_set_optimize_makespan_max(); } 
                else if (strategy == cost)  {
                    yahsp_set_optimize_cost();  }
	            else if (strategy == makespan_add)  {
	                yahsp_set_optimize_makespan_add();  }
	            else {
	                yahsp_set_optimize_length();}
                 
                if(rand_seed)
                    yahsp_set_seed(rng.rand());
               
                // On résout selon l'objectif
                
                daeYahspEval<EOT>::call(decompo);
                
                if(i == 0)
                {
                    bestState = decompo.state();
                    if (bestState == Feasible)
             	    {
             	        bestObjVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
             		    bestObjVector[1] = (this->*secondObjective)(decompo);	
              	    }
                  	else
                  	{
                  	    if(decompo.state() == UnfeasibleIntermediate)
                  	        bestObjVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_intermediate(decompo);
                  	    else if(decompo.state() == UnfeasibleFinal)
                  	        bestObjVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_final(decompo);
                  	    else if(decompo.state() == UnfeasibleTooLong)
                  	        bestObjVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible_too_long();
                  	    //else
                  	    //    objVector[0] = daeCptYahspEval<EOT>::fitness_unfeasible(decompo);
                  	        
                		bestObjVector[1] = bestObjVector[0];
                    }
                    /*std::cerr << "#" << i << std::endl << daeYahspEval< EOT >::fitness_feasible(decompo) << " " << (this->*secondObjective)(decompo) << std::endl; */
                }
                else
                {
                    if(bestState != Feasible && decompo.state() == Feasible)
                    {
                        //std::cerr << "NF -  F : " << bestObjVector[0] << " -> " << daeYahspEval< EOT >::fitness_feasible(decompo) << " " << (this->*secondObjective)(decompo) << std::endl;
                        bestState = Feasible;
                        bestObjVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
             		    bestObjVector[1] = (this->*secondObjective)(decompo);
                    }
                    else if(bestState != Feasible && decompo.state() != Feasible)
                    {
                        
                        double fit;
                        if(decompo.state() == UnfeasibleIntermediate)
                  	        fit = daeCptYahspEval<EOT>::fitness_unfeasible_intermediate(decompo);
                  	    else if(decompo.state() == UnfeasibleFinal)
                  	        fit = daeCptYahspEval<EOT>::fitness_unfeasible_final(decompo);
                  	    else if(decompo.state() == UnfeasibleTooLong)
                  	        fit = daeCptYahspEval<EOT>::fitness_unfeasible_too_long();
                  	    //std::cerr << "NF - NF : " << bestObjVector[0] << " " << fit << std::endl;    
                        bestObjVector[0] = std::min(bestObjVector[0], fit);
                        bestObjVector[1] = bestObjVector[0];
                    }
                    else if(bestState == Feasible && decompo.state() == Feasible)
                    {
                    
                    
                        double f1,f2;
                        /*// euclidian distance
                        f1 = std::sqrt(bestObjVector[0]*bestObjVector[0] + bestObjVector[1]*bestObjVector[1]);
                        f2 = std::sqrt(daeYahspEval< EOT >::fitness_feasible(decompo)*daeYahspEval< EOT >::fitness_feasible(decompo) + (this->*secondObjective)(decompo)*(this->*secondObjective)(decompo));*/
                        // hypersurface
                        f1 = (decompo.prevObjVector[0] - bestObjVector[0]) + (decompo.prevObjVector[1] - bestObjVector[1]);
                        f2 = (decompo.prevObjVector[0] - daeYahspEval< EOT >::fitness_feasible(decompo)) + (decompo.prevObjVector[1] - (this->*secondObjective)(decompo));
                        
                        /*std::cerr << "#" << i << std::endl << daeYahspEval< EOT >::fitness_feasible(decompo) << " " << (this->*secondObjective)(decompo) << " " << f1 << " " << f2 << std::endl; */
                        if(f2 > f1)
                        {
                            bestObjVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
                            bestObjVector[1] = (this->*secondObjective)(decompo);
                        }
                    }
                }
                 
            }
            
            decompo.objectiveVector(bestObjVector);
    	    decompo.fitness(bestObjVector[0]);
    	    
    	    decompo.prevObjVector = bestObjVector;
    	    /*if(decompo.state() == Feasible)
                std::cerr << std::endl << std::endl << "# After" << std::endl << decompo.prevObjVector[0] << " " << decompo.prevObjVector[1] << std::endl; */
            post_call(decompo);
            //std::cerr << std::endl << std::endl;
        }
    }
    
    virtual void step_recorder(){};
    
    virtual void step_recorder_fail(){};
  
    
    void post_call(EOT& decompo)
    {
        decompo.plan().search_steps(decompo.get_number_evaluated_nodes());  
    } 
                                
    // Pointer towards the 2nd objective to optimize (tota cost / max cost)
    double (PlanningEval::*secondObjective)(EOT &);  
     
    // Weight vectors of the different strategies (lenght, cost,  makespan_max, makespan_add,)
    Strategy<EOT> strat;
     
    bool rand_seed; // flag for the random initialization of yashp at each call
    
protected :
    std::string level;  
};

//! Classe à utiliser lors de la première itération, pour estimer b_max
template <class EOT >
class PlanningEvalInit : public PlanningEval< EOT >
{
public:

    PlanningEvalInit(
        Strategy<EOT> _strat,
        unsigned int pop_size, 
        unsigned int l_max, 
        unsigned int b_max_in = 10000, 
        unsigned int b_max_last = 30000, 
        double fitness_weight = 10,
	    double fitness_penalty = 1e6,
	    std::string _objective="Add",
	    unsigned int astar_weigth=3,
	    bool _rand_seed = false,
	    std::string _level = "Pop"):
	    PlanningEval<EOT >(
	        _strat,
	        l_max,
	        b_max_in, 
	        b_max_last, 
	        fitness_weight, 
	        fitness_penalty,
	        _objective,
	        astar_weigth,
	        _rand_seed,
	        _level
	        ) 
    {
       node_numbers.reserve( pop_size * l_max );
    }

    void call(EOT& decompo ){
#ifndef NDEBUG
    eo::log << eo::logging << std::endl << "init decompo nodes nb: ";
    eo::log.flush();
    int prev = std::accumulate( node_numbers.begin(), node_numbers.end(), 0 );
#endif
    PlanningEval< EOT >::call( decompo );
#ifndef NDEBUG
    int next = std::accumulate( node_numbers.begin(), node_numbers.end(), 0 );
    eo::log << eo::logging << "     (" << next - prev << ")";
#endif
};

    //! Récupère le nombre de noeuds utilisés par une résolution avec yahsp
     void step_recorder(){
     
     node_numbers.push_back( static_cast<int>( solution_plan->backtracks ) ); // TODO SolutionPlan->backtracks est codé comme un double dans plan.h
 
 #ifndef NDEBUG
     eo::log << eo::logging << " " << node_numbers.back();
     eo::log.flush();
 #endif
};
    void step_recorder_fail(){
      node_numbers.push_back(stats.evaluated_nodes);
#ifndef NDEBUG
    eo::log << eo::logging << " " << node_numbers.back();
    eo::log.flush();
#endif
};

    //! Le b_max est calculé comme la médiane du nombre total de noeuds parcourus sur l'ensemble de tous les appels à yahsp 
    //lors d'une première phase d'initialisation
    unsigned int estimate_b_max( double quantile = 0.5 ){
    assert( node_numbers.size() > 0 );

    //unsigned int nth = node_numbers.size() / 2; // division euclidienne, indicage à 0 => prend l'élément supérieur
    unsigned int nth = static_cast<unsigned int>( ceil( static_cast<double>( node_numbers.size() ) * quantile ) );

#ifndef NDEBUG
    if( nth == 0 || nth == node_numbers.size()-1 ) {
        eo::log << eo::warnings << "WARNING: while estimating the b_max, the quantile at " << quantile << " returns the " << nth << "th element (size=" << node_numbers.size() << ")" << std::endl;
    }
#endif

    // JACK use a simple computation of the median (rounding in case of an even size)
    
    // code version:
    //return node_numbers[ nth ];

    // suggested version: use a linear interpolation in case of even size
    
    if( node_numbers.size() % 2 != 0 ) { // impair

        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth,  node_numbers.end() );
        // l'element central est la médiane
        return node_numbers[nth];

    } else { // pair

        unsigned int m1, m2;

        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth,  node_numbers.end() );
        m1 = node_numbers[nth];
        std::nth_element( node_numbers.begin(), node_numbers.begin() + nth - 1,  node_numbers.end() );
        m2 = node_numbers[nth-1];
        
        // mean of center elements
        // with rounding, because the b_max should be an uint
        return static_cast<unsigned int>( ceil( static_cast<double>( m1 + m2 ) / 2.0 ) );
    } 
}
;

protected:
    
    //! Distribution des nombres de noeuds utilisés dans les résolutions
    std::vector<unsigned int> node_numbers;
};

} // namespace daex

#endif /*PLANNINGEVAL_H_*/
