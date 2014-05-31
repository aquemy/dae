#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__

#include <map>
#include <src/yahsp.h>
#include "planningState.h"

namespace daex {

enum StrategyType
{
    Static,
    Greedy,
    AutoAdaptive,
    Adaptive  
};


// Strategy class
// Generic functor for strategy. It takes an object and return a objective to send to YAHSP.
// The implementation is a NVI pattern to ensure precondition and post conditions.
// Default implementation is a fixed weighted strategy.

template <class EOT>
class Strategy
{
public:

    Strategy(std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1)) :
        rates(_rates),
        current((Objective)0)
    {}
    
    virtual ~Strategy()
    {}
    
    Strategy operator=(const Strategy& _o)
    {
        rates = _o.rates;
        
        return *this;
    }
    
    double operator[](Objective obj)
    {
        return rates[(int)obj];
    }
    
    Objective operator()(const EOT& o)
    {
        // Préconditions & invariants (serialisation, assertions...)
        current = _choice(o);
        _update(o, current);
        //_mutation(o, current);
        // Post condition
      
        return current;
    }
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }
    
private:

    virtual Objective _choice(const EOT& o)
    {
        (void)o;
        return (Objective)rng.roulette_wheel(rates);
    }
    
    virtual void _update(const EOT& o, Objective choice) 
    { 
        (void)o; 
        (void)choice;
    }
    
        
protected:

    std::vector<double> rates;
    Objective current;
};

template <class EOT>
class GreedyStrategy : public Strategy<EOT>
{
public:

    GreedyStrategy() :
        Strategy<EOT>()
    {}
    
    virtual ~GreedyStrategy()
    {}
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }

private:

    virtual Objective _choice(const EOT& o)
    {
        (void)o;
        return Objective((int)((Strategy<EOT>::current)+1) % NB_YAHSP_STRAT);
    }
                
};


template <class EOT>
class AutoAdaptiveStrategy : public Strategy<EOT>
{
public:

    AutoAdaptiveStrategy(std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1)) :
        Strategy<EOT>(_rates)
    { Strategy<EOT>::current = (Objective)rng.roulette_wheel(_rates); }
    
    virtual ~AutoAdaptiveStrategy()
    {}
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }

private:

    virtual Objective _choice(const EOT& o)
    {
        (void)o;
        return Strategy<EOT>::current;
    }
            
};


template <class EOT>
class AdaptiveStrategy : public Strategy<EOT>
{
public:

    AdaptiveStrategy(std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1)) :
        Strategy<EOT>(_rates)
    {}
    
    virtual ~AdaptiveStrategy()
    {}
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }

private:

          
};

template <class EOT>
std::ostream& operator << (std::ostream& os, const Strategy<EOT>& s)
{
    return s.printOn(os);
}

template <class EOT>
std::ostream& operator << (std::ostream& os, const GreedyStrategy<EOT>& s)
{
    return s.printOn(os);
}

template <class EOT>
std::ostream& operator << (std::ostream& os, const AdaptiveStrategy<EOT>& s)
{
    return s.printOn(os);
}

template <class EOT>
std::ostream& operator << (std::ostream& os, const AutoAdaptiveStrategy<EOT>& s)
{
    return s.printOn(os);
}

template <class EOT>
class StrategyInit
{
public:

    StrategyInit(StrategyType _stratType, std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1)) :
        stratType(_stratType),
        rates(_rates)
    {}

    Strategy<EOT>* operator()()
    {
        if(stratType == Static) {
            return new Strategy<EOT>(rates); }
        else if(stratType == Greedy) {
            return new GreedyStrategy<EOT>(); }
        else if(stratType == Adaptive) {
            return new AdaptiveStrategy<EOT>(rates); }
        else if(stratType == AutoAdaptive){
            return new AutoAdaptiveStrategy<EOT>(rates); }
    }
    
protected:

    StrategyType stratType;
    std::vector<double> rates;
    
};

/*
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
/*        double pmin = 0.1;
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
};*/

} // namespace daex

#endif // __STRATEGIES_H__
