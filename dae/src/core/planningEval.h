
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
        moeoUnboundedArchive<Planning<MOEO<PlanningObjectiveVector, double, double> > >& _arch,
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
       stratLevel(_stratLevel),
       globArch(_arch)
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
    
    PlanningObjectiveVector setObjectiveVector(EOT& decompo)
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
    
        return objVector;
    }

    virtual void operator()(EOT& decompo) 
    {
        if (decompo.invalid())
        {
            // TEST
            moeoUnboundedArchive<Planning<MOEO<PlanningObjectiveVector, double, double> > > arch;
            EOT copyDecompo = decompo;
            // END TEST
            
            std::vector<PlanningObjectiveVector> objvectors(NB_YAHSP_STRAT);
            std::vector<PlanningState> stats(NB_YAHSP_STRAT);
            
            PlanningObjectiveVector bestObjVector;
            PlanningObjectiveVector currentObjVector;
            PlanningObjectiveVector ref = decompo.prevObjVector;
            PlanningState bestState;
            daex::Plan bestPlan;
                
            #ifndef NDEBUG
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
                
                currentObjVector = setObjectiveVector(decompo);
                double f1 = deltaPlus(currentObjVector, ref);
                double f2 = deltaPlus(bestObjVector, ref);
                
                if(i == 0 || f1 < f2)
                {
                    bestPlan = decompo.plan();
                    bestObjVector = currentObjVector;
                }
                
                // Update the strategy according to this evaluation
        	    if(stratLevel == Population)
        	    {
                    strategy->update(-f1);
                }
                else if(stratLevel == Individual)
                {
                    decompo.strategyUpdate(-f1);
                }
                else if(stratLevel == Gene)
                {
                    daex::Decomposition::iterator iter = decompo.begin();
                    for(unsigned i = 0; i < decompo.subplans_size(); i++)
                    {
                        PlanningObjectiveVector v;
                        v[0] = decompo.subplan(i).makespan();
                        v[1] = decompo.subplan(i).cost_add(); // TODO : Fix me for cost max
                        
                        double f3 = manhattan(v, ref);
                        if(iter != decompo.end())
                        {
                            iter->strategyUpdate(-f3);
                            iter++;
                        }
                    }
                    
                }
                // TEST
                copyDecompo.objectiveVector(currentObjVector);
                arch(copyDecompo);
                
                // END TEST
            }
            #ifndef NDEBUG
	        eo::log << eo::xdebug << "selected : " << bestObjVector[0] << " " << bestObjVector[1] << std::endl;
            eo::log.flush();
            #endif 
            
            #ifndef NDEBUG
            // Points + ref + best
            PlanningObjectiveVector average;
            average[0] = 0;
            average[1] = 0;
            for(unsigned i = 0; i < nbEvaluations; i++)
            {
                std::cout << vectors[i][0] << " " << vectors[i][1] << " " 
                          << ref[0] << " " << ref[1] << " " 
                          << bestObjVector[0] << " " << bestObjVector[1] << std::endl;
               average[0] += vectors[i][0];
               average[1] += vectors[i][1];
                          
            }    
            average[0] /= nbEvaluations;   
            average[1] /= nbEvaluations;
            bestObjVector = average; 
            std::cout << std::endl << std::endl;
            
            
            // TEST
            // Archive
            std::vector<PlanningObjectiveVector> localArchVector;
            for(unsigned i = 0; i < globArch.size(); i++)
            {
                arch(globArch[i]);
            }
            for(unsigned i = 0; i < arch.size(); i++)
            {
                std::cout << arch[i].objectiveVector(0) << " " << arch[i].objectiveVector(1) << std::endl;
                //globArch(arch[i]);
                localArchVector.push_back(arch[i].objectiveVector());
            }
            std::cout << std::endl << std::endl;
            
            std::vector<PlanningObjectiveVector> globalArchVector;
            for(unsigned i = 0; i < globArch.size(); i++)
            {
                std::cout << globArch[i].objectiveVector(0) << " " << globArch[i].objectiveVector(1) << std::endl;
                globalArchVector.push_back(globArch[i].objectiveVector());
                arch(globArch[i]);
            }
            std::cout << std::endl << std::endl;
            
            if(globalArchVector.size() > 0)
            {
                moeoHyperVolumeDifferenceMetric<PlanningObjectiveVector> diffHypervolume;
                std::cerr << diffHypervolume(globalArchVector,localArchVector) << std::endl;
            }
            
            // Mise à jour de l'archive
            for(unsigned i = 0; i < arch.size(); i++)
            {
                globArch(arch[i]);
            }
            // END TEST
            #endif
            
            // Mutate the strategy according to this evaluation
        	    if(stratLevel == Population)
        	    {
                    strategy->mutation();
                }
                else if(stratLevel == Individual)
                {
                    decompo.strategyMutation();
                }
                else if(stratLevel == Gene)
                {
                    for(daex::Decomposition::iterator igoal = decompo.begin(), iend = decompo.end(); igoal != iend; ++igoal)
                    {
                        
                        igoal->strategyMutation();
                    }
                    
                    
                }
            
            decompo.objectiveVector(bestObjVector);
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
    moeoUnboundedArchive<Planning<MOEO<PlanningObjectiveVector, double, double> > >& globArch;
};

//! Classe à utiliser lors de la première itération, pour estimer b_max
template <class EOT >
class PlanningEvalInit : public PlanningEval< EOT >
{
public:

    PlanningEvalInit(
        Strategy<EOT>* _strategy,
        StrategyLevel _stratLevel,
        moeoUnboundedArchive<Planning<MOEO<PlanningObjectiveVector, double, double> > >& _arch,
        unsigned int pop_size, 
        unsigned int l_max, 
        unsigned int b_max_in = 10000, 
        unsigned int b_max_last = 30000, 
        double fitness_weight = 10,
	    double fitness_penalty = 1e6,
	    bool _cost_max = false,
	    unsigned _nbEvaluations = 1,
	    unsigned int astar_weigth=3,
	    bool _rand_seed = true
	    ):
	    PlanningEval<EOT >(
	        _strategy,
	        _stratLevel,
	        _arch,
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
