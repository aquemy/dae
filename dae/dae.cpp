#include <sys/time.h>
#include <sys/resource.h>

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cfloat>

#include <eo>
#include <daex.h>
 
#include <utils/eoParser.h>
#include <utils/eoLogger.h>




using namespace std;
typedef daex::Decomposition T;

/// main
int main ( int argc, char* argv[] )
{
    eoParser parser(argc, argv); // for user-parameter reading
 	eoState state;                // to keep all things allocated
  	make_verbose(parser); // to keep all things allocated
   
 
   std::string domain = parser.createParam( (std::string)"./domain-zeno-time-miniRisk.pddl", "domain", "PDDL domain file", 'D', "Problem", true ).value();
    eo::log << eo::logging << "domain" << domain << std::endl;

    std::string instance = parser.createParam( (std::string)"./zeno3eMiniMulti.pddl", "instance", "PDDL instance file", 'I', "Problem", true ).value();
    eo::log << eo::logging  << "instance" << instance << std::endl;
    
    std::string plan_file = parser.createParam( (std::string)"plan.soln", "plan-file", "Plan file backup", 'F', "Output" ).value();
    eo::log << eo::logging <<  "plan-file" << plan_file << std::endl;

    // pop size
    unsigned int pop_size = parser.createParam( (unsigned int)100, "popSize", "Population Size", 'P', "Evolution Engine").value();
    eo::log << eo::logging <<  "pop_size" << pop_size << std::endl;

    // multi-start
    unsigned int maxruns = parser.createParam( (unsigned int)0, "runs-max", 
            "Maximum number of runs, if x==0: unlimited multi-starts, if x>1: will do <x> multi-start", 'r', "Stopping criterions" ).value();
    eo::log << eo::logging << "maxruns" << maxruns << std::endl;

    // b_max estimation
    bool insemination = parser.createParam(false, "insemination", "Use the insemination heuristic to estimate b_max at init", '\0', "Initialization").value();
    eo::log << eo::logging << "insemination" << insemination << std::endl;

    
    
    
     eoValueParam<unsigned int> & param_seed = parser.createParam( (unsigned int)0, "seed", "Random number seed", 'S' );


    unsigned int seed = 0;
    seed = param_seed.value();
    
    rng.reseed( seed );
    eo::log << eo::logging << "seed" << seed << std::endl;
    
    /*daex::do_make_eval_param( parser );
    daex::do_make_init_param( parser );
    daex::do_make_variation_param( parser );
    daex::do_make_breed_param( parser, pop_size);
    daex::do_make_checkpoint_param( parser );*/
    
    unsigned int maxgens = parser.valueOf<unsigned int>("gen-max");
    
    daex::pddlLoad pddl( domain, instance, SOLVER_YAHSP, HEURISTIC_H1, 1, std::vector<std::string>());
    daex::Goal::atoms( pddl.atoms() );

    return 0;
}

