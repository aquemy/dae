
#ifndef PLANNING_H_
#define PLANNING_H_

 
//#include <moeo>
#include "planningObjectiveVector.h"
#include <iterator>
#include <list>
#include <core/MOEO.h>
#include <daex.h>

namespace daex {

/**
 *  Structure of the genotype for the planning problem: a vector of decomposition and an objective vector.
 */
template < class MOEOObjectiveVector = PlanningObjectiveVector, class MOEOFitness = double, class MOEODiversity = double > 
class Planning: public MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >, 
                public daex::Decomposition
{
public:

    typedef MOEOFitness Fitness;

    using daex::Decomposition :: begin;
    using daex::Decomposition :: end;
    using daex::Decomposition :: resize;
    using daex::Decomposition :: size;
     
    Planning(): 
        MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >(), 
        daex::Decomposition(),
        _is_feasible(false)
    {}
     
    virtual ~Planning() {}   
      
    std::string className() const 
    { 
        return "Planning";
    } 
  	
  	
     Planning & operator=(const Planning & other)
     {
        if (this != &other) {
             MOEO< MOEOObjectiveVector, MOEOFitness, MOEODiversity >::operator=(other);
             Decomposition::operator=(other); 
             _is_feasible = other._is_feasible ;
        }
        return *this;
    }
    
    virtual void invalidate()
    {
        MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity > ::invalidate();
        daex::Decomposition::invalidate();
    }
    
    void value(const MOEO<MOEOObjectiveVector,MOEOFitness, MOEODiversity>  & _moeo)
    {
        if (_moeo.size() != size())	   // safety check
        {
            if (size())		   // NOT an initial empty std::vector
            {
                std::cout << "Warning: Changing size in moeoVector assignation"<<std::endl;
                resize(_moeo.size());
            }
            else
            {
                throw std::runtime_error("Size not initialized in moeoVector");
            }
        }
     
        std::copy( _moeo.begin(), _moeo.end(),  this->begin() ); 
        invalidate();
    }

    virtual void printOn(std::ostream & _os) const
    {
		MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::printOn(_os);
        _os << ' ';
        Decomposition::printOn(_os);  
    }
    
    /**
     * Reading object
     * @param _is input stream
     */
    virtual void readFrom(std::istream & _is)
    {
       MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::readFrom(_is);
       Decomposition::readFrom(_is);
    }

  
    void setFeasible(bool  b)
    {
	    _is_feasible = b;
	}
 
    bool is_feasible() const 
    {
        return _is_feasible;
    }
     
    bool operator< (const MOEO<MOEOObjectiveVector,MOEOFitness, MOEODiversity>  & _moeo) const
    {
        return MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::operator<(_moeo);
    }
   
protected:
   
    bool _is_feasible;
 
};

/**
 * To avoid conflicts between MOEO::operator< and std::vector<double>::operator<
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity>
bool operator<(const Planning< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _moeo1, const 
Planning< MOEOObjectiveVector, MOEOFitness, MOEODiversity > & _moeo2)
{
    return _moeo1.operator<(_moeo2);
}


/**
 * To avoid conflicts between MOEO::operator> and std::vector<double>::operator>
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity >
bool operator>(const Planning< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _moeo1, const moeoVector< MOEOObjectiveVector, MOEOFitness, MOEODiversity > & _moeo2)
{
    return _moeo1.operator>(_moeo2);
}


template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity > 
std::ostream & operator << ( std::ostream& _os, const Planning< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _o ) 
{
    _o.printOn(_os);
    return _os;
} 

} // namespace daex

#endif /*PLANNING_H_*/
