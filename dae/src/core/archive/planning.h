
#ifndef PLANNING_H_
#define PLANNING_H_

 
//#include <moeo>
#include "moeoDaex.h"
#include "planningObjectiveVector.h"

/**
 *  Structure of the genotype for the planning problem: a vector of decomposition, eoDualFitness.
 */
 
class Planning:   public moeoDaex < PlanningObjectiveVector> 

  {
  public:
       /**
     * class name
     */
     
      //Planning():moeoDaex < PlanningObjectiveVector>()
      //{}
     
        
      //virtual ~Planning() {}   
      
     std::string className() const { 
   	 return "Planning";
  	} 
     
      virtual  void printOn(std::ostream & _os) const
      {
         
        moeoDaex < PlanningObjectiveVector> ::printOn(_os);
         
      }  
      
      virtual void readFrom(std::istream & _is){
      
        moeoDaex < PlanningObjectiveVector>::readFrom(_is);
    /*unsigned int sz;
       _is >> sz;
//  */    /*   resize(sz);*/
//       unsigned int i;
//       daex::Decomposition::iterator it = this->begin();
//       for (i = 0; i < sz; ++i)
//         {
//            _is >> *it; 
//            
//            it ++;
//           
//         }
    }
   
 
  };

 
 /*
  std::ostream & operator << ( std::ostream& _os, const Planning& _o ) {
  _o.printOn(_os);
          return _os;
  } ; 
*/





#endif /*PLANNING_H_*/
