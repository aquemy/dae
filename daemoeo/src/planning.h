
#ifndef PLANNING_H_
#define PLANNING_H_

 
//#include <moeo>
#include "moeoDaex.h"
#include "planningObjectiveVector.h"

/**
 *  Structure of the genotype for the planning problem: a vector of decomposition and an objective vector.
 */
 
class Planning:   public moeoDaex < PlanningObjectiveVector> 
  {
  public:
       /**
     * class name
     */
     
     using moeoDaex < PlanningObjectiveVector>:: begin;
     using moeoDaex < PlanningObjectiveVector>:: end;
     using moeoDaex < PlanningObjectiveVector>::resize;
     using moeoDaex < PlanningObjectiveVector>::size;
     
     
     Planning():moeoDaex < PlanningObjectiveVector>(), _is_feasible(false), _indiv_seed(rng.rand())
     {}
     
        
     virtual ~Planning() {}   
      
     std::string className() const { 
   	 return "Planning";
  	} 
  	
  	
     Planning & operator=(const Planning & other){
       if (this != &other) {
             moeoDaex < PlanningObjectiveVector>::operator=(other);
             _is_feasible = other._is_feasible ;
	     _indiv_seed = other._indiv_seed;
        }
        return *this;
    }

    virtual void printOn(std::ostream & _os) const
      {
         
	///if (is_feasible())
	
		moeoDaex < PlanningObjectiveVector> ::printOn(_os);
	//else
	
		///_os<<"UNFEASIBLE ";
        
        
      }	
  
    void setFeasible(bool  b){

	_is_feasible = b;

	}
 
     bool is_feasible() const {
        return _is_feasible;
     }
   
     void setIndivSeed(uint32_t indiv_seed){

	_indiv_seed = indiv_seed;

	}
	
      uint32_t indivSeed(){
	
	return _indiv_seed;
      }
  
  
  private:
   
    bool _is_feasible;
    uint32_t _indiv_seed;
 
  };

 

#endif /*PLANNING_H_*/
