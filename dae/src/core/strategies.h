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

    Strategy()
    {}

    Strategy(std::vector<double> initRates) : distribution(initRates)
    {}
    
    Strategy<EOT> operator=(const Strategy<EOT>& _o)
    {
        distribution = _o.distribution;
        return *this;
    }
    
    Strategy<EOT> operator=(std::vector<double> rates)
    {
        distribution = rates;
        return *this;
    }
    
    double& operator[](Objective obj)
    {
        return distribution[(int)obj];
    }

    Objective operator()(const EOT& o)
    {
        // Préconditions & invariants (serialisation, assertions...)
        Objective choice = _choice(o);
        _update(o, choice);
        // Post condition
        return choice;
    }
    
protected:

    std::vector<double> distribution;

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
};

class StrategyInit
{
public:

    virtual std::vector<double> operator()() = 0;

};

class StrategyInitStatic : public StrategyInit
{
public:
    
    StrategyInitStatic(std::vector<double> initRates) : rates(initRates)
    {}

    std::vector<double> operator()()
    {
        return rates;
    }
    
protected:

    std::vector<double> rates;
    
};

class StrategyRngStatic : public StrategyInit
{
public:
    
    StrategyRngStatic(double _a, double _b) : a(_a), b(_b) 
    {}

    std::vector<double> operator()()
    {
        std::vector<double> rates(NB_YAHSP_STRAT);
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            rates[i] = rng.uniform(a,b);
        return rates;
    }
    
protected:

    double a;
    double b;
    
};

class StrategyRngOne : public StrategyInit
{
public:
    
    StrategyRngOne(std::vector<double> initRates = std::vector<double>(NB_YAHSP_STRAT,1)) : rates(initRates)
    {}
    

    std::vector<double> operator()()
    {
        std::vector<double> distrib(NB_YAHSP_STRAT,0);
        unsigned pos = rng.roulette_wheel(rates);
        distrib[pos] = 1;
        return distrib;
    }
    
protected:

    std::vector<double> rates;
    
};

} // namespace daex

#endif // __STRATEGIES_H__
