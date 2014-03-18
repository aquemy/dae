#include "AggregaEval.h"

std::ostream & operator<<( std::ostream & out, BitArray bitarray )
{
	for( unsigned int i = 1; i < (unsigned int) fluents_nb; ++i ) {
		unsigned long bit = bitarray_get( bitarray, fluents[i] );
		if( bit != 0 ) {
			out << " " << fluent_name(fluents[i]);
		}
	}
	return out;
}

PlanningAggregaEval::PlanningAggregaEval(unsigned int l_max_ ,
		unsigned int b_max_in,
		unsigned int b_max_last,
		double fitness_weight,
		double fitness_penalty,
		std::string  _objective,
		double lenght_weigth,
		double cost_weigth,
		double makespan_max_weigth,
		double makespan_add_weigth,
		unsigned int astar_weigth,
		bool _rand_seed,
		double _alpha,
		double _minObj1,
		double _maxObj1,
		double _minAddObj2,
		double _maxAddObj2,
		double _minMaxObj2,
		double _maxMaxObj2,
		bool _normalize,
		std::string _strategy_level,
		double _proba_strateg_indiv,
		double _proba_strateg_goal):
		daeCptYahspEval <Planning>
(l_max_,b_max_in, b_max_last, fitness_weight, fitness_penalty),
rand_seed(_rand_seed), alpha(_alpha), normalize(_normalize),
strategy_level(_strategy_level), proba_strateg_indiv(_proba_strateg_indiv),
proba_strateg_goal(_proba_strateg_goal){


	if (_objective.compare("Add")==0)
		fitness_aggregation=  &  PlanningAggregaEval::aggreg_additiveCost_makespan;
	else
		fitness_aggregation=  & PlanningAggregaEval::aggreg_maxCost_makespan;



	rates.push_back(lenght_weigth);

	rates.push_back(cost_weigth);

	rates.push_back(makespan_max_weigth);

	rates.push_back(makespan_add_weigth);

	yahsp_set_weight(astar_weigth);	

	obj1_bounds[0]=_minObj1;

	obj1_bounds[1]=_maxObj1;

	obj2_add_bounds[0]=_minAddObj2;

	obj2_add_bounds[1]=_maxAddObj2;

	obj2_max_bounds[0]=_minMaxObj2;

	obj2_max_bounds[1]=_maxMaxObj2;

}


PlanningAggregaEval::~PlanningAggregaEval(){};

void PlanningAggregaEval::operator()(Planning& _decompo)
{
	if (_decompo.invalid())
	{
		weighted_search_strategy(_decompo);
		pre_call(_decompo);
		call(_decompo);
		post_call(_decompo);

	}
}

void PlanningAggregaEval::weighted_search_strategy(Planning & _decompo)
{


	if (strategy_level.compare("pop")==0){

		unsigned what = rng.roulette_wheel(rates);

		if (what == 0) yahsp_set_optimize_length();
		else	if (what ==1) yahsp_set_optimize_cost();
		else if (what ==2) yahsp_set_optimize_makespan_max();
		else yahsp_set_optimize_makespan_add();
	}
	/*else


		if ( strategy_level.compare("indiv") ==0 || (strategy_level.compare("mixte") ==0  && _decompo.indiv_strategy_level) ) {

			if (rng.flip(proba_strateg_indiv))

				_decompo.makespan_weight_indiv = ! _decompo.makespan_weight_indiv ;


			if (_decompo.makespan_weight_indiv )

				yahsp_set_optimize_makespan_add();
			else

				yahsp_set_optimize_cost();



		}*/


	if (rand_seed)
		yahsp_set_seed(rng.rand());


}


double PlanningAggregaEval::additive_cost(  Planning & _decompo)
{
	/// Total cost of the solution

	return _decompo.plan().makespan();
}


double PlanningAggregaEval::max_cost(  Planning & _decompo)
{
	/// Max cost of the solution

	return _decompo.plan().cost_max();
}


double PlanningAggregaEval::aggreg_additiveCost_makespan ( Planning & decompo,  PlanningObjectiveVector& objVector)
{
	double Q;

	objVector[1]=decompo.plan().cost_add() ;

	// Pour travailler sur les valeurs affichables, on va partout ramener à la bonne valeur
	//unsigned int Q = solution_plan->makespan;

	if (normalize)

		Q =  alpha *( (double) (decompo.plan().makespan() -  obj1_bounds[0] )/ (obj1_bounds[1]- obj1_bounds[0]))  + (1-alpha) * ( (double) 		(decompo.plan().cost_add() - obj2_add_bounds[0] )/  (obj2_add_bounds[1] - obj2_add_bounds[0] ));

	else

		Q = (alpha *((double) decompo.plan().makespan())+ (1-alpha) * (double) decompo.plan().cost_add() );

	//assert( Q > 0 );

	return Q ;//+ ( (double)decompo.size() - (double)decompo.get_number_useful_goals() + 1.0 ) / Q + (double)decompo.get_number_evaluated_nodes() / ( (double)_l_max * (double)decompo.b_max() );
}



double PlanningAggregaEval::aggreg_maxCost_makespan ( Planning & decompo,  PlanningObjectiveVector &objVector)
{
	double Q;

	objVector[1]=decompo.plan().cost_max() ;

	// Pour travailler sur les valeurs affichables, on va partout ramener à la bonne valeur
	//unsigned int Q = solution_plan->makespan;


	if (normalize)

		Q =  alpha *( (double) (decompo.plan().makespan() -  obj1_bounds[0] )/ (obj1_bounds[1]- obj1_bounds[0]) )+ (1-alpha) * ( (double) (decompo.plan().cost_max() - obj2_max_bounds[0] )/  (obj2_max_bounds[1] - obj2_max_bounds[0] ));

	else

		Q = (alpha *((double) decompo.plan().makespan()) + (1-alpha) * (double) decompo.plan().cost_max() );

	//assert( Q > 0 );


	return Q ;//+ ( (double)decompo.size() - (double)decompo.get_number_useful_goals() + 1.0 ) / Q + (double)decompo.get_number_evaluated_nodes() / ( (double)_l_max * (double)decompo.b_max() );
}

void PlanningAggregaEval::call (Planning & _decompo){


	aggregation(_decompo);

}


void PlanningAggregaEval::aggregation( Planning &  decompo)
{

	PlanningObjectiveVector objVector;
	double unfeasible_fitness;

#ifndef NDEBUG
	eo::log << eo::xdebug << "decompo.size=" << decompo.size() << std::endl;
#endif
#ifndef NDEBUG
	eo::log << eo::xdebug << "Check goal consistency" << std::endl;
	for( Planning::iterator igoal  = decompo.begin(), goal_end = decompo.end(); igoal != goal_end; ++igoal ) {
		assert_noduplicate( igoal->begin(), igoal->end() );
		assert_nomutex(     igoal->begin(), igoal->end() );
	}
#endif
	if( ! decompo.invalid() ) { // do nothing
#ifndef NDEBUG
		eo::log << eo::debug << "-";
		eo::log.flush();
#endif
	} else { // if decompo.invalid

#ifndef PAPERVERSION
		//   JACK the code does not even try to evaluate decompositions that are too long
		// FIXME what is the effect on variation operators that relies on last_reached?
		if( decompo.size() > _l_max ) {

			//_makespan = fitness_unfeasible_too_long();
			unfeasible_fitness= fitness_unfeasible_too_long();
			decompo.fitness(unfeasible_fitness);
			decompo.setFeasible(false);
			objVector[0]=objVector[1]=unfeasible_fitness;

		} else
#endif
		{
			BitArray previous_state = bitarray_create( fluents_nb );
#ifndef NDEBUG
			eo::log << eo::xdebug << "malloc plans...";
			eo::log.flush();
#endif
			cpt_malloc( plans, decompo.size()+1 ); // +1 for the subplan between the last goal and the final state
			plans_nb = 0;
#ifndef NDEBUG
			eo::log << eo::xdebug << "ok" << std::endl;
			eo::log << eo::xdebug << "yahsp reset...";
			eo::log.flush();
#endif
			yahsp_reset();
#ifndef NDEBUG
			eo::log << eo::xdebug << "ok" << std::endl;
#endif
			decompo.reset_number_evaluated_goals(); // compteur de goals
			decompo.reset_number_useful_goals(); // compteur de goals utiles
			decompo.reset_number_evaluated_nodes(); // compteur des tentatives de recherche

#ifndef NDEBUG
			eo::log << eo::xdebug << "for each goal:" << std::endl;
#endif
			unsigned int code = 0; // return code of cpt_search
			// b_max( b_max_in); // set the generic b_max
			decompo.b_max(  _b_max_in ); // VV : set b_max for the decomposition

			//parcourt les goals de la décomposition
			for( Planning::iterator igoal = decompo.begin(), iend = decompo.end(); igoal != iend; ++igoal ) {
#ifndef NDEBUG
				eo::log << eo::xdebug << "\t\tcopy of states and fluents...";
				eo::log.flush();
#endif
				//  copie des goals daex dans leur equivant YAHSP
				//           nouvelle allocation de tableau de goal
				assert( igoal->size() > 0 );


				/*if (strategy_level.compare("goal") ==0 ||  (strategy_level.compare("mixte") ==0 && ! decompo.indiv_strategy_level)) {

					//daex::Goal & subGoal = * decompo.iter_at(decompo.last_reached_safe()) ;

					if (rng.flip(proba_strateg_goal))

						igoal->makespan_weight  = ! igoal-> makespan_weight ;


					if (igoal-> makespan_weight)

						yahsp_set_optimize_makespan_add();
					else

						yahsp_set_optimize_cost();


				}*/

				Fluent **intermediate_goal_state = (Fluent **) malloc(igoal->size() * sizeof(Fluent *));
				unsigned int i = 0;
				for( daex::Goal::iterator iatom = igoal->begin(); iatom != igoal->end(); ++iatom ) {
					//  le compilateur demande à expliciter le template pour fluents,
					//car le C++ ne prend pas en compte les types de retour dans la signature (beurk).
					intermediate_goal_state[i] =  (*iatom)->fluent();
					i++;
				}
				assert( i ==  igoal->size());
				//  search a plan towards the current goal
				bitarray_copy( previous_state, *get_current_state(), fluents_nb );
				code = solve_next( decompo, intermediate_goal_state, igoal->size(), _b_max_in );
				free(intermediate_goal_state);

				if( code != PLAN_FOUND ) {

					decompo.setFeasible(false);
#ifdef PAPERVERSION
					unfeasible_fitness = fitness_unfeasible(decompo,previous_state);

#else

					unfeasible_fitness = fitness_unfeasible_intermediate(decompo);

#endif 
					decompo.fitness(unfeasible_fitness);

					objVector[0]=objVector[1]=unfeasible_fitness;

					break;
				}
			} // for igoal in decompo
			//        here we have reached the last goal of the decomposition, it remains searching towards the ultimate goal
			if((decompo.size() == 0) || (code == PLAN_FOUND)) {
				//  set the b_max specific to this step
				//  b_max( _b_max_last );
				decompo.b_max( _b_max_last ); // VV : set b_max for the decomposition

				bitarray_copy( previous_state, *get_current_state(), fluents_nb );
				unsigned int code = solve_next( decompo, goal_state, goal_state_nb, _b_max_last );

				if( code == PLAN_FOUND ) {
					compress( decompo );
					/*
                if (solution_plan->makespan < 6)
                    std::cout << decompo.size() << " " << plans_nb << std::endl;
					 */

					decompo.setFeasible(true);
                    //std::cout << fitness_feasible( decompo ) << std::endl;
					objVector[0]=fitness_feasible( decompo );

					decompo.fitness((this->*fitness_aggregation)(decompo,objVector));


#ifndef NDEBUG
					eo::log << eo::debug << "*";
					eo::log.flush();
#endif
				} else {

					decompo.setFeasible(false);
#ifdef PAPERVERSION



					unfeasible_fitness =fitness_unfeasible(decompo, previous_state);

#else

					unfeasible_fitness= fitness_unfeasible_final(decompo);
					//
#endif   
					decompo.fitness(unfeasible_fitness);
					objVector[0]=objVector[1]=unfeasible_fitness;

				} // if PLAN_FOUND for last goal
			} // if PLAN_FOUND
			cpt_free(previous_state);
		} // if size > _l_max
	} // if !decompo.invalid
	free_yahsp_structures();

	decompo.objectiveVector(objVector);
    //std::cout << objVector[0] << " " << objVector[1] << std::endl;

}



void PlanningAggregaEval::post_call( Planning & decompo ) {
	decompo.plan().search_steps( decompo.get_number_evaluated_nodes() );

}


unsigned int PlanningAggregaEval::solve_next( Planning & decompo, Fluent** next_state, unsigned int next_state_nb, long max_evaluated_nodes ) {

#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
	eo::log << eo::xdebug << "\t\tcall the solver...";
	eo::log.flush();
#endif
	unsigned int return_code = cpt_search( init_state, init_state_nb, next_state, next_state_nb, false, false, false, max_evaluated_nodes );
#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
	eo::log << eo::xdebug << "\t\treturn code: " << return_code << " ";
	eo::log.flush();
#endif
	if( return_code == NO_PLAN || return_code == GOALS_MUTEX ) {
		step_recorder_fail();
#ifndef NDEBUG
		eo::log << eo::debug << "x";
		eo::log.flush();
		eo::log << eo::xdebug << std::endl;
#endif
	} else if( return_code == PLAN_FOUND ) { assert( solution_plan != NULL );

	if( solution_plan->steps_nb > 0 )  {
		decompo.incr_number_useful_goals(1); // un goal utile supplémentaire
		decompo.incr_number_evaluated_nodes(static_cast<unsigned int>( solution_plan->backtracks ));
	}
	decompo.incr_number_evaluated_goals(1); // incrémente le compteur de plan

	plans[plans_nb] = solution_plan;
	plans_nb++;

	// if k != plans_nb => the same decomposition is evaluated simultaneously by several threads !!!
	assert (decompo.get_number_evaluated_goals() == (unsigned int) plans_nb);

	decompo.plans_sub_add( daex::Plan() ); // On ne stocke plus les sous-plans mais on garde la structure notamment pour last_reached.
	decompo.last_subplan().search_steps( decompo.get_number_evaluated_nodes() );

#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
	eo::log << eo::xdebug << "\t\trecord steps...";
	eo::log.flush();
#endif
	step_recorder();

	solution_plan = NULL; // the corresponding pointer is stored in plans, thus we do not free it

#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
#endif

	}
	/*else { // return_code != NO_PLAN && != GOALS_MUTEX && != PLAN_FOUND
                                   throw std::runtime_error( "Unknown error code from cpt_search" );
	                  }*/
	return return_code;
}

void PlanningAggregaEval::compress( Planning & decompo ) {
#ifndef NDEBUG
	eo::log << eo::xdebug << "\t\tcompression...";
	eo::log.flush();
#endif
	// compression, utilise la globale "plans" construire plus haut et créé un plan compressé dans solution_plan
	yahsp_compress_plans();
	assert(solution_plan != NULL);
	// TODO pendant les tests, le plan ne peut pas etre vide, mais en compétition, cela peut arriver, auquel cas il faudra virer l'assert (penser à compiler en NDEBUG)

	assert(solution_plan->makespan > 0);

#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
	eo::log << eo::xdebug << "\t\tsave compressed plan and fitness...";
	eo::log.flush();
#endif
	decompo.plan_global( daex::Plan( solution_plan ) ); // sauvegarde le plan compressé global pour DAEx
	// NOTE: solution_plan is freed in free_yahsp_structures
	decompo.last_subplan().search_steps( decompo.get_number_evaluated_nodes() );
#ifndef NDEBUG
	eo::log << eo::xdebug << "ok" << std::endl;
#endif
}


void  PlanningAggregaEval::free_yahsp_structures(){
	{
#ifndef NDEBUG
		eo::log << eo::xdebug << "\t\tfree plans...";
		eo::log.flush();
#endif
		// libère la variable globale "plans", utilisée par yahsp lors de la compression
		for( unsigned int p=0; p < (unsigned int) plans_nb; ++p ) {
			plan_free( plans[p] );
		}
		plans_nb = 0;

		cpt_free( plans );

		if( solution_plan != NULL ) {
			plan_free( solution_plan );
			solution_plan = NULL;
		}
#ifndef NDEBUG
		eo::log << eo::xdebug << "ok" << std::endl;
#endif
	}
	;


}
