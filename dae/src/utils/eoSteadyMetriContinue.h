/*
* <moeoArchiveObjectiveVectorSavingUpdater.h>
* Copyright (C) TAO Project-Team, INRIA-Saclay, 2011-2012
* (C) TAO Team, LRI, 2011-2012
*
Mostepha-Redouane Khouadjia
mostepha-redouane.khouadjia@inria.fr

* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use,
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info".
*
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited liability.
*
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or
* data to be ensured and,  more generally, to use and operate it in the
* same conditions as regards security.
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*
* ParadisEO WebSite : http://paradiseo.gforge.inria.fr
* Contact: paradiseo-help@lists.gforge.inria.fr
*
*/
//-----------------------------------------------------------------------------


#ifndef _eoSteadyMetriContinue_h
#define _eoSteadyMetriContinue_h

#include <eoContinue.h>
#include <utils/eoLogger.h>
#include <metric/moeoHyperVolumeMetric.h>
#include <archive/moeoUnboundedArchive.h>

/**
    A continuator:  does a minimum number of generations, then
    stops whenever a given number of generations takes place without improvement in terms of hypervolume

    @ingroup Continuators
*/
template< class MOEOT>
class eoSteadyMetriContinue: public eoContinue<MOEOT>
{
public:

    typedef typename MOEOT::ObjectiveVector ObjectiveVector;

    /// Ctor for setting a
    eoSteadyMetriContinue(unsigned long _minGens, 
            unsigned long _steadyGens,moeoArchive < MOEOT > & _archive, 
            bool _normalize=true, 
            double _rho=1.1) : 
        repMinGenerations( _minGens ), repSteadyGenerations( _steadyGens),
        steadyState(false), thisGenerationPlaceHolder(0),
        thisGeneration(thisGenerationPlaceHolder),
        arch(_archive),metric(_normalize,_rho)
    {};
      
    eoSteadyMetriContinue(unsigned long _minGens, 
            unsigned long _steadyGens, 
            moeoArchive < MOEOT > & _archive, 
            bool _normalize=true, 
            ObjectiveVector& _ref_point=NULL) : 
        repMinGenerations( _minGens ), repSteadyGenerations( _steadyGens),
        steadyState(false), thisGenerationPlaceHolder(0),
        thisGeneration(thisGenerationPlaceHolder),
        arch(_archive), metric(_normalize,_ref_point)
    {};
      

    /// Ctor for enabling the save/load the no. of generations counted
    eoSteadyMetriContinue(unsigned long _minGens, 
            unsigned long _steadyGen,
            unsigned long& _currentGen,
            moeoArchive < MOEOT > & _archive, 
            bool _normalize=true, 
            double _rho=1.1) : 
        repMinGenerations( _minGens ), 
        repSteadyGenerations( _steadyGen),
        steadyState(_currentGen>_minGens), 
        thisGenerationPlaceHolder(0),
        arch(_archive), 
        thisGeneration(_currentGen),
        metric(_normalize,_rho)
    {};

    eoSteadyMetriContinue(unsigned long _minGens, 
            unsigned long _steadyGen,
            unsigned long& _currentGen,
            moeoArchive < MOEOT > & _archive, 
            bool _normalize=true, 
            ObjectiveVector& _ref_point=NULL) : 
        repMinGenerations( _minGens ), 
        repSteadyGenerations( _steadyGen),
        steadyState(_currentGen>_minGens), 
        thisGenerationPlaceHolder(0),
        arch(_archive), 
        thisGeneration(_currentGen), 
        metric(_normalize,_ref_point)
    {};
      
    /** Returns false when a certain number of generations is
    * reached withtout improvement
    */
    virtual bool operator() (const eoPop<MOEOT>& _pop )
    {
        double bestCurrentMetric=0.0; 
        
        std::vector < ObjectiveVector > currentParetoSet;
        
        for (size_t i=0; i<arch.size(); i++)  
            currentParetoSet.push_back(arch[i].objectiveVector());
     
        if (arch.size())
        {
	        if (thisGeneration!=0)
	        { 
	            bestCurrentMetric= metric(currentParetoSet,oldParetoSet);
	            if (steadyState) 
	            {     // already after MinGenenerations
	                if (bestCurrentMetric > bestSoFar) 
	                {
	                    bestSoFar = bestCurrentMetric;
	                    lastImprovement = thisGeneration;
	                } 
	                else 
	                {
                        if (thisGeneration - lastImprovement > repSteadyGenerations) 
                        {
                            eo::log << eo::progress << "STOP in eoSteadyMetriContinue: Done " << repSteadyGenerations << " generations without improvement\n";
                            return false;
	                    }
	                }
	            } 
	            else 
	            {               // not yet in steady state
                    if (thisGeneration > repMinGenerations) 
                    { // go to steady state
                        steadyState = true;
                        bestSoFar = bestCurrentMetric;
                        lastImprovement = thisGeneration;
	                    eo::log << eo::progress << "eoSteadyMetriContinue: Done the minimum number of generations\n";
	                }
                }
            }
            else
	            oldParetoSet=currentParetoSet;
        } 
        thisGeneration++;
        return true;
    }

    /** Sets the parameters (minimum nb of gen. + steady nb of gen.)
      and sets the current generation to 0 (the begin)
      @todo replace thi by an init method ?
    */
    virtual void totalGenerations(unsigned long _mg, unsigned long _sg) 
    {
        repMinGenerations = _mg;
        repSteadyGenerations = _sg;
        reset();
    };

    /// Resets the state after it's been reached
    virtual void reset () 
    {
        steadyState=false;
        thisGeneration = 0;
    }

    /** accessors*/
    virtual unsigned long minGenerations( )
    {  
        return repMinGenerations;  
    };
    
    
    virtual unsigned long steadyGenerations()
    {
        return repSteadyGenerations;
    };

  virtual std::string className(void) const { return "eoSteadyMetriContinue"; }
  
private:

    unsigned long repMinGenerations;
    unsigned long  repSteadyGenerations;
    bool steadyState;
    unsigned long thisGenerationPlaceHolder;
    unsigned long& thisGeneration;
    unsigned int lastImprovement;
    double bestSoFar;
    moeoHyperVolumeDifferenceMetric <ObjectiveVector> metric;
    // moeoVectorVsVectorBinaryMetric < ObjectiveVector, double > & metric;
    moeoArchive <MOEOT> & arch;
    std::vector < ObjectiveVector > oldParetoSet;
};

#endif
