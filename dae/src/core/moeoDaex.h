
#ifndef MOEODAEX_H_
#define MOEODAEX_H_

//#include <moeo>
#include <iterator>
#include <list>
#include <core/MOEO.h>
#include <daex.h>
/**
 * Base class for fixed length chromosomes, just derives from MOEO and std::vector and redirects the smaller than operator to MOEO (objective vector based comparison).
 * GeneType must have the following methods: void ctor (needed for the std::vector<>), copy ctor.
 */
template < class MOEOObjectiveVector, class MOEOFitness=double, class MOEODiversity=double > 

class moeoDaex :   public MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >,    public daex::Decomposition
  
  {
  public:
     
    typedef MOEOFitness Fitness;
      
  //typedef daex::Decomposition::Fitness Fitness;
  
 
     using daex::Decomposition :: begin;
     using daex::Decomposition :: end;
     using daex::Decomposition :: resize;
     using daex::Decomposition :: size;

  
    /**
     * Default ctor.
     * @param _size Length of vector (default is 0)
     * @param _value Initial value of all elements (default is default value of type GeneType)
     */
    moeoDaex() :
        MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >(), daex::Decomposition()
    {}
     
     virtual ~moeoDaex(){ }
     
     
     moeoDaex & operator=(const moeoDaex & other){
       if (this != &other) {
               MOEO< MOEOObjectiveVector, MOEOFitness, MOEODiversity >::operator=(other);
                Decomposition::operator=(other); 
             
        }
        return *this;
    }


     virtual  void invalidate(){
           
     MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity > ::invalidate();
      
     daex::Decomposition::invalidate();
       
     }
 /*
 	bool invalid() const {
        MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::invalid();
        
//       daex::Decomposition::invalid();
      }
     
     void fitness(const Fitness & _fitnessValue) {
      
      MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::fitness(_fitnessValue); 
      
	//       daex::Decomposition::fitness(std::make_pair(_fitnessValue, daex::Decomposition::fitness().is_feasible() ));
    }
      
      
      Fitness fitness() const {
      return MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::fitness();
    }



      bool invalidFitness() const {
             
      MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::invalidFitness();
      
        //daex::Decomposition::fitness().invalidFitness();
      }

       */
      
      
    /**
     * We can't have a Ctor from a std::vector as it would create ambiguity  with the copy Ctor.
     * @param _v a vector of GeneType
     */
    void value(const moeoDaex<MOEOObjectiveVector,MOEOFitness, MOEODiversity>  & _moeo)
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



    /**
     * To avoid conflicts between MOEO::operator< and std::vector<GeneType>::operator<
     * @param _moeo the object to compare with
     */
    bool operator< (const moeoDaex<MOEOObjectiveVector,MOEOFitness, MOEODiversity>  & _moeo) const
      {
        return MOEO < MOEOObjectiveVector, MOEOFitness, MOEODiversity >::operator<(_moeo);
      }


    /**
     * Writing object
     * @param _os output stream
     */
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

  };


/**
 * To avoid conflicts between MOEO::operator< and std::vector<double>::operator<
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity>
bool operator<(const moeoDaex< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _moeo1, const 

moeoDaex< MOEOObjectiveVector, MOEOFitness, MOEODiversity > & _moeo2)
{
  return _moeo1.operator<(_moeo2);
}


/**
 * To avoid conflicts between MOEO::operator> and std::vector<double>::operator>
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity >
bool operator>(const moeoDaex< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _moeo1, const moeoVector< MOEOObjectiveVector, MOEOFitness, MOEODiversity > & _moeo2)
{
  return _moeo1.operator>(_moeo2);
}


template < class MOEOObjectiveVector, class MOEOFitness, class MOEODiversity > 
std::ostream & operator << ( std::ostream& _os, const moeoDaex< MOEOObjectiveVector, MOEOFitness, MOEODiversity> & _o ) 
{
  _o.printOn(_os);
  
  return _os;
} 



#endif /*MOEODAEX_H_*/
