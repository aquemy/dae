
#ifndef __DAEX_yahsp_plan_H__
#define __DAEX_yahsp_plan_H__

#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

//extern "C" {
#include <src/plan.h>
//}


namespace daex
{

class Plan
{
protected:

    //! The makespan/cost of the plan, as extracted from the YAHSP SolutionPlan * pointer in the constructor
    TimeVal _makespan;
    TimeVal _cost_add;
    TimeVal _cost_max;
 
    //! Nombre d'étapes de recherche
    /* Nombre de backtracks si solveur type CPT,
     * nombre d'itérations si solveur type YAHSP.
     */
    unsigned int _search_steps;

    //! True if the plan is correctly initialized and contains a SolutionPlan
    bool _is_valid;

    //! The string representation of the plan
    std::string _plan_rep;

public:

    //! Construct a valid plan from a YAHSP's pointer: get the makespan and the string representation
    
     Plan() : 
        _makespan(INT_MAX), 
        _cost_add(INT_MAX),
        _cost_max(INT_MAX),
        _search_steps(0), 
        _is_valid(false), 
        _plan_rep("No plan")
    {}
	
      ~Plan(){}
     
     Plan( SolutionPlan * p_plan ) : 
        _makespan(p_plan->makespan),
        _cost_add(p_plan ->cost_add), 
        _cost_max(p_plan-> cost_max),
        _search_steps(0), 
        _is_valid(true)
      {   // get the plan representation
// OMP DIRTY
#pragma omp critical
        _plan_rep = plan_to_str( p_plan );
      }
    
    //! Construct a invalid plan from scratch
    /*! @TODO INT_MAX may not be the best choice here, FIXME
     */
    Plan  & operator=(const daex::Plan  & other)
    {
       if (this != &other) 
       {
            _makespan = other._makespan;
            _cost_add = other._cost_add; 
            _cost_max = other._cost_max;
            _search_steps = other._search_steps;
            _is_valid = other._is_valid;
	        _plan_rep  = other._plan_rep;
        }
        return *this;
    }

    void search_steps( unsigned int steps ) { _search_steps = steps; }
    unsigned int search_steps() const { return _search_steps; }

    TimeVal makespan() const { return _makespan; }
    
    TimeVal cost_add() const {return _cost_add;}
     
    TimeVal cost_max() const {return _cost_max;}

    void makespan(TimeVal makespan){ _makespan = makespan;} // mutateur nouvellement introduit
    
    void cost_add(TimeVal cost_add){_cost_add = cost_add;}
     
    void cost_max(TimeVal cost_max){_cost_max = cost_max;}

    bool isValid(){return _is_valid;}

    void isValid(bool is_valid){_is_valid = is_valid;}

    //! Print a SolutionPlan in a string using YAHSP's print_plan_ipc function
    std::string plan_to_str( SolutionPlan * p_plan )
    {        
        std::ostringstream out;

        char* buffer;
        size_t buffer_size;

        FILE* stream = open_memstream( & buffer, & buffer_size );

        if( stream == NULL ) {
            std::ostringstream msg;
            msg << "Cannot open memstream for printing Plan (" << p_plan << ")";
            throw std::runtime_error( msg.str() );
        }

        // CPT function @ plan.c:66
        // see also print_plan @ plan.c:32
        print_plan_ipc( stream, p_plan, 0.0 ); // last arg is the time taken FIXME ?

        fclose( stream );

        out << buffer;

        free( buffer );

        return out.str();
    }

    std::string escape_newlines( const std::string &in, const std::string &search="\n", const std::string &replace="\\n" ) const
    {
        std::string s = in;
        for(size_t pos = 0; ; pos += replace.length()) {
            // find the substring
            pos = s.find( search, pos );
            if( pos == std::string::npos ) break;
            // erase and insert == replace
            s.erase( pos, search.length() );
            s.insert( pos, replace );
        }
        return s;
    }

    std::string plan_to_str_escaped( SolutionPlan * p_plan )
    {
        return escape_newlines( plan_to_str( p_plan ) );
    }

    //! Print the string rep on a ostream
    friend std::ostream& operator<<( std::ostream& out, const daex::Plan & plan )
    {
        out << plan.plan_rep();
	    return out;
    }

    std::string plan_rep() const
    {
        return _plan_rep ;
	}

};

} // namespace daex

#endif // __DAEX_yahsp_plan_H__

