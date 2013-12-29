
//#include "planning.h"

 Planning::Planning():moeoDaex < PlanningObjectiveVector>()
    {}
   
 Planning::~Planning(){}
 
  Planning::Planning & operator=(const Planning & other){
       if (this != &other) {
             moeoDaex < PlanningObjectiveVector>::operator=(other);
             _is_feasible = other._is_feasible ;
        }
        return *this;
    }

  	
  
    void setFeasible(bool  b){

	_is_feasible = b;

	}
 
    inline bool is_feasible() const {
        return _is_feasible;
     }
   
 
 
 
 
 std::string Planning::className() const
  {
    return "Planning";
  }
  
  void Planning::printOn(std::ostream & _os) const{
        
       moeoDaex < PlanningObjectiveVector> ::printOn(_os);
        
   } 
      
   void Planning::readFrom(std::istream & _is) 
      {
       MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::readFrom(_is);
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
