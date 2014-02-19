#include <eo>
#include <moeo>
#include <daex.h>
 
#include <utils/eoParser.h>
#include <utils/eoLogger.h>

#include "src/core/moplanning.h"
#include "src/core/moplanningEval.h"
#include "src/core/moDaex.h"

#include "src/do/make_pddl_dae.h"
///for the creation of an initializer
#include "src/do/make_genotype_daemoeo.h"
/// how to initialize the population
#include <do/make_pop.h>
///for the creation of an evaluator
#include "src/do/make_eval_mo.h"

#include "src/do/make_op_dae.h"

/// the stopping criterion

#include "src/do/make_continue_daemoeo.h"
#include "src/do/make_checkpoint_daemoeo.h"

/// evolution engine (selection and replacement)
#include "src/do/make_ea_moeo.h"


using namespace std;


/// main
int main (int argc, char *argv[])
{
       
         
  	eoParser parser(argc, argv); // for user-parameter reading
 	eoState state;                // to keep all things allocated
  	make_verbose(parser); // to keep all things allocated
  	
  	std::string domain = parser.createParam( (std::string)"domain-zeno-time.pddl", "domain", "PDDL domain file", 'D', "Problem", true ).value();
    
    std::string instance = parser.createParam( (std::string)"zeno10.pddl", "instance", "PDDL instance file", 'I', "Problem", true ).value();
    
    bool is_sequential = parser.createParam( (bool)false, "sequential", "Is the problem a sequential one?", 'q', "Problem", true ).value();
   
    std::string plan_file = parser.createParam( (std::string)"plan.soln", "plan-file", "Plan file backup", 'F', "Output" ).value();
    
    // pop size
    unsigned int pop_size = parser.createParam( (unsigned int)100, "popSize", "Population Size", 'P', "Evolution Engine").value();
   
    // multi-start
    unsigned int maxruns = parser.createParam( (unsigned int)0, "runs-max", 
            "Maximum number of runs, if x==0: unlimited multi-starts, if x>1: will do <x> multi-start", 'r', "Stopping criterions" ).value();
   
    // b_max estimation
    bool insemination = parser.createParam(false, "insemination", "Use the insemination heuristic to estimate b_max at init", '\0', "Initialization").value();
    
    // seed
    eoValueParam<unsigned int> & param_seed = parser.createParam( (unsigned int)0, "seed", "Random number seed", 'S' );
    // if one want to initialize on current time
    if ( param_seed.value() == 0) {
        // change the parameter itself, that will be dumped in the status file
        //        param_seed.value( time(0) );
        param_seed.value() = time(0); // EO compatibility fixed by CC on 2010.12.24
    }

    unsigned int seed = 0;
    seed = param_seed.value();


    rng.reseed( seed );
  
    // Parameters makers
    unsigned int fitness_weight = parser.createParam( (unsigned int)10, "fitness-weight", 
            "Unknown weight in the feasible and unfeasible fitness computation", 'W', "Evaluation" ).value();
    
    unsigned int fitness_penalty = parser.createParam( (unsigned int)2, "fitness-penalty", 
            "Penalty in the unfeasible fitnesses computation", 'w', "Evaluation" ).value();
    
#ifndef SINGLE_EVAL_ITER_DUMP
    unsigned int max_seconds = parser.createParam( (unsigned int)0, "max-seconds", 
            "Maximum number of user seconds in CPU for the whole search, set it to 0 to deactivate (1800 = 30 minutes)", 'i', "Stopping criterions" ).value(); // 1800 seconds = 30 minutes
    
#endif
    
    unsigned int b_max_init = parser.createParam( (unsigned int)1e4, "bmax-init", "Number of allowed expanded nodes for the initial computation of b_max", 'B', "Evaluation" ).value();
    
    /* nonsense with the incremental strategy
    double b_max_quantile = parser.createParam( (double)0.5, "bmax-quantile", 
            "Quantile to use for estimating b_max (in [0,1], 0.5=median)", 'Q', "Evaluation" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "b_max_quantile" << b_max_quantile << std::endl;
    if( b_max_quantile < 0 || b_max_quantile > 1 ) {
        std::cout << "bmax-quantile must be a double in [0,1] (=" << b_max_quantile << ") type --help for usage." << std::endl;
        exit(1);
    }looser throw specifier for
    */

    unsigned int b_max_fixed = parser.createParam( (unsigned int)0, "bmax-fixed", "Fixed number of allowed expanded nodes. Overrides bmaxinit if != 0", 'b', "Evaluation" ).value();
   
    double b_max_last_weight = parser.createParam( (double)3, "bmax-last-weight",
            "Weighting for the b_max used during the last search towards the end goal (must be strictly positive)", 'T', "Evaluation" ).value();
    
    if( b_max_last_weight <= 0 ) {
        std::cout << "bmax-last-weight must be strictly positive (=" << b_max_last_weight << ") type --help for usage." << std::endl;
        exit(1);
    }
    
    double b_max_ratio = parser.createParam( 0.01, "bmax-ratio","Satisfying proportion of feasible individuals for the computation of b_max", 'J', "Evaluation" ).value();
   
    unsigned int l_max_init_coef = parser.createParam( (unsigned int)2, "lmax-initcoef", 
            "l_max will be set to the size of the chrono partition * this coefficient", 'C', "Initialization" ).value();

    unsigned int l_min = parser.createParam( (unsigned int)1, "lmin", 
            "Minimum number of goals in a decomposition", 'L', "Initialization" ).value();

    // Evaluation
    double b_max_increase_coef = parser.createParam( (double)2, "bmax-increase-coef", "Multiplier increment for the computation of b_max", 'K', "Evaluation" ).value();
    
    // Variation
    unsigned int radius = parser.createParam( (unsigned int)2, "radius", 
            "Number of neighbour goals to consider for the addGoal mutation", 'R', "Variation" ).value();
    
    double proba_change = parser.createParam( (double)0.8, "proba-change", 
            "Probability to change an atom for the changeAtom mutation", 'O', "Variation" ).value();
    
    double proba_del_atom = parser.createParam( (double)0.8, "proba-del-atom", 
            "Average probability to delete an atom for the delAtom mutation", 'd', "Variation" ).value();

    double w_delgoal = parser.createParam( (double)1, "w-delgoal", 
            "Relative weight defining the probability to call the delGoal mutation", 'a', "Variation" ).value();
    
    double w_addgoal = parser.createParam( (double)3, "w-addgoal", 
            "Relative weight defining the probability to call the addGoal mutation", 'A', "Variation" ).value();
    
    double w_delatom = parser.createParam( (double)1, "w-delatom", 
            "Relative weight defining the probability to call the delAtom mutation", 'g', "Variation" ).value();
    
    double w_addatom = parser.createParam( (double)1, "w-addatom", 
            "Relative weight defining the probability to call the addAtom mutation", 'G', "Variation" ).value();
    
    double proba_cross = parser.createParam( (double)0.2, "proba-cross", 
            "Probability to apply a cross-over", 'c', "Variation" ).value();
    
    double proba_mut = parser.createParam( (double)0.8, "proba-mut", 
            "Probability to apply one of the mutation", 'm', "Variation" ).value();
    
    // Selection
    unsigned int toursize = parser.createParam( (unsigned int)5, "tournament", 
            "Size of the deterministic tournament for the selection", 't', "Selection" ).value();
    
    unsigned int offsprings = parser.createParam( (unsigned int)pop_size*7, "offsprings", 
            "Number of offsprings to produces", 'f', "Selection" ).value();
    
    unsigned int out_save_freq = parser.createParam((unsigned int)0, "out-save-freq", "Save every F generation (0 = only final state, absent = never)", '\0', "Persistence" ).value();
   
    // shoudl we empty it if exists
    std::string out_dir = parser.createParam(std::string("results"), "out-dir", "Directory to store DISK outputs", '\0', "Output").value();
   
    bool out_dir_erase = parser.createParam(true, "out-dir-erase", "erase files in out-dir, if any", '\0', "Output").value();
    
    unsigned int mingen = parser.createParam( (unsigned int)10, "gen-min", 
            "Minimum number of iterations", 'n', "Stopping criterions" ).value();
        
    unsigned int steadygen = parser.createParam( (unsigned int)50, "gen-steady", 
            "Number of iterations without improvement", 's', "Stopping criterions" ).value();
        
    unsigned int maxgens = parser.createParam( (unsigned int)1000, "gen-max", 
            "Maximum number of iterations", 'x', "Stopping criterions" ).value();

    make_help( parser );
  	
   
  	daex::pddlLoad & pddl = do_make_pddl ( parser,  state);
  	
  	cout << "A" << endl;
    
 	///*** the representation-dependent things ***///

    /// the genotype (through a genotype initializer)
    daex::Init<PlanningMO> & init = do_make_genotype<PlanningMO>(parser, state, pddl); 	
    cout << "B" << endl;
  	eoGenOp<PlanningMO>& variator = do_make_op<PlanningMO>(parser, state, pddl);
  	cout << "C" << endl;
  	
  	// Breeder
  	eoSelectOne<PlanningMO> * p_selectone;
    if ( toursize == 1 ) {
    // L'article indique qu'il n'y a pas de sélection, on aurait alors ça :
      p_selectone = (eoSelectOne<PlanningMO> *) ( new eoSequentialSelect<PlanningMO> ( true ) );
    }
    else {
    // MAIS le code utilise un tournoi déterministe, on a donc ça :
      p_selectone = (eoSelectOne<PlanningMO> *) ( new eoDetTournamentSelect<PlanningMO> ( toursize ) );
    }
    state.storeFunctor( p_selectone );
    cout << "D" << endl;
    // selector, variator, rate (for selection), interpret_as_rate
    eoGeneralBreeder<PlanningMO>  breed(*p_selectone, variator, (double)offsprings, false);
    cout << "E" << endl;

  	/// initialization of the population    
    eoPop<PlanningMO>& pop = do_make_pop(parser, state, init);
              
         cout << "F" << endl;
        /// The fitness evaluation
     
        eoEvalFuncCounter<PlanningMO>& eval_yahsp_moeo = do_make_eval(parser,state,pop, init);
        cout << "G" << endl;
        eoPopLoopEval<PlanningMO> eval(eval_yahsp_moeo);
          /// stopping criteria
         cout << "H" << endl;
         //eoCheckPoint<PlanningMO>& checkpoint = do_make_checkpoint_daemoeo (parser, state,   eval_yahsp_moeo, continuator, pop, arch);
         
         // Continue
         eoGenContinue<PlanningMO> maxgen( maxgens );
    state.storeFunctor(&maxgen );
cout << "I" << endl;
    // combine the continuators
    eoCombinedContinue<PlanningMO> continuator(maxgen);
    state.storeFunctor(& continuator );
    eoSteadyFitContinue<PlanningMO> steadyfit(mingen, steadygen );
    state.storeFunctor(&steadyfit);
    continuator.add(steadyfit);
        cout << "J" << endl;
    eoCommaReplacement<PlanningMO> replacor;
    cout << "K" << endl;
         /// algorithm
    //eoEasyEA<PlanningMO> algo(continuator, eval_yahsp_moeo, variator);
    eoEasyEA<PlanningMO> algo(continuator, eval_yahsp_moeo,  eval, breed, replacor, offsprings );     	 
         cout << "L" << endl;
	/// help ?
        
       make_help(parser); 

       ///*** Go ! ***///
       
       /// printing of the  best of the initial population
        
//        cout << "Initial Population\n";
//        pop.sort();
//        //cout<<pop;
//        cout<<pop.front();
//        cout << endl;

       /// run the algo
       algo(pop);
        cout << "M" << endl;
       /// printing of the best of the final population
       cout << "Final Population\n";
       pop.sortedPrintOn(cout);
       cout<<pop.front();
       cout << endl;

      /// printing of the final archive
//        cout << "Final Archive\n";
//        arch.sortedPrintOn(cout);
//        cout << endl;


    return EXIT_SUCCESS;
}
