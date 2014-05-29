#include <eo>
#include <moeo>
#include <daex.h>
 
#include <utils/eoParser.h>
#include <utils/eoLogger.h>

#include "src/core/planningObjectiveVectorTraits.h"
#include "src/core/planningObjectiveVector.h"
#include "src/core/planning.h"
#include "src/core/planningEval.h"

// Parameters
#include "src/do/make_checkpoint_param.h"
#include "src/do/make_continue_param.h"
#include "src/do/make_general_param.h"
#include "src/do/make_init_param.h"

/// how to initialize the population
#include <do/make_pop.h>
///for the creation of an evaluator
#include "src/do/make_eval_dae.h"

#include "src/do/make_op_daemoeo.h"

/// the stopping criterion

#include "src/do/make_continue_daemoeo.h"
#include "src/do/make_checkpoint_daemoeo.h"

#include <do/make_checkpoint_moeo.h>

/// evolution engine (selection and replacement)
#include "src/do/make_ibea.h"


using namespace std;
using namespace daex;

typedef Planning<MOEO<PlanningObjectiveVector, double, double> > PlanningMOEO;
/// main
int main (int argc, char *argv[])
{
    
  	eoParser parser(argc, argv); // for user-parameter reading
 	eoState state;               // to keep all things allocated
  	make_verbose(parser);        // to keep all things allocated

  	// General parameters
  	daex::do_make_general_param(parser);            // Common part
  	daex::do_make_ibea_param(parser);               // IBEA part
  	
  	// Parameters makers COMMON PART
    daex::do_make_eval_param(parser);             
    daex::do_make_init_param(parser);             
    daex::do_make_variation_param(parser);        
    daex::do_make_checkpoint_param(parser);
    daex::do_make_continue_param(parser);
    
    // Parameters makers MO PART
    do_make_eval_mo_param(parser);
    
    make_help(parser);
    
    
    
    #ifndef NDEBUG  
    struct rlimit limit;
    getrlimit(RLIMIT_AS, &limit);
    eo::log << eo::logging << "Maximum size of the process virtual memory (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;
    getrlimit(RLIMIT_DATA, &limit);
    eo::log << eo::logging << "Maximum size of the process   data segment (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;

    /*
    // Hard coded memory usage limits
    limit.rlim_cur=100000000;
    limit.rlim_max=100000000;
    setrlimit(RLIMIT_AS, &limit);
    setrlimit(RLIMIT_DATA, &limit);

    getrlimit(RLIMIT_AS, &limit);
    std::cout << "Maximum size of the process virtual memory (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;
    getrlimit(RLIMIT_DATA, &limit);
    std::cout << "Maximum size of the process   data segment (soft,hard)=" << limit.rlim_cur << ", " << limit.rlim_max << std::endl;
    */
    
#endif
   
        

    
    daex::pddlLoad pddl(parser.valueOf<std::string>("domain"), parser.valueOf<std::string>("instance"));
    
 	///*** the representation-dependent things ***///
 	unsigned seed = parser.valueOf<unsigned int>("seed");
 	if (seed == 0) {
        // change the parameter itself, that will be dumped in the status file
        //        param_seed.value( time(0) );
        seed = time(0); // EO compatibility fixed by CC on 2010.12.24
    }
    eo::rng.reseed(seed);
    
    /// Initialization
    unsigned int l_max_init_coef = parser.valueOf<unsigned int>("lmax-initcoef");
    unsigned int l_min = parser.valueOf<unsigned int>("lmin");

	//StrategyInitStatic stratInit(rates);
	
    daex::Init<PlanningMOEO > init(pddl.chronoPartitionAtom(), l_max_init_coef, l_min);
    	
  	eoGenOp<PlanningMOEO>& variator = do_make_op<PlanningMOEO> (parser, state, pddl);
  	 
  	/// definition of the archive
    moeoUnboundedArchive<PlanningMOEO > arch;
  	  	
  	/// initialization of the population
    eoPop<PlanningMOEO >& pop = do_make_pop(parser, state, init);
     
    // The fitness evaluation
    eoEvalFuncCounter<PlanningMOEO >& eval_yahsp_moeo = do_make_eval_mo(parser, state, pop, init);
        
    /// stopping criteria
    eoContinue<PlanningMOEO >& continuator= do_make_continue_daemoeo(parser, state, eval_yahsp_moeo,arch);
       	 
    eoCheckPoint<PlanningMOEO >& checkpoint = do_make_checkpoint_daemoeo(parser, state, eval_yahsp_moeo, continuator, pop, arch);

    /// algorithm
    moeoIBEA<PlanningMOEO > &  ibea = do_make_ibea_moeo(parser, state, eval_yahsp_moeo, checkpoint, variator);

    // run the algo
    ibea(pop);

    // extract first front of the final population using an moeoArchive (this is the output of nsgaII)
    arch(pop);
    	 
    /// printing of the final archive
    cout << "Final Archive\n";
    arch.sortedPrintOn(cout);
    cout << endl;

    return EXIT_SUCCESS;
}
