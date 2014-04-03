
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
//MOEO<MOEOObjectiveVector,MOEOFitness, MOEODiversity>
template < class BaseT > 
class Planning: public BaseT, 
                public daex::Decomposition
{
public:

    typedef typename BaseT::Fitness Fitness;

    using daex::Decomposition :: begin;
    using daex::Decomposition :: end;
    using daex::Decomposition :: resize;
    using daex::Decomposition :: size;
     
    Planning(): 
        BaseT(), 
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
             BaseT::operator=(other);
             Decomposition::operator=(other); 
             _is_feasible = other._is_feasible ;
        }
        return *this;
    }
    
    virtual void invalidate()
    {
        BaseT::invalidate();
        daex::Decomposition::invalidate();
    }

    virtual void printOn(std::ostream & _os) const
    {
		BaseT::printOn(_os);
        _os << ' ';
        Decomposition::printOn(_os);  
    }
    
    /**
     * Reading object
     * @param _is input stream
     */
    virtual void readFrom(std::istream & _is)
    {
       BaseT::readFrom(_is);
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
     
    bool operator< (const BaseT  & _moeo) const
    {
        return BaseT::operator<(_moeo);
    }
   
protected:
   
    bool _is_feasible;
 
};

/**
 * To avoid conflicts between MOEO::operator< and std::vector<double>::operator<
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template <class BaseT >
bool operator<(const Planning< BaseT > & _moeo1, const 
Planning< BaseT > & _moeo2)
{
    return _moeo1.operator<(_moeo2);
}


/**
 * To avoid conflicts between MOEO::operator> and std::vector<double>::operator>
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
/*template <class BaseT >
bool operator>(const Planning< BaseT > & _moeo1, const moeoVector< BaseT > & _moeo2)
{
    return _moeo1.operator>(_moeo2);
}*/


template < class BaseT > 
std::ostream & operator << ( std::ostream& _os, const Planning< BaseT > & _o ) 
{
    _o.printOn(_os);
    return _os;
} 

} // namespace daex

#endif /*PLANNING_H_*/
