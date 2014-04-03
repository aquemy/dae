
#ifndef __DECOMPOSITION_H__
#define __DECOMPOSITION_H__

#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <functional>
#include <iomanip>

#include <eo>

#include "goal.h"
#include "plan.h"
#include <src/globs.h>
#include <src/yahsp.h>

namespace daex
{

//! A decomposition is a list of Goal objects, and we are trying to minimize a scalar fitness (e.g. time or number of actions)
class Decomposition : public std::list<Goal>
{

public:
    
    //! At instanciation, a decomposition does not have any plan
    /*!
     * Note: and is not feasible, @see eoDualFitness
     */
    Decomposition() : 
        _plan_global(),
        _plans_sub(), 
        _b_max(0), 
        _k(0), 
        _u(0), 
        _B(0)
    {}  

    virtual ~Decomposition(){}
     
    Decomposition & operator=(const Decomposition & other)
    {
        if (this != &other) {
            std::list<Goal>::operator=(other);
            _plan_global = other.plan_copy();
            _plans_sub = other.subplans(); 
            _b_max = other.b_max();
            _k = other.get_number_evaluated_goals();
            _u = other.get_number_useful_goals();
            _B = other.get_number_evaluated_nodes();            
        }
        return *this;
    }
    
    //! After a modification of the decomposition, it needs to be re-evaluated
    //! Variation operator should use this method to indicate it
    virtual void invalidate() 
    {   
        // this->EO<eoMinimizingDualFitness>::invalidate();

        //clear the sub_plans vector
        //because if the decomposition becomes invalid, so are its intermediate plans
        this->plans_sub_reset();

        //plan vide
        this->_plan_global = daex::Plan();

    }
    
    daex::Plan plan_copy() const
    {
        return _plan_global;
    }

    daex::Plan & plan()
    {
        return _plan_global;
    }
    

    daex::Plan & subplan(unsigned int i) 
    {
        return _plans_sub[i];
    }

    std::vector<daex::Plan>  subplans()  const
    {
        return _plans_sub;
    }

    daex::Plan & last_subplan()
    {
        return *(_plans_sub.end() - 1 );
    }

    unsigned int subplans_size() const
    {
        return _plans_sub.size();
    }

    //! If no goal has been reached, return -1, else return the index of the goal
    int last_reached() const
    {
        return static_cast<int>( subplans_size() ) - 1;
    }

    //! If one has reached no goal or the first one, return 0, else return the index of the goal, if the end state has been reached, return the index of the last goal in the decomposition
    /*    unsigned int last_reached_safe() const
    {
        int last_reached = static_cast<int>( subplans_size() ) - 1;

        if( last_reached < 0 ) {
            last_reached = 0;

        } else if( last_reached >= this->size() ) {
            last_reached = this->size() - 1;
        }

        return static_cast<unsigned int>( last_reached );
    }
    */

    unsigned int last_reached_safe() const
    {
        if ( subplans_size() == 0 ) return 0;
        if ( subplans_size() > this->size()) return this->size() - 1;
        return subplans_size() - 1 ;
    }

    /*
    Decomposition::iterator iter_last_reached()
    {
        return iter_at( subplans_size() - 1 );
    }
    */

    void plan_global( daex::Plan p )
    {
        _plan_global = p;
    }

    void plans_sub_add( daex::Plan p ) 
    {
        _plans_sub.push_back( p );
    }

    void plans_sub_reset()
    {
        _plans_sub.clear();

        // on prévoit un sous-plan de plus que le nombre de stations
        // pour la dernière étape
        _plans_sub.reserve( this->size() + 1 );
    }

    virtual void printOn( std::ostream & out ) const 
    {
       // EO< eoMinimizingDualFitness >::printOn(out);
        out << " ";

        out << "(Decomposition[" <<  this->size() << "]: ";

        std::copy( this->begin(), this->end(), std::ostream_iterator<Goal>(out, " ") );

        out << ")";
        
        out << this->plan_copy(); 
    }
    
    virtual void readFrom(std::istream & _is) {(void*)_is;};


    Decomposition::iterator iter_at( unsigned int i )
    {
        if( i >= this->size() ) {
            std::ostringstream msg;
            msg << "asked for element " << i << " but size of the Decomposition is " << this->size();
            throw( std::out_of_range( msg.str() ) );
        }

        Decomposition::iterator it = this->begin();

        std::advance( it, i );

        return it;
    }

    // VV : getters/setters for 4 fields taken from daeCptYahspEval
    void b_max( unsigned int b ) { _b_max = b; }
    unsigned int b_max() const { return _b_max; } 

    unsigned int get_number_evaluated_goals()const { return _k; } 
    void reset_number_evaluated_goals() { _k = 0; }
    void incr_number_evaluated_goals(unsigned int k) { _k += k; }

    unsigned int get_number_useful_goals()const { return _u; } 
    void reset_number_useful_goals() { _u = 0; }
    void incr_number_useful_goals(unsigned int u) { _u += u; }

    unsigned int get_number_evaluated_nodes() const { return _B; }
    void reset_number_evaluated_nodes() { _B = 0; }
    void incr_number_evaluated_nodes(unsigned int B) { _B += B; }

protected:

    //! daex::Plan global compressé
    daex::Plan _plan_global;

    //! Vecteur des sous-plans
    std::vector< daex::Plan > _plans_sub;

    // VV : 4 fields made local to decomposition instead of daeCptYahspEval

    //! Current number of backtracks/nodes allowed
    unsigned int _b_max;

    //! compteur de goals
    unsigned int _k;

    //! compteur de goals utiles
    unsigned int _u;

    //! compteur des tentatives de recherche
    unsigned int _B;
    
    

}; // class Decomposition

//! Print a decomposition in a simple format
/** On a single line, print the date and the number of atoms of each goal, i.e.:
 *    Decomposition (size): goal(#atoms) ...
 *  e.g.:
 *    Decompositon (3): 2(5) 12(45) 123(4)
 */
template<class EOT>
void simplePrint( std::ostream & out, EOT & decompo )
{
    out << "Decomposition " 
        << std::right << std::setfill(' ') << std::setw(3) 
        << "[" << decompo.size() << "]: ";

    for(typename EOT::iterator igoal = decompo.begin(), end = decompo.end(); igoal != end; ++igoal ) {
        out << "\t" << std::right << std::setfill(' ') << std::setw(3)
            << igoal->earliest_start_time() << "(" << igoal->size() << ")";
    }

    out << std::endl;
}


} // namespace daex

#endif

