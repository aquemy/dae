#ifndef __STRATEGIES_H__
#define __STRATEGIES_H__

#include <map>
#include "planningState.h"

namespace daex {
#define NB_YAHSP_STRAT 4
enum Objective 
{ 
    makespan_add,
    makespan_max, 
    cost, 
    length,
};




// Strategy class
// Generic functor for strategy. It takes an object and return a objective to send to YAHSP.
// The implementation is a NVI pattern to ensure precondition and post conditions.
// Default implementation is a fixed weighted strategy.
template <class EOT>
class Strategy
{
public:

    Strategy(int updateRate = 1,
             double _mutRate = 0.5,
             bool _efficiencyEstimation = false,
             double _pmin = 0.05,
             double _delta = 0.15, 
             double _epsilon = 1,
             std::vector<double> initRates = std::vector<double>(NB_YAHSP_STRAT,1./NB_YAHSP_STRAT)) :
        distribution(initRates),
        nbChoices(std::vector<int>(NB_YAHSP_STRAT,0)),
        positiveChoices(std::vector<int>(NB_YAHSP_STRAT,0)),
        mutRate(_mutRate), 
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
        it(1)
    { 
    }

    virtual ~Strategy()
    {}
    
    Strategy operator=(const Strategy& _o)
    {
        distribution = _o.distribution;
        nbChoices = _o.nbChoices;
        positiveChoices = _o.positiveChoices;
        mutRate = _o.mutRate;
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
    
    double& operator[](Objective obj)
    {
        return distribution[(int)obj];
    }

    Objective operator()(const EOT& o)
    {
        // Préconditions & invariants (serialisation, assertions...)
        nbAppel++;
        current = _choice(o);
        _update(o, current);
        //_mutation(o, current);
        // Post condition
        std::cerr << "Appel n°" << nbAppel << std::endl;
        nbChoices[current]++;
        cycleChoices[current]++;
      
        return current;
    }
    
     void update(double indicator)
    {
        std::cerr << "Update strategy n°" << nbAppel << std::endl;
        std::cerr << "- Update information : " << std::endl;
        std::cerr << ":::: Indicator : " << indicator << std::endl;
        std::cerr << ":::: Objective : " << current << std::endl;
        
        for(unsigned j = 0; j < indicatorsSerie.size(); j++)
        {
            for(unsigned i = 0; i < indicatorsSerie[j].size(); i++)
                std::cerr << indicatorsSerie[j][i] << " -> ";
            std::cerr << std::endl;
        }
        std::cerr << std::endl;
        /*if(indicator > 0)
        {
            positiveChoices[current]++;
            indicatorsSerie[current].push_back(indicator);
        }*/
        
        {
            std::cerr << "- Quality assessment : ";
            
            // Exponential recency-weighted average
            //quality[current] = indicator + 0.7*(sumRewards[current] - indicator);
            //sumRewards[current] += indicator;
            
            // Sum
            //quality[current] += indicator;
            
            // Moyenne
            quality[current] = ((nbChoices[current]-1)*quality[current]+indicator)/nbChoices[current];     
              
            // Extreme value
            //quality[current] = std::max(quality[current], indicator);
            
            
            
            // Clear information
            /*for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                indicatorsSerie[i].clear();
                cycleChoices[i] = 0;
            }*/
            std::cerr << "- Select new parameters : ";
            adaptivePursuit(quality, distribution);
            //probabilityMatching(quality, distribution);
            
            std::cerr << "Jump detection : ";
            if(jump(quality))
            {
                std::cerr << "Jump detected ! Reset strategy." << std::endl;
                for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                {
                    nbChoices[i] = 0;
                    positiveChoices[i] = 0;
                    sumRewards[i] = 0;
                    quality[i] = 0;
                    // Doit-on réinitialiser la distribution ? À priori oui.
                    distribution[i] = 1./NB_YAHSP_STRAT;
                }
    
            }
        }

    }
    
    
    /*void update(double indicator)
    {
        std::cerr << "Update strategy n°" << nbAppel << std::endl;
        std::cerr << "- Update information : " << std::endl;
        std::cerr << ":::: Indicator : " << indicator << std::endl;
        std::cerr << ":::: Objective : " << current << std::endl;
        
        for(unsigned j = 0; j < indicatorsSerie.size(); j++)
        {
            for(unsigned i = 0; i < indicatorsSerie[j].size(); i++)
                std::cerr << indicatorsSerie[j][i] << " -> ";
            std::cerr << std::endl;
        }
        std::cerr << std::endl;
        if(indicator > 0)
        {
            positiveChoices[current]++;
            indicatorsSerie[current].push_back(indicator);
        }
        if(nbAppel != 0 && nbAppel % updateDistribRate == 0)
        {
            std::cerr << "- Quality assessment : ";
            extremeQuality(quality, indicatorsSerie, cycleChoices, nbChoices, positiveChoices);
            // Clear information
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                indicatorsSerie[i].clear();
                cycleChoices[i] = 0;
            }
            std::cerr << "- Select new parameters : ";
            adaptivePursuit(quality, distribution);
            
            std::cerr << "Jump detection : ";
            if(jump(quality))
            {
                std::cerr << "Jump detected ! Reset strategy." << std::endl;
                for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
                {
                    nbChoices[i] = 0;
                    positiveChoices[i] = 0;
                    // Doit-on réinitialiser la distribution ? À priori oui.
                    distribution[i] = 1./NB_YAHSP_STRAT;
                }
    
            }
        }

    }*/
     
protected:

    double efficiency(Objective obj, const std::vector<int>& nbChoices, const std::vector<int>& positiveChoices)
    {
        //std::cerr << "( p : " << positiveChoice[obj] << " | n : " << nbChoices[obj] << ")"; 
        if(!efficiencyEstimation)
            return 1;
        if(nbChoices[obj] == 0)
            return 1;
        return 0.1+0.9*((double) positiveChoices[obj]) / nbChoices[obj];
    }
    
    void averageQuality(std::vector<double>& quality, 
                    const std::vector<std::vector<double> >& indicatorsSerie,
                    const std::vector<int>& cycleChoices, 
                    const std::vector<int>& nbChoices,
                    const std::vector<int>& positiveChoices
                    )
    {
        std::cerr << "- Average quality assessment strategy" << std::endl;
         std::cerr << "##### DUMP #####" << std::endl;
         std::cerr << "Makespan Add  -  Makespan Max  -  Cost  - Length" << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "Efficiency : " << efficiency(Objective(i), nbChoices, positiveChoices) << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "NbChoices : " <<nbChoices[i] << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "PosChoices : " << positiveChoices[i] << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "CycleChoices : " << cycleChoices[i] << " ";
        std::cerr << std::endl;
        
        std::cerr << "Makespan Add  -  Makespan Max  -  Cost  - Length" << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
        {
            //std::cerr << quality[i] << " -> ";
            quality[i] = 0;
            
            // If the objective never has been picked, we assume it does not participate to the quality
            if(cycleChoices[i] != 0) 
            {
                for(unsigned j = 0; j < indicatorsSerie[i].size(); j++)
                {
                    std::cerr << "Quality " << quality[i] << " + " << indicatorsSerie[i][j] << std::endl;
                    quality[i] += indicatorsSerie[i][j];
                }
                quality[i] /= cycleChoices[i]; // Average quality
                quality[i] *= efficiency(Objective(i), nbChoices, positiveChoices); // Ponderate by efficiency
                    
            }
            
            std::cerr << quality[i] << " - ";
        }
        std::cerr << std::endl;
    }
    
    
    void extremeQuality(std::vector<double>& quality, 
                    const std::vector<std::vector<double> >& indicatorsSerie,
                    const std::vector<int>& cycleChoices, 
                    const std::vector<int>& nbChoices,
                    const std::vector<int>& positiveChoices
                    )
    {
        std::cerr << "- Extreme quality assessment strategy" << std::endl;
         std::cerr << "##### DUMP #####" << std::endl;
         std::cerr << "Makespan Add  -  Makespan Max  -  Cost  - Length" << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "Efficiency : " << efficiency(Objective(i), nbChoices, positiveChoices) << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "NbChoices : " <<nbChoices[i] << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "PosChoices : " << positiveChoices[i] << " ";
        std::cerr << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            std::cerr << "CycleChoices : " << cycleChoices[i] << " ";
        std::cerr << std::endl;
        
        std::cerr << "Makespan Add  -  Makespan Max  -  Cost  - Length" << std::endl;
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
                std::cerr << "Quality : " << quality[i] << " ";
                quality[i] *= efficiency(Objective(i), nbChoices, positiveChoices); // Ponderate by efficiency
                    
            }
            
            std::cerr << quality[i] << " | ";
        }
        std::cerr << std::endl;
    }

    void probabilityMatching(const std::vector<double>& quality, std::vector<double>& distribution)
    {
        std::cerr << "- Probability matching selection strategy" << std::endl;
        double min = -std::min(0.,*std::min_element(quality.begin(), quality.end()));
            
        double sum = 0;
        std::cerr << "Makespan Add  -  Makespan Max  -  Cost  - Length" << std::endl;
        for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
        {
                //std::cerr << "On ajoute " << (quality[i] + min) << " ( Q :" << quality[i] << " min : " << min << " E : " <<  efficiency(Objective(i)) << " )"<< std::endl;
                sum += (quality[i] + min);
        }

        if(sum > 0)
        {
            //std::cerr << "New distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                std::cerr << distribution[i] << "  ->  ";
                distribution[i] = pmin + ((1-NB_YAHSP_STRAT*pmin)*(quality[i] + min)) / sum;
                std::cerr << distribution[i] << "  |  ";
            }
            std::cerr << std::endl;
        }
    }
    
    void adaptivePursuit(const std::vector<double>& quality, std::vector<double>& distribution)
    {
        std::cerr << "- Adaptive Pursuit selection strategy" << std::endl;
        double beta = 0.5;
        double pmax = 1 - (NB_YAHSP_STRAT - 1)*pmin;
        unsigned o = std::distance(quality.begin(), std::max_element(quality.begin(), quality.end()));    
        std::cerr << "Best : " << o << " | " << pmin << " - " << pmax << std::endl;
            //std::cerr << "New distribution : ";
            for(unsigned i = 0; i < NB_YAHSP_STRAT; i++)
            {
                std::cerr << distribution[i] << "  ->  ";
                if(i == o)
                    distribution[i] = distribution[i] + beta*(pmax - distribution[i]);
                else
                    distribution[i] = distribution[i] + beta*(pmin - distribution[i]);
                std::cerr << distribution[i] << "  |  ";
            }
            std::cerr << std::endl;
    }

    bool jump(std::vector<double>& quality)
    {
        std::cerr << "- Page Hinkley jump detection" << std::endl;
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
            std::cerr << "##### Page-Hinkley Test #####" << std::endl;
            std::cerr << "Iteration : " << it << std::endl;
            std::cerr << "Average Distribution Quality : " << averageDistribQuality << std::endl;
            std::cerr << "Current M : " << M << std::endl;
            std::cerr << "Max M : " << maxM << std::endl;
            std::cerr << "PHT : " << PHT << std::endl;
            if(PHT > epsilon)
                std::cerr << "Changement détecté !" << std::endl;
            else
                std::cerr << "Aucun changement." << std::endl;
            std::cerr << "#############################" << std::endl;
        
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






    Objective current;
    std::vector<double> distribution;
    std::vector<int> nbChoices;
    std::vector<int> positiveChoices;
    double mutRate;
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
        /*mutRate += rng.normal(0.1, 0.1);
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

        }*/
        
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
        //std::cerr << "Generate new strategy object" << std::endl;
       
        /*if(quality == "AQA")
        {
            std::cerr << "Average Quality Attribution" << std::endl;
            if(effect)
                ;
            else
                ;
        }
    
        if(update == "PM")
        {
            selectParameters = new AdaptivePursuit();
        }
        
        if(jump)
            jumpDetection = PageHinkley();*/
        Strategy<EOT> strat;
        return strat;
    }
    
protected :

    std::string indicator;
    bool effect;
    std::string quality;
    std::string update;
    bool jump;
};

template <class EOT>
double deltaPlus(EOT& o)
{
    double res = 0;
    //std::cerr << "(" << o.prevObjVector[0] << " - " << o.prevObjVector[1] << ") -> (" << o.objectiveVector(0) << " - " << o.objectiveVector(1) << ")" << std::endl;
    if(o.prevState == Feasible && o.state() == Feasible)
    {
        for(unsigned i = 0; i < o.objectiveVector().size(); i++)
            res += (o.prevObjVector[i] - o.objectiveVector(i)) / o.prevObjVector[i];   
    }
    else if(o.prevState == Feasible) 
    {
        res = -1;
    }
    else if(o.state() == Feasible)
    {
        res = 1;
    }
    
    return res;    
}

// TODO : Gérer le signe et peut être une alternative à 0 quand on a une amélioration sur un seul axe 
template <class EOT>
double deltaProd(EOT& o)
{
    double res = 0;
    if(o.prevState == Feasible && o.state() == Feasible)
    {
        res = 1;
        for(unsigned i = 0; i < o.objectiveVector().size(); i++)
            res *= (o.prevObjVector[i] - o.objectiveVector(i)) / o.prevObjVector[i];   
        //res /= 100*100; // pow(100, o.objectiveVector().size())
    }
    else if(o.prevState == Feasible) 
    {
        res = -1;
    }
    else if(o.state() == Feasible)
    {
        res = 1;
    }
    
    return res;    
}

// TODO : Gérer le signe !
template <class EOT>
double deltaExp(EOT& o)
{
    double res = 0;
    if(o.prevState == Feasible && o.state() == Feasible)
    {
        for(unsigned i = 0; i < o.objectiveVector().size(); i++)
            res += (o.prevObjVector[i] - o.objectiveVector(i)) / o.prevObjVector[i];   
        res = exp(res); // pow(100, o.objectiveVector().size())
    }
    else if(o.prevState == Feasible) 
    {
        res = -100000;
    }
    else if(o.state() == Feasible)
    {
        res = 100000;
    }
    
    return res;    
}

} // namespace daex

#endif // __STRATEGIES_H__
