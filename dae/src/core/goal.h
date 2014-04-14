
#ifndef __GOAL_H__
#define __GOAL_H__

#include <iterator>
#include <iostream>

#include <eo>

#include "atom.h"
#include "strategies.h"

namespace daex {

class Goal : public std::list<Atom*>
{
public:

    Goal(TimeVal t, std::vector<double> rates = std::vector<double>(NB_YAHSP_STRAT, 1)) :
        _earliest_start_time(t),
        strat(Strategy<Goal>(rates))
    {}
    

    TimeVal earliest_start_time(  ) const
    {
        return _earliest_start_time;
    }

    void earliest_start_time(TimeVal d)
    {
        _earliest_start_time = d;
    }

    friend std::ostream& operator<<(std::ostream & out, const Goal & goal)
    {
        out << "(Goal[" << goal.size() << "]: ";

        if( goal.size() != 0 ) 
        {
            std::list<Atom*>::const_iterator it = goal.begin();
            out << *(*it);
            it++;

            while( it != goal.end() ) 
            {
                out << " " << *(*it);
                it++;
            }
        }

        out << ")";
        return out;
    }

    Goal::iterator iter_at( unsigned int i )
    {
        if( i >= this->size() ) {
            std::ostringstream msg;
            msg << "asked for element " << i << " but size of the Goal is " << this->size();
            throw( std::out_of_range( msg.str() ) );
        }

        Goal::iterator it = this->begin();
        std::advance(it,i);

        return it;
    }
    
    Objective objective()
    {
        return strat(*this);
    }
    
    void setStratRates(std::vector<double> rates)
    {
        strat = rates;
    }

protected:

    Strategy<Goal> strat;
    
    //! Earliest start time among all atoms
    TimeVal _earliest_start_time;
};

} // namespace daex

#endif // __GOAL_H__

