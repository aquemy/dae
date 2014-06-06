#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__

#include <map>
#include <src/yahsp.h>
#include "planningState.h"
#include "planningObjectiveVector.h"
#include "strategyIndicators.h"

namespace daex {

template <class T>
class Planning;
typedef Planning<MOEO<PlanningObjectiveVector, double, double> > IndiMOEO;

enum StrategyType
{
    Static,
    Greedy,
    AutoAdaptive,
    Adaptive  
};

enum StrategyLevel
{
    Population,
    Individual,
    Gene
};


// Strategy class
// Generic functor for strategy. It takes an object and return a objective to send to YAHSP.
// The implementation is a NVI pattern to ensure precondition and post conditions.
// Default implementation is a fixed weighted strategy.

template <class EOT>
class Strategy
{
public:

    Strategy(std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1), double _mutRate = 0.05) :
        rates(_rates),
        current((Objective)0),
        mutRate(_mutRate)
    {}
    
    Strategy(const Strategy& _o)
    {
        *this = _o;
    }
    
    virtual Strategy<EOT>* clone()
    {
        return new Strategy<EOT>(rates);
    }
    
    virtual ~Strategy()
    {}
    
    Strategy operator=(const Strategy& _o)
    {
        rates = _o.rates;
        mutRate = _o.mutRate;
        
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
        // Post condition
      
        return current;
    }
    
    virtual void update(double indicator) 
    { 
        (void)indicator; 
    }
    
    virtual void mutation() 
    { 
        _mutation();
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
    
    
    
    virtual void _mutation() 
    { }
        
protected:

    std::vector<double> rates;
    Objective current;
    double mutRate;
    
};

template <class EOT>
class GreedyStrategy : public Strategy<EOT>
{
public:

    GreedyStrategy() :
        Strategy<EOT>()
    {}
    
    virtual GreedyStrategy<EOT>* clone()
    {
        return new GreedyStrategy<EOT>();
    }
    
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
    { 
        // Randomly choose an objective according to user defined rates (may be a hint).
        Strategy<EOT>::current = (Objective)rng.roulette_wheel(_rates); 
        
        // Reset rates (and we use the Static operator () to return an objective)
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            if(i == (unsigned)Strategy<EOT>::current)
                Strategy<EOT>::rates[i] = 1;
            else
                Strategy<EOT>::rates[i] = 0;
    }
    
    virtual AutoAdaptiveStrategy<EOT>* clone()
    {
        AutoAdaptiveStrategy<EOT>* p = new AutoAdaptiveStrategy<EOT>(Strategy<EOT>::rates);
        p->Strategy<EOT>::current = Strategy<EOT>::current;
        return p;
    }
    
    virtual ~AutoAdaptiveStrategy()
    {}
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }

private:

    virtual void _mutation() // TODO : put the rate in the interface
    { 
        // Static mutation for SelfAdaptive mutation
        double r = rng.uniform(0,1);
        if(r < Strategy<EOT>::mutRate)
        {
            unsigned pos;
            do {
                pos = rng.uniform(0,NB_YAHSP_STRAT);
            } while(pos != Strategy<EOT>::current);
            #ifndef NDEBUG
            eo::log << eo::xdebug << "strategy mutation : " 
                    << Strategy<EOT>::current << " to " << pos << std::endl;
            #endif 
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            if(i == pos)
                Strategy<EOT>::rates[i] = 1;
            else
                Strategy<EOT>::rates[i] = 0;
        }
    }

protected:
   
    
            
};

template <class EOT>
class AdaptiveStrategy : public Strategy<EOT>
{
public:

    AdaptiveStrategy(std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1./NB_YAHSP_STRAT),
             int updateRate = 10,
             bool _efficiencyEstimation = false,
             double _pmin = 0.05,
             double _delta = 0.15, 
             double _epsilon = 1) :
        Strategy<EOT>(_rates),
        nbChoices(std::vector<int>(NB_YAHSP_STRAT,0)),
        positiveChoices(std::vector<int>(NB_YAHSP_STRAT,0)),
        nbAppel(0),
        quality(std::vector<double>(NB_YAHSP_STRAT,0)),
        sumRewards(std::vector<double>(NB_YAHSP_STRAT,0)),
        indicatorsSerie(std::vector<std::vector<double> >(NB_YAHSP_STRAT)),
        cycleChoices(std::vector<int>(NB_YAHSP_STRAT,0)),
        updateDistribRate(updateRate),
        efficiencyEstimation(_efficiencyEstimation),
        pmin(_pmin),
        averageDistribQuality(0),
        M(0),
        maxM(0),
        delta(_delta),
        epsilon(_epsilon),
        it(0)
    { Strategy<EOT>::rates = std::vector<double>(NB_YAHSP_STRAT,1./NB_YAHSP_STRAT); }
    
    AdaptiveStrategy(const AdaptiveStrategy& _o)
    {
        *this = _o;
    }
    
    AdaptiveStrategy operator=(const AdaptiveStrategy& _o)
    {
        Strategy<EOT>::rates = _o.rates;
        Strategy<EOT>::mutRate = _o.mutRate;
        
        nbChoices = _o.nbChoices;
        positiveChoices = _o.positiveChoices;
        nbAppel = _o.nbAppel;
        quality = _o.quality,
        sumRewards = _o.sumRewards;
        indicatorsSerie = _o.indicatorsSerie;
        cycleChoices = _o.cycleChoices;
        updateDistribRate = _o.updateDistribRate;
        
        efficiencyEstimation = _o.efficiencyEstimation;
    
        pmin = _o.pmin;
        
        averageDistribQuality = _o.averageDistribQuality;
        M = _o.M;
        maxM = _o.maxM;
        delta = _o.delta;
        epsilon = _o.epsilon;
        it = _o.it;
        
        return *this;
    }
        
    
    virtual AdaptiveStrategy<EOT>* clone()
    {
        return new AdaptiveStrategy<EOT>(
            Strategy<EOT>::rates, 
            updateDistribRate,
            efficiencyEstimation,
            pmin,
            delta,
            epsilon);
    }
    
    virtual ~AdaptiveStrategy()
    {}
    
    virtual void update(double indicator)
    {
        #ifndef NDEBUG
        eo::log << eo::xdebug << "update adaptive strategy" << std::endl;
        #endif
        
        indicatorsSerie[Strategy<EOT>::current].push_back(indicator);
        cycleChoices[Strategy<EOT>::current]++;
        nbChoices[Strategy<EOT>::current]++;
        it++;
        nbAppel++;
        
        /*std::cerr << "Update strategy n°" << nbAppel << " ( " << it << ")" << std::endl;
        std::cerr << "- Update information : " << std::endl;
        std::cerr << ":::: Indicator : " << indicator << std::endl;
        std::cerr << ":::: Objective : " << Strategy<EOT>::current << std::endl;
        std::cerr << ":::: Indicator Serie : " << std::endl;*/
        /*for(unsigned j = 0; j < indicatorsSerie.size(); j++)
        {
            for(unsigned i = 0; i < indicatorsSerie[j].size(); i++)
                std::cerr << indicatorsSerie[j][i] << " -> ";
            std::cerr << std::endl;
        }*/
        /*if(indicator > 0) // TODO : Comment définir un choix positif pour l'estimation de l'efficacité ?
        {
            positiveChoices[Strategy<EOT>::current]++;
            
        }*/
        // Adds the current indicator and increments the choice and iteration
        
        
        if(it >= updateDistribRate)
        {
            it = 0;
            /*std::cerr << "Efficiency : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr  << efficiency(Objective(i), nbChoices, positiveChoices) << " ";
            std::cerr << std::endl;
            std::cerr << "NbChoices : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << nbChoices[i] << " ";
            std::cerr << std::endl;
            std::cerr << "CycleChoices : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                std::cerr << cycleChoices[i] << " ";
            std::cerr << std::endl;
            std::cerr << "- Quality assessment : " << std::endl;*/
            
            averageQuality(quality, indicatorsSerie, cycleChoices, nbChoices, positiveChoices);
            
            
            // Exponential recency-weighted average
            //quality[current] = indicator + 0.7*(sumRewards[current] - indicator);
            //sumRewards[current] += indicator;
            
            // Sum
            //quality[current] += indicator;
            
            // Moyenne
            //quality[Strategy<EOT>::current] = ((nbChoices[Strategy<EOT>::current]-1)*quality[Strategy<EOT>::current]+indicator)/nbChoices[Strategy<EOT>::current];     
              
            // Extreme value
            //quality[current] = std::max(quality[current], indicator);
            
            //std::cerr << "- Select new parameters : " << std::endl;
            adaptivePursuit(quality, Strategy<EOT>::rates);
            //probabilityMatching(quality, Strategy<EOT>::rates);
            
            // Clear information
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                indicatorsSerie[i].clear();
                cycleChoices[i] = 0;
            }
            
            
            //std::cerr << "- Jump detection : " << std::endl;
            if(jump(quality))
            {
                //std::cerr << "Jump detected ! Reset strategy." << std::endl;
                for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                {
                    nbChoices[i] = 0;
                    positiveChoices[i] = 0;
                    sumRewards[i] = 0;
                    quality[i] = 0;
                    // Doit-on réinitialiser la distribution ? À priori oui.
                    Strategy<EOT>::rates[i] = 1./NB_YAHSP_STRAT;
                }
    
            }
        }

    }
    
    virtual std::ostream& printOn(std::ostream& os) const
    {
        return os;
    }
    
    double efficiency(Objective obj, const std::vector<int>& nbChoices, const std::vector<int>& positiveChoices)
    {
        //std::cerr << "( p : " << positiveChoice[obj] << " | n : " << nbChoices[obj] << ")"; 
        if(!efficiencyEstimation or nbChoices[obj] == 0)
            return 1;
        return ((double) positiveChoices[obj]) / nbChoices[obj];
    }
    
    void averageQuality(std::vector<double>& quality, 
                    const std::vector<std::vector<double> >& indicatorsSerie,
                    const std::vector<int>& cycleChoices, 
                    const std::vector<int>& nbChoices,
                    const std::vector<int>& positiveChoices
                    )
    {
        //std::cerr << "- Average quality assessment strategy" << std::endl;
         
        
        //std::cerr << "Quality : ";
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
        {
            //std::cerr << quality[i] << " -> ";
            quality[i] = 0;
            
            // If the objective never has been picked, we assume it does not participate to the quality
            if(cycleChoices[i] != 0) 
            {
                for(unsigned j = 0; j < indicatorsSerie[i].size(); j++)
                {
                    //std::cerr << "Quality " << quality[i] << " + " << indicatorsSerie[i][j] << std::endl;
                    quality[i] += indicatorsSerie[i][j];
                }
                quality[i] /= cycleChoices[i]; // Average quality
                quality[i] *= efficiency(Objective(i), nbChoices, positiveChoices); // Ponderate by efficiency   
            }
            
            //std::cerr << quality[i] << " | ";
        }
        //std::cerr << std::endl;
    }
    
    
    void extremeQuality(std::vector<double>& quality, 
                    const std::vector<std::vector<double> >& indicatorsSerie,
                    const std::vector<int>& cycleChoices, 
                    const std::vector<int>& nbChoices,
                    const std::vector<int>& positiveChoices
                    )
    {
        //std::cerr << "Quality : ";
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
        {
            //std::cerr << quality[i] << " -> ";
            quality[i] = 0;
            
            // If the objective never has been picked, we assume it does not participate to the quality
            if(cycleChoices[i] != 0 && indicatorsSerie[i].size() > 0) 
            {
                quality[i] = indicatorsSerie[i][0];
                for(unsigned j = 0; j < indicatorsSerie[i].size(); j++)
                {
                    quality[i] = std::max(indicatorsSerie[i][j], quality[i]);
                }
                //std::cerr << "Quality : " << quality[i] << " ";
                quality[i] *= efficiency(Objective(i), nbChoices, positiveChoices); // Ponderate by efficiency
                    
            }
            
            std::cerr << quality[i] << " | ";
        }
        std::cerr << std::endl;
    }

    void probabilityMatching(const std::vector<double>& quality, std::vector<double>& distribution)
    {
        //std::cerr << "- Probability matching selection strategy" << std::endl;
        double min = -std::min(0.,*std::min_element(quality.begin(), quality.end()));
            
        double sum = 0;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            sum += quality[i];
        //std::cerr << "sum : " << sum << std::endl;
        //if(sum > 0)
        {
            //std::cerr << "New distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                //std::cerr << distribution[i] << "  ->  ";
                distribution[i] = pmin + ((1-NB_YAHSP_STRAT*pmin)*(quality[i])) / sum;
                //std::cerr << distribution[i] << "  |  ";
            }
            //std::cerr << std::endl;
        }
    }
    
    void adaptivePursuit(const std::vector<double>& quality, std::vector<double>& distribution)
    {
        //std::cerr << "- Adaptive Pursuit selection strategy" << std::endl;
        double beta = 0.5;
        double pmax = 1 - (NB_YAHSP_STRAT - 1)*pmin;
        unsigned o = std::distance(quality.begin(), std::max_element(quality.begin(), quality.end()));    
        //std::cerr << "Best : " << o << " | " << pmin << " - " << pmax << std::endl;
            //std::cerr << "New distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                //std::cerr << distribution[i] << "  ->  ";
                if(i == o)
                    distribution[i] = distribution[i] + beta*(pmax - distribution[i]);
                else
                    distribution[i] = distribution[i] + beta*(pmin - distribution[i]);
                //std::cerr << distribution[i] << "  |  ";
            }
            //std::cerr << std::endl;
    }

    bool jump(std::vector<double>& quality)
    {
        //std::cerr << "- Page Hinkley jump detection" << std::endl;
        it++;
        // Quality of the current distribution : sum of all qualities
        double qualityDistribution = 0;
        double min = -std::min(0.,*std::min_element(quality.begin(), quality.end()));
        for(unsigned i = 0; i < quality.size(); i++)
            qualityDistribution += (quality[i] + min);

        M += (qualityDistribution - averageDistribQuality + (delta/2));
        maxM = std::max(M,maxM);
        averageDistribQuality = ((it-1)*averageDistribQuality + M) / it;
        double PHT = fabs(maxM - M);
        
        // TODO : logger en debug
        /*    std::cerr << "##### Page-Hinkley Test #####" << std::endl;
            std::cerr << "Cycle : " << nbAppel / it << std::endl;
            std::cerr << "Average Distribution Quality : " << averageDistribQuality << std::endl;
            std::cerr << "Current M : " << M << std::endl;
            std::cerr << "Max M : " << maxM << std::endl;
            std::cerr << "PHT : " << PHT << std::endl;
            if(PHT > epsilon)
                std::cerr << "Changement détecté !" << std::endl;
            else
                std::cerr << "Aucun changement." << std::endl;
            std::cerr << "#############################" << std::endl;*/
        
        if(PHT > epsilon)
        {
            averageDistribQuality = 0;
            maxM = 0;
            it = 0;
            return true;
        }
        else
            return false;
    }

    bool dummyJump(std::vector<double>& quality)
    {
        return false;
    }

    std::vector<int> nbChoices;
    std::vector<int> positiveChoices;
    unsigned nbAppel;
    std::vector<double> quality;
    std::vector<double> sumRewards;
    std::vector<std::vector<double> > indicatorsSerie;
    std::vector<int> cycleChoices;

    unsigned updateDistribRate;
    
    bool efficiencyEstimation;
    
    double pmin;
    
    double averageDistribQuality;
    double M;
    double maxM;
    double delta;                   ///< Tolerance factor
    double epsilon;                 ///< Threshold
    double it;                      ///< Iterations

private:

          
};

template <class EOT>
std::ostream& operator << (std::ostream& os, const Strategy<EOT>& s)
{
    return s.printOn(os);
}

class StrategyInit
{
public:

    StrategyInit(StrategyType _stratType, std::vector<double> _rates = std::vector<double>(NB_YAHSP_STRAT,1)) :
        stratType(_stratType),
        rates(_rates)
    {}

    template <class EOT>
    Strategy<EOT>* operator()()
    {
        if(stratType == Greedy) {
            return new GreedyStrategy<EOT>(); }
        else if(stratType == Adaptive) {
            return new AdaptiveStrategy<EOT>(rates); }
        else if(stratType == AutoAdaptive){
            return new AutoAdaptiveStrategy<EOT>(rates); }
        else
            return new Strategy<EOT>(rates);
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
