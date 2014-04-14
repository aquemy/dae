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




} // namespace daex

#endif // __STRATEGIES_H__
