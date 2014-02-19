#include <sys/time.h>
#include <sys/resource.h>

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cfloat>

#include <eo>
#include <eo>
#include <moeo>
#include <daex.h>

//#include <do/make_pop.h>
#include <ga.h>
#include <utils/eoFeasibleRatioStat.h>
#include "src/core/planningObjectiveVectorTraits.h"
#include "src/core/planningObjectiveVector.h"
#include "src/core/planning.h"
#include "src/core/planningEval.h"
#include "src/core/moeoDaex.h"
#include "src/do/make_genotype_daemoeo.h"

#include "daex.h"


#include <utils/eoTimer.h>

int main ( int argc, char* argv[] )
{

    typedef daex::Decomposition T;


    /**************
     * PARAMETERS *
     **************/

    // EO
    eoParser parser(argc, argv);
    make_verbose(parser);
    eoState state;

    // GENERAL PARAMETERS
    // createParam (ValueType _defaultValue, std::string _longName, std::string _description, char _shortHand=0, std::string _section="", bool _required=false)
    std::string domain = parser.createParam( (std::string)"domain-zeno-time.pddl", "domain", "PDDL domain file", 'D', "Problem", true ).value();
    
    std::string instance = parser.createParam( (std::string)"zeno10.pddl", "instance", "PDDL instance file", 'I', "Problem", true ).value();
   
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


    /***********
     * PARSING *
     ***********/

    // PDDL

    daex::pddlLoad pddl( domain, instance, SOLVER_YAHSP, HEURISTIC_H1, eo::parallel.nthreads(), std::vector<std::string>());
    //daex::Goal goals( & pddl.atoms() );
    

    /******************
     * INITIALIZATION *
     ******************/

    daex::Init<Planning> & init = do_make_genotype(parser, state, pddl);
   
    // randomly generate the population with the init operator
    eoPop<Planning> pop = eoPop<Planning>( pop_size, init ) ;

    // used to pass the eval count through the several eoEvalFuncCounter evaluators
    unsigned int eval_count = 0;

    TimeVal best_makespan = INT_MAX;

    eoEvalFuncCounter<Planning> eval = do_make_eval(parser, state, pop, init);
   
    /*std::pair< eoEvalFunc<T>&, eoEvalFuncCounter<T>* > eval_pair
        = daex::do_make_eval_op<T>(
                parser, state, init.l_max(), eval_count, b_max_in, b_max_last, plan_file, best_makespan, dump_sep, dump_file_count, metadata
                );
    eoEvalFunc<T>& eval = eval_pair.first;*/

    eoPopLoopEval<T> pop_eval( eval );

    // a first evaluation of generated pop
    pop_eval( pop, pop );

    /********************
     * EVOLUTION ENGINE *
     ********************/


    eoCombinedContinue<T> continuator = daex::do_make_continue_op<T>( parser, state );

    // Direct access to continuators are needed during restarts (see below)
    eoGenContinue<T> & maxgen
        = *( dynamic_cast< eoGenContinue<T>* >( continuator.at(0) ) );

    // CHECKPOINTING
    eoCheckPoint<T> & checkpoint = daex::do_make_checkpoint_op( continuator, parser, state, pop);

    
    // VARIATION
    daex::MutationDelGoal<T>* delgoal = new daex::MutationDelGoal<T>;
    eoGenOp<T> & variator = daex::do_make_variation_op<T>( parser, state, pddl, delgoal );

    
    // Selection
    eoGeneralBreeder<T> & breeder = daex::do_make_breed_op<T>( parser, state, variator );

    // Replacement
    eoReplacement<T> & replacor = daex::do_make_replace_op<T>( parser, state );
    unsigned int offsprings = parser.valueOf<unsigned int>("offsprings");

    eoEasyEA<T> dae( checkpoint, eval, pop_eval, breeder, replacor, offsprings );

    // best decomposition of all the runs, in case of multi-start
    // start at the best element of the init
    T best = pop.best_element();

    unsigned int run = 1;

    // Evaluate an empty decomposition, for comparison with decomposed solutions
    T empty_decompo;

    eval( empty_decompo );

    return 0;
}

