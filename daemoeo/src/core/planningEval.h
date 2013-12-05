
#ifndef PLANNINGEVAL_H_
#define PLANNINGEVAL_H_

#include <iostream>
#include <utility>
#include <moeo>
#include <evaluation/yahsp.h>
#include "planning.h"

/**
 * Evaluation of the objective vector a (multi-objective) Planning object
 */
class PlanningEval : public daeCptYahspEval  <Planning>
  {
  public:

  PlanningEval (unsigned int l_max_ = 20,
		unsigned int b_max_in = 10, 
		unsigned int b_max_last = 30,
		double fitness_weight = 10, 
		double fitness_penalty = 1e6,
		std::string _objective="Add",
		double lenght_weigth=1.0, 
		double cost_weigth=1.0,
		double makespan_max_weigth=1.0, 
		double makespan_add_weigth=1.0,
		unsigned int astar_weigth=3,
		bool _rand_seed = false
 	      );
  /**
     * computation of the multi-objective evaluation of a Planning object
     * @param _decompo the Planning object to evaluate
     */
  void operator()(Planning & _decompo);
  

  virtual ~PlanningEval();

   
  virtual void call (Planning & _decompo);
   
   /**
   * computation of the makespan
   * @param _decompo the genotype to evaluate
   */
   double makespan(Planning & _decompo);  

   /**
    * computation of the cost
    * @param _decompo the genotype to evaluate
    */
   double additive_cost(Planning & _decompo); 
   
   double max_cost(Planning & _decompo); 
   
   void adaptive_search_strategy();
    
   virtual void step_recorder(){};
    
   virtual void step_recorder_fail(){};
   
   void pre_call( Planning& decompo ){};   
    
    void post_call( Planning & decompo);  
        
    

  protected:

    unsigned int solve_next( Planning & decompo, Fluent** next_state, unsigned int next_state_nb, long max_evaluated_nodes );
    
     void compress( Planning & decompo );
                                

   // ! Free all necessary pointers to global variables
    //that have been used during call
      void free_yahsp_structures();
      
    // Pointer towards the 2nd objective to optimize (tota cost / max cost)
     double  (PlanningEval::*secondObjective)(Planning &);  
     
     // Weight vectors of the different strategies (lenght, cost,  makespan_max, makespan_add,)
     
     std::vector<double> rates;
     
     bool rand_seed; // flag for the random initialization of yashp at each call
  
 };
//! Classe à utiliser lors de la première itération, pour estimer b_max
 
class PlanningEvalInit : public PlanningEval
{
public:

    PlanningEvalInit( 
            unsigned int pop_size, 
            unsigned int l_max, 
            unsigned int b_max_in = 10000, 
            unsigned int b_max_last = 30000, 
            double fitness_weight = 10,
	    double fitness_penalty = 1e6,
	    std::string _objective="Add",
	    double lenght_weigth=1.0, 
	    double cost_weigth=1.0,
	    double makespan_max_weigth=1.0, 
	    double makespan_add_weigth=1.0,
	    unsigned int astar_weigth=3,
	    bool _rand_seed = false):
	    PlanningEval( l_max, b_max_in, b_max_last, fitness_weight, fitness_penalty,_objective,lenght_weigth,
	    cost_weigth, makespan_max_weigth, makespan_add_weigth, astar_weigth,_rand_seed) 
    {
       node_numbers.reserve( pop_size * l_max );
    }

    void call(Planning & decompo ){
#ifndef NDEBUG
    eo::log << eo::logging << std::endl << "init decompo nodes nb: ";
    eo::log.flush();
    int prev = std::accumulate( node_numbers.begin(), node_numbers.end(), 0 );
#endif

    PlanningEval::call( decompo );

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


#endif /*PLANNINGEVAL_H_*/
