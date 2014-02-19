
#ifndef moDaex_H_
#define moDaex_H_

//#include <moeo>
#include <iterator>
#include <list>
#include <core/MOEO.h>
#include <daex.h>
/**
 * Base class for fixed length chromosomes, just derives from MOEO and std::vector and redirects the smaller than operator to MOEO (objective vector based comparison).
 * GeneType must have the following methods: void ctor (needed for the std::vector<>), copy ctor.
 */
//template < class MOEOObjectiveVector, class MOEOFitness=double, class MOEODiversity=double > 
template <class Fit = double>
class moDaex :   public EO<Fit>,    public daex::Decomposition
  
  {
  public:
     
    typedef Fit Fitness;
      
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
    moDaex() : daex::Decomposition()
    {}
     
    virtual ~moDaex(){ }
     
     
     moDaex & operator=(const moDaex & other){
       if (this != &other) {
                EO<Fit>::fitness(other.fitness());
                Decomposition::operator=(other); 
             
        }
        return *this;
    }


     virtual  void invalidate(){
           
     EO<Fit>::invalidate();
      
     daex::Decomposition::invalidate();
       
     }
 
     
    /**
     * We can't have a Ctor from a std::vector as it would create ambiguity  with the copy Ctor.
     * @param _v a vector of GeneType
     */
    void value(const moDaex<Fit>  & _moeo)
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
    bool operator< (const moDaex<Fit>  & _moeo) const
      {
        return EO<Fit>::operator<(_moeo);
      }


    /**
     * Writing object
     * @param _os output stream
     */
      virtual void printOn(std::ostream & _os) const
      {
         
	    EO <Fit>::printOn(_os);
        _os << ' ';
        Decomposition::printOn(_os);  
        
      }
      
    
    /**
     * Reading object
     * @param _is input stream
     */
    virtual void readFrom(std::istream & _is)
    {
       EO <Fit>::readFrom(_is);
       Decomposition::readFrom(_is);


     }

  };


/**
 * To avoid conflicts between MOEO::operator< and std::vector<double>::operator<
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class Fit>
bool operator<(const moDaex< Fit> & _moeo1, const moDaex< Fit > & _moeo2)
{
  return _moeo1.operator<(_moeo2);
}


/**
 * To avoid conflicts between MOEO::operator> and std::vector<double>::operator>
 * @param _moeo1 the first object to compare
 * @param _moeo2 the second object to compare
 */
template < class Fit >
bool operator>(const Fit & _moeo1, const Fit & _moeo2)
{
  return _moeo1.operator>(_moeo2);
}


template < class Fit > 
std::ostream & operator << ( std::ostream& _os, const moDaex< Fit> & _o ) 
{
  _o.printOn(_os);
  
  return _os;
} 



#endif /*moDaex_H_*/
