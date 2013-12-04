
#ifndef _eoFeasibleStat_h_
#define _eoFeasibleStat_h_

#include <algorithm>

#include <utils/eoStat.h>

/** Ratio of the number of feasible individuals in the population
 *
 * @ingroup Stats
 */


template< class EOT>
bool isFeasible ( const EOT & sol ) { return sol.is_feasible();}


template<class EOT>
class eoFeasibleStat : public eoStat< EOT, double >
{
public:
    using eoStat<EOT, double>::value;

    eoFeasibleStat( std::string description = "FeasibleRatio(%)" ) : eoStat<EOT,double>( 0.0, description ) {}

    virtual void operator()( const eoPop<EOT> & pop )
    {
#ifndef NDEBUG
        assert( pop.size() > 0 );

        double count = static_cast<double>( std::count_if( pop.begin(), pop.end(), isFeasible<EOT> ) );
        double size = static_cast<double>( pop.size() );
        double ratio = count/size;
        value() = ratio;
#else
        value() = static_cast<double>( std::count_if( pop.begin(), pop.end(), isFeasible<EOT> ) ) / static_cast<double>( pop.size() );
	
#endif
	 value() *=100;
		
    }

 virtual std::string className(void) const { return "eoFeasibleStat"; }
};




template<class EOT>
class eoDaeAverageSizeStat : public eoStat< EOT, double>
{
public:

    using eoStat<EOT, double>::value;

    eoDaeAverageSizeStat( std::string description = "Av.Size" ) :
        eoStat<EOT,double>( 0.0, description ) {} // 0 by default

    virtual void operator()( const eoPop<EOT> & pop )
    {
        size_t pop_size = pop.size();
	size_t indivSize;
	
	std::list<daex::Goal>::const_iterator it;

        std::vector<size_t> sizes;
        sizes.reserve(pop_size);

        for( unsigned int i=0, s1 = pop_size; i<s1; ++i ) {  
                    
	      it =  pop[i].begin();
	     indivSize=0;
	     
	     for (; it != pop[i].end(); ++it)  
		
		    indivSize += (*it).size();
        
	     sizes.push_back(indivSize);                                  
        }

        size_t sum = std::accumulate( sizes.begin(), sizes.end(), 0 );

        value() = static_cast<double>(sum) / static_cast<double>(pop_size);
    }
    

    virtual std::string className(void) const { return "eoDaeAverageSizeStat"; }
};


#endif
