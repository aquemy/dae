#include <eo>
#include <moeo>
#include <daex.h>
 
#include <utils/eoParser.h>
#include <utils/eoLogger.h>

#include "src/core/planningObjectiveVectorTraits.h"
#include "src/core/planningObjectiveVector.h"
#include "src/core/planning.h"
#include "src/core/planningEval.h"
#include "src/core/moeoDaex.h"

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
#include <do/make_ea_moeo.h>


using namespace std;


/// main
int main (int argc, char *argv[])
{
        
  	eoParser parser(argc, argv); // for user-parameter reading
 	eoState state;                // to keep all things allocated
  	make_verbose(parser); // to keep all things allocated
   
  	// General parameters
  	daex::do_make_general_param(parser);            // Common part
  	daex::do_make_general_param_moeo(parser);       // Multiobjectives part
  	
  	// Parameters makers
    daex::do_make_eval_param(parser);             
    daex::do_make_init_param(parser);             
    daex::do_make_variation_param(parser);        
    //daex::do_make_breed_param(parser, pop_size);
    daex::do_make_checkpoint_param(parser);
    //daex::do_make_replace_param(parser);
    daex::do_make_continue_param(parser);
    
    make_help(parser);
    
    daex::pddlLoad pddl(parser);
    
 	///*** the representation-dependent things ***///
    
    /// Initialization
    unsigned int l_max_init_coef = parser.valueOf<unsigned int>("lmax-initcoef");
    unsigned int l_min = parser.valueOf<unsigned int>("lmin");
    daex::Init<Planning> init(pddl.chronoPartitionAtom(), l_max_init_coef, l_min );
    
  	eoGenOp<Planning>& variator = do_make_op (parser, state, pddl);
  	 
  	 /// definition of the archive
    moeoUnboundedArchive<Planning> arch;
  	  	
  	/// initialization of the population
    eoPop<Planning>& pop = do_make_pop(parser, state, init);
              
    /// The fitness evaluation
    eoEvalFuncCounter<Planning>& eval_yahsp_moeo = do_make_eval(parser,state,pop, init);
    
    /// stopping criteria
    eoContinue<Planning>& continuator= do_make_continue_daemoeo(parser, state, eval_yahsp_moeo,arch);
       	 
    eoCheckPoint<Planning>& checkpoint = do_make_checkpoint_daemoeo (parser, state,   eval_yahsp_moeo, continuator, pop, arch);
   
    // algorithm
    moeoSPEA2<Planning> speaII (checkpoint, eval_yahsp_moeo, variator,arch);
    
    // run the algo
    speaII(pop);

    // printing of the final archive
    cout << "Final Archive\n";
    arch.sortedPrintOn(cout);
    cout << endl;

    return EXIT_SUCCESS;
}
