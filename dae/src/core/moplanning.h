
#ifndef PlanningMO_H_
#define PlanningMO_H_

 
//#include <moeo>
#include "moDaex.h"
// #include "moeoDaex.h"
//#include "double.h"

/**
 *  Structure of the genotype for the PlanningMO problem: a vector of decomposition and an objective vector.
 */

//class PlanningMO:   public moeoDaex < double> 
class PlanningMO:   public moDaex < double> 
  {
  public:
       /**
     * class name
     */
     
     using moDaex < double>:: begin;
     using moDaex < double>:: end;
     using moDaex < double>::resize;
     using moDaex < double>::size;
     
     
     PlanningMO():moDaex < double>(), _is_feasible(false)
     {}
     
        
     virtual ~PlanningMO() {}   
      
     std::string className() const { 
   	 return "PlanningMO";
  	} 
  	
  	
     PlanningMO & operator=(const PlanningMO & other){
       if (this != &other) {
             moDaex < double>::operator=(other);
             _is_feasible = other._is_feasible ;
        }
        return *this;
    }

    virtual void printOn(std::ostream & _os) const
      {
         
	///if (is_feasible())
	
		moDaex < double> ::printOn(_os);
	//else
	
		///_os<<"UNFEASIBLE ";
        
        
      }	
  
    void setFeasible(bool  b){

	_is_feasible = b;

	}
 
     bool is_feasible() const {
        return _is_feasible;
     }
   
  
  
  private:
   
    bool _is_feasible;
 
  };

 

#endif /*PlanningMO_H_*/
