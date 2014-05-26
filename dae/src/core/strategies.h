#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__

#include <map>
#include <src/yahsp.h>
#include "planningState.h"

namespace daex {


// Strategy class
// Generic functor for strategy. It takes an object and return a objective to send to YAHSP.
// The implementation is a NVI pattern to ensure precondition and post conditions.
// Default implementation is a fixed weighted strategy.
template <class EOT>
class Strategy
{
public:

    Strategy(double _mutRate = 0.1,
            std::vector<double> initRates = std::vector<double>(NB_YAHSP_STRAT,1./NB_YAHSP_STRAT)) :
        mutRate(_mutRate),
        distribution(initRates)
    { 
    }

    virtual ~Strategy()
    {}
    
    Strategy operator=(const Strategy& _o)
    {
        mutRate = _o.mutRate;
        distribution = _o.distribution;
        
        return *this;
    }
    
    double& operator[](Objective obj)
    {
        return distribution[(int)obj];
    }

    Objective operator()(const EOT& o)
    {
        // Préconditions & invariants (serialisation, assertions...)
        current = _choice(o);
        //_update(o, current);
        //_mutation(o, current);
        // Post condition
      
        return current;
    }
    
protected:

    Objective current;
    double mutRate;
    std::vector<double> distribution;
    

private:

    virtual Objective _choice(const EOT& o)
    {
        (void)o;
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
        double pmin = 0.1;
        std::cerr << "Mutation rate : " << mutRate;
        mutRate += rng.normal(0.0, 0.1);
        if(mutRate < 0.05)
            mutRate = 0.05;
        else if(mutRate > 1)
            mutRate = 1;
        double p = rng.uniform(0,1);
        std::cerr << " -> " << mutRate << std::endl;
        if(p < mutRate)   
        {
            std::cerr << "Distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << distribution[i] << " ";
            std::cerr << std::endl;
            unsigned pos = rng.uniform(0,NB_YAHSP_STRAT);
            do
                pos = rng.uniform(0,NB_YAHSP_STRAT);
            while(pos == choice);
            
            // Un seul objectif muté
            //distribution[pos] += rng.normal(0.0, 0.1*NB_YAHSP_STRAT);
            //if(distribution[pos] < 0)
            //    distribution[pos] = pmin;
            // Tous les objectifs mutés
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                distribution[i] += rng.normal(0.0, 0.25*NB_YAHSP_STRAT);
            
            double m = std::min(0., *std::min_element(distribution.begin(), distribution.end()));
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                distribution[i] -= m;
                 
            // Renormalisation
            double sum = 0;
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                sum += distribution[i];
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                distribution[i] /= sum;
            std::cerr << "Nouvelle Distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << distribution[i] << " ";
            std::cerr << std::endl;
        }
        
    }
};

// Initialize the strategy with equiprobability for each strategy
class StrategyInit
{
public:

    StrategyInit(std::string _indicator, bool _effect, std::string _quality, std::string _update, bool _jump) :
        indicator(_indicator),
        effect(_effect),
        quality(_quality),
        update(_update),
        jump(_jump)
    {}
    
    ~StrategyInit()
    {}

    template <class EOT>
    Strategy<EOT> operator()()
    {
        double mutRate = 0.1;
        std::vector<double> distribution(NB_YAHSP_STRAT);
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            distribution[i] = rng.uniform(0,1);
        double sum = 0;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            sum += distribution[i];
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            distribution[i] /= sum;
        
        return Strategy<EOT>(mutRate, distribution);
    }
    
protected :

    std::string indicator;
    bool effect;
    std::string quality;
    std::string update;
    bool jump;
};

} // namespace daex

#endif // __STRATEGIES_H__
