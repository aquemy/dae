#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__

#include <map>

namespace daex {
#define NB_YAHSP_STRAT 4
enum Objective 
{ 
    length, 
    cost, 
    makespan_max, 
    makespan_add 
};

// Strategy class
// Generic functor for strategy. It takes an object and return a objective to send to YAHSP.
// The implementation is a NVI pattern to ensure precondition and post conditions.
// Default implementation is a fixed weighted strategy.
template <class EOT>
class Strategy
{
public:

    Strategy(double _mutRate = 0.5) : mutRate(_mutRate), nbAppel(0)
    {}

    Strategy(std::vector<double> initRates, double _mutRate = 0.5) : 
        distribution(initRates),
        mutRate(_mutRate),
        nbAppel(0)
    {}
    
    Strategy<EOT> operator=(const Strategy<EOT>& _o)
    {
        distribution = _o.distribution;
        mutRate = _o.mutRate;
        nbAppel = _o.nbAppel;
        return *this;
    }
    
    double& operator[](Objective obj)
    {
        return distribution[(int)obj];
    }

    Objective operator()(const EOT& o)
    {
        // Préconditions & invariants (serialisation, assertions...)

        nbAppel++;
        Objective choice = _choice(o);
        _update(o, choice);
        _mutation(o, choice);
        // Post condition
        //std::cerr << nbAppel << std::endl;
      
        return choice;
    }
    
protected:

    std::vector<double> distribution;
    double mutRate;
    unsigned nbAppel;

private:

    virtual Objective _choice(const EOT& o)
    {
        return (Objective)rng.roulette_wheel(distribution);
    };
    
    virtual void _update(const EOT& o, Objective choice) 
    { 
        (void)o; 
        (void)choice;
    }
    
    virtual void _mutation(const EOT& o, Objective choice)
    {
        (void)o;
        //////////////////////////////////////////////////////////
        // Static mutation
        //////////////////////////////////////////////////////////
        /*double p = rng.uniform(0,1);
        if(p < mutRate)
        {
            //
            std::cerr << "Avant : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << distribution[i] << " ";
            //
            double avrg = 0;
            double stddev = 0;
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                avrg += distribution[i];
                stddev += distribution[i]*distribution[i];
            }
            stddev = (1 / (NB_YAHSP_STRAT - 1))*(stddev - avrg*avrg);
            unsigned pos = rng.uniform(0,NB_YAHSP_STRAT);
                distribution[pos] += rng.normal(avrg, stddev);
            
            std::cerr << " | Après : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << distribution[i] << " ";
            std::cerr << std::endl;    
                
           // Update the mutation rate
        }
        mutRate = mutRate*0.9;
        std::cerr << mutRate << std::endl;*/
        //////////////////////////////////////////////////////////
        // End Static mutation
        ////////////////////////////////////////////////////////// 
        
        //////////////////////////////////////////////////////////
        // Self-adaptive mutation
        //////////////////////////////////////////////////////////
        mutRate += rng.normal(0.1, 0.1);
        if(mutRate < 0.01)
            mutRate = 0.01;
        else if(mutRate > 1)
            mutRate = 1;
        double p = rng.uniform(0,1);

        if(p < mutRate)   
        {
            unsigned pos = rng.uniform(0,NB_YAHSP_STRAT);
            do
                pos = rng.uniform(0,NB_YAHSP_STRAT);
            while(pos == choice);
            distribution[pos] += 1;

        }
        
    }
};

class StrategyInit
{
public:

    StrategyInit(std::vector<std::pair<double,double> > initRates) : rates(initRates)
    {}

    std::vector<double> operator()()
    {

        std::vector<double> distrib(NB_YAHSP_STRAT);
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
        {
            if(rates[i].first == rates[i].second)
                distrib[i] = rates[i].first;
            else
                distrib[i] = rng.uniform(rates[i].first,rates[i].second);
        }

        return distrib;
    }
    
protected:

    std::vector<std::pair<double,double> > rates;
    
};


} // namespace daex

#endif // __STRATEGIES_H__
