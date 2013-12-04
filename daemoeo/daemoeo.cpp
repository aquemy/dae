#include <eo>
#include <moeo>
#include <daex.h>
 
#include <utils/eoParserLogger.h>
#include <utils/eoLogger.h>

#include "src/core/planningObjectiveVectorTraits.h"
#include "src/core/planningObjectiveVector.h"
#include "src/core/planning.h"
#include "src/core/planningEval.h"
#include "src/core/moeoDaex.h"

#include "src/do/make_pddl_dae.h"
///for the creation of an initializer
#include "src/do/make_genotype_daemoeo.h"
/// how to initialize the population
#include <do/make_pop.h>
///for the creation of an evaluator
#include "src/do/make_eval_dae.h"

#include "src/do/make_op_daemoeo.h"

/// the stopping criterion

#include "src/do/make_continue_daemoeo.h"
#include "src/do/make_checkpoint_daemoeo.h"

/// evolution engine (selection and replacement)
#include <do/make_ea_moeo.h>


using namespace std;


/// main
int main (int argc, char *argv[])
{
        
  	eoParserLogger parser(argc, argv); // for user-parameter reading
 	eoState state;                // to keep all things allocated
  	make_verbose(parser); // to keep all things allocated
   
  	daex::pddlLoad & pddl = do_make_pddl ( parser,  state);
  	
  	

 	///*** the representation-dependent things ***///

       	/// the genotype (through a genotype initializer)
     	daex::Init<Planning> & init = do_make_genotype(parser, state, pddl);
     	  	
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
   
    	  
         /// algorithm
         eoAlgo<Planning>& algo = do_make_ea_moeo(parser, state, eval_yahsp_moeo, checkpoint, variator, arch);
          
         
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
