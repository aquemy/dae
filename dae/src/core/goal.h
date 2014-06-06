
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

    Goal(TimeVal t) :
        _earliest_start_time(t),
        strat(NULL)
    {}
    
    // FixMe : Ca fait segfault sans raison apparante. Du coup, fuite mémoire...
    /*virtual ~Goal() 
    {
        if(strat != NULL)
            delete strat;
    }   
    
    Goal (const Goal& other)
    {
        *this = other;
    }*/
  	
    
    Goal operator=(const Goal& other)
    {
        _earliest_start_time = other._earliest_start_time;
        if (this != &other) {
            if(other.strat != NULL)
                strat = other.strat->clone(); // We need to clone the strategy
        }
        
        return *this;
    }
  

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
    
    void strategy(Strategy<Goal>* _strat)
    {
        strat = _strat;
    }
    
    Objective strategy()
    {   
        #ifndef NDEBUG
        assert(strat != NULL);
        #endif
        return (*strat)(*this);
    }
    
    void strategyUpdate(double indicator)
    {   
        #ifndef NDEBUG
        assert(strat != NULL);
        #endif
        return strat->update(indicator);
    }
    
    void strategyMutation()
    {   
        #ifndef NDEBUG
        assert(strat != NULL);
        #endif
        return strat->mutation();
    }

protected:

    //! Earliest start time among all atoms
    TimeVal _earliest_start_time;
    Strategy<Goal>* strat;

};

} // namespace daex

#endif // __GOAL_H__

