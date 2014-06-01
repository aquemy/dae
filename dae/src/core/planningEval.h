
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
        Strategy<EOT>* _strategy,
        StrategyLevel _stratLevel,
        unsigned int l_max_ = 20,
		unsigned int b_max_in = 10, 
		unsigned int b_max_last = 30,
		double fitness_weight = 10, 
		double fitness_penalty = 1e6,
		bool _cost_max = false,
		unsigned _nbEvaluations = 1,
		unsigned int astar_weigth=3,
		bool _rand_seed = true
    ):
        daeYahspEval< EOT >(
            _stratLevel,
            l_max_,
            b_max_in, 
            b_max_last, 
            fitness_weight, 
            fitness_penalty,
            _rand_seed
       ),
       nbEvaluations(_nbEvaluations),
       strategy(_strategy),
       stratLevel(_stratLevel)
    {
        if (!_cost_max)
       		secondObjective = &PlanningEval::additive_cost;
      	else
     		secondObjective = &PlanningEval::max_cost;
       
	    yahsp_set_weight(astar_weigth);

    }
    
    virtual ~PlanningEval() 
    { 
        if(strategy != NULL)
            delete strategy;
    };

    virtual void operator()(EOT& decompo) 
    {
        if (decompo.invalid())
        {
            
            std::vector<PlanningObjectiveVector> objvectors(NB_YAHSP_STRAT);
            std::vector<PlanningState> stats(NB_YAHSP_STRAT);
            
            PlanningObjectiveVector bestObjVector;
            PlanningState bestState;
            daex::Plan bestPlan;
                
            #ifndef NDEBUG
            PlanningObjectiveVector ref = decompo.prevObjVector;
            std::vector<PlanningObjectiveVector> vectors(nbEvaluations);
            #endif 
            
            // Pour chaque objectif
            Objective objective;
            for(unsigned i = 0; i < nbEvaluations; i++)
            {
                
                if(stratLevel == Population)
                     objective = (*strategy)(decompo);
                else if(stratLevel == Individual)
                     objective = decompo.strategy();
                     
                yahsp_set_optimize(objective);
                
                daeYahspEval<EOT>::pre_call(decompo);
               
                // On résout selon l'objectif
                daeYahspEval<EOT>::call(decompo);
                #ifndef NDEBUG
                if(stratLevel != Gene)
                {
                    if (objective == makespan_max)
                        eo::log << eo::xdebug << "makespan_max : ";
                    else if (objective == cost)
                        eo::log << eo::xdebug << "cost : ";
	                else if (objective == makespan_add) 
	                    eo::log << eo::xdebug << "makespan_add : ";
	                else 
	                    eo::log << eo::xdebug << "length : ";
	                
                }
                eo::log << eo::xdebug << daeYahspEval< EOT >::fitness_feasible(decompo) << " " << (this->*secondObjective)(decompo) << std::endl;  
	                    
                eo::log.flush();
                
                vectors[i][0] = daeYahspEval< EOT >::fitness_feasible(decompo);
                vectors[i][1] = (this->*secondObjective)(decompo);
                #endif 
                
                if(i == 0)
                {
                    bestState = decompo.state();
                    bestPlan = decompo.plan();	
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
                }
                else
                {
                    if(bestState != Feasible && decompo.state() == Feasible)
                    {
                        bestState = Feasible;
                        bestObjVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
             		    bestObjVector[1] = (this->*secondObjective)(decompo);
             		    bestPlan = decompo.plan();	
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

                        if(bestObjVector[0] > fit)
                        {
                            bestObjVector[0] = fit;
                            bestObjVector[1] = bestObjVector[0];
                            bestPlan = decompo.plan();	
                        }
                    }
                    else if(bestState == Feasible && decompo.state() == Feasible)
                    {
                        // TODO : Tester si la condition suivante plus élitiste :
                        // Soit x le vecteur objectif précédent.
                        // On écarte les vecteurs objectifs qui sont dominés par celui-ci
                        // En dernier lieu, on applique la condition suivante
                        double f1 = (decompo.prevObjVector[0] - bestObjVector[0]) 
                            + (decompo.prevObjVector[1] - bestObjVector[1]);
                        double f2 = (decompo.prevObjVector[0] - daeYahspEval< EOT >::fitness_feasible(decompo)) 
                            + (decompo.prevObjVector[1] - (this->*secondObjective)(decompo));
                        
                        if(f2 > f1)
                        {
                            bestObjVector[0] = daeYahspEval< EOT >::fitness_feasible(decompo);
                            bestObjVector[1] = (this->*secondObjective)(decompo);
                            bestPlan = decompo.plan();
                        }
                    }
                }
                
            }
            #ifndef NDEBUG
	        eo::log << eo::xdebug << "selected : " << bestObjVector[0] << " " << bestObjVector[1] << std::endl;
            eo::log.flush();
            #endif 
            
            /*#ifndef NDEBUG
            unsigned lx = 0;
            unsigned ly = 0;
            unsigned mx = 0;
            unsigned my = 0;
            for(unsigned i = 0; i < k; i++)
            {
                //std::cout << vectors[i][0] << " " << vectors[i][1] << std::endl;
                if(vectors[i][0] < vectors[lx][0])
                    lx = i;
                if(vectors[i][0] > vectors[mx][0])
                    mx = i;
                if(vectors[i][1] < vectors[ly][1])
                    ly = i;
                if(vectors[i][1] > vectors[my][1])
                    my = i;    
            }
            //std::cout << "Max / Min : " << " " << lx << " " << mx << " " << ly << " " << my << std::endl;
            double r, cx, cy;
            if(vectors[mx][0]-vectors[lx][0] > vectors[my][1]-vectors[ly][1])
            {
                r = (vectors[mx][0]-vectors[lx][0]) / 2;
                cx = (vectors[mx][0]+vectors[lx][0]) / 2;
                cy = (vectors[mx][1]+vectors[lx][1]) / 2;
            }
            else
            {
                r = (vectors[my][1]-vectors[ly][1]) / 2;
                cx = (vectors[ly][0]+vectors[my][0]) / 2;
                cy = (vectors[ly][1]+vectors[my][1]) / 2;
            }    
            // Circles
            std::cerr << cx << " " << cy << " " << r << std::endl;
            
            // Points + ref + best
            for(unsigned i = 0; i < k; i++)
                std::cout << i << " " << vectors[i][0] << " " << vectors[i][1] << " " 
                          << ref[0] << " " << ref[1] << " " 
                          << bestObjVector[0] << " " << bestObjVector[1] << std::endl;
            std::cout << std::endl << std::endl;
            #endif */
            
            decompo.objectiveVector(bestObjVector);
    	    decompo.fitness(bestObjVector[0]);
    	    decompo.plan_global(bestPlan);
    	    
    	    decompo.prevObjVector = bestObjVector;
    	    
            daeYahspEval<EOT>::post_call(decompo); 
            
        }
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
                                
    // Pointer towards the 2nd objective to optimize (tota cost / max cost)
    double (PlanningEval::*secondObjective)(EOT &);
     
    unsigned nbEvaluations;
    Strategy<EOT>* strategy;
    StrategyLevel stratLevel;
};

//! Classe à utiliser lors de la première itération, pour estimer b_max
template <class EOT >
class PlanningEvalInit : public PlanningEval< EOT >
{
public:

    PlanningEvalInit(
        Strategy<EOT>* _strategy,
        StrategyLevel _stratLevel,
        unsigned int pop_size, 
        unsigned int l_max, 
        unsigned int b_max_in = 10000, 
        unsigned int b_max_last = 30000, 
        double fitness_weight = 10,
	    double fitness_penalty = 1e6,
	    bool _cost_max = false,
	    unsigned _nbEvaluations = 1,
	    unsigned int astar_weigth=3,
	    bool _rand_seed = true):
	    PlanningEval<EOT >(
	        _strategy,
	        _stratLevel,
	        l_max,
	        b_max_in, 
	        b_max_last, 
	        fitness_weight, 
	        fitness_penalty,
	        _cost_max,
	        _nbEvaluations,
	        astar_weigth,
	        _rand_seed
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
    PlanningEval< EOT >::operator()(decompo);
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
