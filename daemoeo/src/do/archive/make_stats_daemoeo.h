// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-



 
//-----------------------------------------------------------------------------
/*
* <make_checkpoint_dae.h>
* Copyright (C) TAO Project-Team, INRIA Saclay-LRI && Thales Group, 2011-2012
* DESCARWIN ANR project 
* Author: <Mostepha R. Khouadjia>
* Copyright: See COPYING file that comes with this distribution
*
*
*///-----------------------------------------------------------------------------
 


#ifndef _make_checkpoint_dae_h
#define _make_checkpoint_dae_h


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <climits>

#include <eoScalarFitness.h>
#include <utils/selectors.h> // for minimizing_fitness()
#include <EO.h>
#include <eoEvalFuncCounter.h>
#include <utils/checkpointing>


template<class EOT> 
eoCheckPoint<EOT>& do_make_checkpoint(eoParser& _parser, eoState& _state, eoValueParam<unsigned long>& _eval, eoContinue<EOT>& _continue)
{
  std::string plan_file = _parser.getORcreateParam( (std::string)"plan.ipc", "plan-file", "Plan file backup", 'F', "Misc" ).value();
  
 eoValueParam<unsigned>& popSize = _parser.getORcreateParam(unsigned(20), "popSize", "Population Size", 'P', "Evolution Engine");

 
 
  // first, create a checkpoint from the eoContinue
  eoCheckPoint<EOT> *checkpoint = new eoCheckPoint<EOT>(_continue);

  _state.storeFunctor(checkpoint);
  
  
  eoIncrementorParam<unsigned> *generationCounter = new eoIncrementorParam<unsigned>("Gen.");

  // store it in the state

  _state.storeFunctor(generationCounter);

  // And add it to the checkpoint,

  checkpoint->add(*generationCounter);
  
  
  
    // get the best plan only if it improve the fitness
    // note: fitness is different from the makespan!
    // worst fitness, TODO we should use the best individual from the previous evals at init
    eoMinimizingDualFitness worst_fitness( std::make_pair<double,bool>( DBL_MAX, 1 ) );
  
   
    eoBestPlanImprovedStat<EOT> * best_plan = new eoBestPlanImprovedStat<EOT> ( worst_fitness, "Best improved plan");
    
    
    _state.storeFunctor(best_plan);
    
    // at each generation
    checkpoint->add( *best_plan );
    
    // display the stats on std::cout
    // ostream & out, bool _verbose=true, std::string _delim = "\t", unsigned int _width=20, char _fill=' ' 
    eoOStreamMonitor * cout_monitor = new  eoOStreamMonitor ( std::cout, "\t", 10, ' '); 
	_state.storeFunctor (cout_monitor);

    // get best fitness
    // for us, has the form "fitness feasibility" (e.g. "722367 1")
    eoBestFitnessStat<EOT> * best_stat = new  eoBestFitnessStat<EOT>("Best");
    
    _state.storeFunctor(best_stat);
    
    
    /*
       eoAverageStat<EOT> averageStat = new eoAverageStat<EOT>;

        // store it

        _state.storeFunctor(averageStat);*/

    

    //eoInterquartileRangeStat<EOT> iqr_stat( std::make_pair(0.0,false), "IQR" );
    eoInterquartileRangeStat<EOT> * iqr_f = new eoInterquartileRangeStat<EOT> ( std::make_pair(0.0,false), "IQR_f" );
    
     _state.storeFunctor(iqr_f);
    eoInterquartileRangeStat<EOT> *iqr_uf = new eoInterquartileRangeStat<EOT> ( std::make_pair(0.0,false), "IQR_uf" );
    
     _state.storeFunctor(iqr_uf);
    
    eoDualStatSwitch<EOT,eoInterquartileRangeStat<EOT> >* dual_iqr =  new  eoDualStatSwitch<EOT,eoInterquartileRangeStat<EOT> > (* iqr_f,* iqr_uf, "\t" );
    
    
     _state.storeFunctor(dual_iqr);
 
    // TODO implement "better" nth_element stats with different interpolations (linear and second moment?)
    eoNthElementFitnessStat<EOT> *median_stat = new eoNthElementFitnessStat<EOT> ( popSize.value() / 2, "Median" ); 
    
    
     _state.storeFunctor(median_stat);
    /*
    eoNthElementFitnessStat<EOT> median_f( pop.size() / 2, "Median_f" ); 
    eoNthElementFitnessStat<EOT> median_uf( pop.size() / 2, "Median_uf" ); 
    eoDualStatSwitch<EOT,eoNthElementFitnessStat<EOT> > dual_median( median_f, median_uf, "\t/\t" );
    */

    eoFeasibleRatioStat<EOT> *feasible_stat = new  eoFeasibleRatioStat<EOT>( "F.Ratio" );
    
    
     _state.storeFunctor(feasible_stat);

    eoAverageSizeStat<EOT> *asize_stat = new    eoAverageSizeStat<EOT> ( "Av.Size" );
    
    
     _state.storeFunctor(asize_stat);

   
        // compute stas at each generation
        checkpoint -> add( *best_stat );
            // add it to the checkpoint

      
        checkpoint->add( *feasible_stat );
        checkpoint->add( *asize_stat );
        checkpoint->add( *median_stat );
        //checkpoint.add( dual_median );
        //checkpoint.add( iqr_stat );
        checkpoint->add( *dual_iqr );

        cout_monitor->add( *best_stat );
        cout_monitor->add( *asize_stat );
        cout_monitor->add(* feasible_stat );
        cout_monitor->add(* median_stat );
        //cout_monitor.add( dual_median );
        //cout_monitor.add( iqr_stat );
        cout_monitor->add( *dual_iqr );
        
        // the checkpoint should call the monitor at every generation
        checkpoint->add( *cout_monitor );
    

    // append the plans in a file
    // std::string _filename, std::string _delim = " ", bool _keep = false, bool _header=false, bool _overwrite = false
    eoFileMonitor *file_monitor = new eoFileMonitor ( plan_file, "\n", false, false, true);
    
    
     _state.storeFunctor(file_monitor);
     
    file_monitor-> add( *best_plan );

    checkpoint-> add( *file_monitor );
    
  

    // and that's it for the (control and) output

    return *checkpoint;

}



#endif
