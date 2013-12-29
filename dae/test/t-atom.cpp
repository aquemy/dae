#include <eo>
#include <core/atom.h>
#include <daex.h>
#include <utils/pddl_load.h> 

using namespace daex;
using namespace std;

int main(int argc, char* argv[])
{
    eoParser parser(argc, argv);
    eoState state;
    make_verbose(parser);
    
    std::string domain = parser.createParam( (std::string)"./domain-zeno-time-miniRisk.pddl", "domain", "PDDL domain file", 'D', "Problem", true ).value();
    eo::log << eo::logging << "domain" << domain << std::endl;

    std::string instance = parser.createParam( (std::string)"./zeno3eMiniMulti.pddl", "instance", "PDDL instance file", 'I', "Problem", true ).value();
    eo::log << eo::logging  << "instance" << instance << std::endl;
    
    daex::pddlLoad pddl( domain, instance, SOLVER_YAHSP, HEURISTIC_H1, 1, std::vector<std::string>());
    
    for(unsigned i = 0; i < pddl.atoms().size(); i++)
    {
        std::cout << *(pddl.atoms())[i] << std::endl;
        std::cout << pddl.atoms()[i]->earliest_start_time() << std::endl;
        std::cout << pddl.atoms()[i]->fluent() << std::endl;
    }
    eo::log << eo::progress << "Load the instance...OK" << std::endl;
    eo::log << eo::progress << "Initialization...";
    eo::log.flush();

    try
    {
        
    }
    catch(exception& e)
    {
      cout << "Exception: " << e.what() << '\n';
    }
    
    return 0;
}
