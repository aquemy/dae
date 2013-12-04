/*
* <make_checkpoint_daemoeo.h>
 
//-----------------------------------------------------------------------------
**/
#ifndef MAKE_CHECKPOINT_DAEMOEO_H_
#define MAKE_CHECKPOINT_DAEMOEO_H_

#include <do/make_checkpoint_moeo.h>
#include "utils/eoFeasibleStat.h"
#include "utils/moeoPopObjectiveVectorSavingUpdater.h"
#include "utils/moeoArchiveObjectiveVectorTimeSavingUpdater.h"
#include "utils/eoPlanStat.h"
#include <metric/moeoHyperVolumeDifferenceMetric.h>
template < class MOEOT >
eoCheckPoint < MOEOT > & do_make_checkpoint_daemoeo (eoParser & _parser, eoState & _state, eoEvalFuncCounter < MOEOT > & _eval, eoContinue < MOEOT > & _continue, eoPop < MOEOT > & _pop, moeoArchive < MOEOT > & _archive)
{
  eoCheckPoint < MOEOT > & checkpoint = _state.storeFunctor(new eoCheckPoint < MOEOT > (_continue));
  /* the objective vector type */
  typedef typename MOEOT::ObjectiveVector ObjectiveVector;

  ///////////////////
  // Counters
  //////////////////
  // is nb Eval to be used as counter?
  //bool useEval = _parser.getORcreateParam(true, "useEval", "Use nb of eval. as counter (vs nb of gen.)", '\0', "Output").value();
  // Create anyway a generation-counter parameter
  eoValueParam<unsigned int> *generationCounter = new eoValueParam<unsigned int>(0, "Gen.");
  // Create an incrementor (sub-class of eoUpdater).
  eoIncrementor<unsigned int> & increment = _state.storeFunctor( new eoIncrementor<unsigned int>(generationCounter->value()) );
  // Add it to the checkpoint
  checkpoint.add(increment);
  
  //  we probably need an eoTimeCounter
  eoTimeCounter *tCounter =  new eoTimeCounter;
   _state.storeFunctor(tCounter);
   checkpoint.add(*tCounter);


  // dir for DISK output
  std::string & dirName =  _parser.getORcreateParam(std::string("Res"), "resDir", "Directory to store DISK outputs", '\0', "Output").value();
  // shoudl we empty it if exists
  eoValueParam<bool>& eraseParam = _parser.getORcreateParam(true, "eraseDir", "erase files in dirName if any", '\0', "Output");
  bool dirOK = false;		   // not tested yet

  // Dump of the whole population
  //-----------------------------
  bool printPop = _parser.getORcreateParam(false, "printPop", "Print sorted pop. every gen.", '\0', "Output").value();
  eoSortedPopStat<MOEOT> * popStat;
  if ( printPop ) // we do want pop dump
    {
      popStat = & _state.storeFunctor(new eoSortedPopStat<MOEOT>);
      checkpoint.add(*popStat);
    }
       
  bool printPlan = _parser.getORcreateParam(false, "printPlan", "Print sorted plan. every gen.", '\0', "Output").value();
 
  if ( printPlan ) // we do want plan dump
    {
      eoSortedPlanStat<MOEOT> * planStat = & _state.storeFunctor(new eoSortedPlanStat<MOEOT>);
      checkpoint.add(*planStat);
    }
    
   
  //////////////////////////////////
  // State savers
  //////////////////////////////
  // feed the state to state savers
  // save state every N  generation
  eoValueParam<unsigned int>& saveFrequencyParam = _parser.createParam((unsigned int)(0), "saveFrequency", "Save every F generation (0 = only final state, absent = never)", '\0', "Persistence" );
  if (_parser.isItThere(saveFrequencyParam))
    {
      // first make sure dirName is OK
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
      unsigned int freq = (saveFrequencyParam.value()>0 ? saveFrequencyParam.value() : UINT_MAX );
#ifdef _MSVC
      std::string stmp = dirName + "\generations";
#else
      std::string stmp = dirName + "/generations";
#endif
      eoCountedStateSaver *stateSaver1 = new eoCountedStateSaver(freq, _state, stmp);
      _state.storeFunctor(stateSaver1);
      checkpoint.add(*stateSaver1);
    }
  // save state every T seconds
  eoValueParam<unsigned int>& saveTimeIntervalParam = _parser.getORcreateParam((unsigned int)(0), "saveTimeInterval", "Save every T seconds (0 or absent = never)", '\0',"Persistence" );
  if (_parser.isItThere(saveTimeIntervalParam) && saveTimeIntervalParam.value()>0)
    {
      // first make sure dirName is OK
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\time";
#else
      std::string stmp = dirName + "/time";
#endif
      eoTimedStateSaver *stateSaver2 = new eoTimedStateSaver(saveTimeIntervalParam.value(), _state, stmp);
      _state.storeFunctor(stateSaver2);
      checkpoint.add(*stateSaver2);
    }

  ///////////////////
  // Archive
  //////////////////
  // update the archive every generation
  bool updateArch = _parser.getORcreateParam(true, "updateArch", "Update the archive at each gen.", '\0', "Evolution Engine").value();
  if (updateArch)
    {
      moeoArchiveUpdater < MOEOT > * updater = new moeoArchiveUpdater < MOEOT > (_archive, _pop);
      _state.storeFunctor(updater);
      checkpoint.add(*updater);
    }
  // store the objective vectors contained in the archive every generation
  bool storeArch = _parser.getORcreateParam(false, "storeArch", "Store the archive's objective vectors at each gen.", '\0', "Output").value();
  
  bool printArch = _parser.getORcreateParam(false, "printArch", "Print the archive at each gen.", '\0', "Output").value(); 
  
  if (storeArch)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\arch";
#else
      std::string stmp = dirName + "/arch";
#endif
          
      moeoArchiveObjectiveVectorSavingUpdater < MOEOT > * save_updater = new moeoArchiveObjectiveVectorSavingUpdater < MOEOT > (_archive, stmp, printArch);
      _state.storeFunctor(save_updater);
      checkpoint.add(*save_updater);
    }
    
      
  eoValueParam<unsigned int>&  saveIntervalArch = _parser.getORcreateParam((unsigned int)(0), "saveIntervalArch", "Save the archive's objective vectors every T seconds (0 or absent = never)", '\0', "Output");
  
  bool printIntervalArch = _parser.getORcreateParam(false, "printIntervalArch", "Print the archive at each time interval", '\0', "Output").value(); 
     
  
  if (_parser.isItThere(saveIntervalArch) && saveIntervalArch.value()>0)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\archTime";
#else
      std::string stmp = dirName + "/archTime";
#endif
        
      moeoArchiveObjectiveVectorTimeSavingUpdater < MOEOT > * saveTimeUpdater = new moeoArchiveObjectiveVectorTimeSavingUpdater < MOEOT > (_archive, stmp, saveIntervalArch.value(),printIntervalArch);
      _state.storeFunctor(saveTimeUpdater);
      checkpoint.add(*saveTimeUpdater);
    }
    
  ///////////////////
  // Pop
  //////////////////
  // update the pop vectors every generation    
  
  bool storePopVectors = _parser.getORcreateParam(false, "storePopVectors", "Store the pop's objective vectors at each gen.", '\0', "Output").value();
  
  bool printPopVectors = _parser.getORcreateParam(false, "printPopVectors", "Print the pop vectors at each gen.", '\0', "Output").value(); 
  
  if (storePopVectors)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\pop";
#else
      std::string stmp = dirName + "/pop";
#endif
      
      moeoPopObjectiveVectorSavingUpdater < MOEOT > * save_popvec_updater = new moeoPopObjectiveVectorSavingUpdater < MOEOT > (_pop, stmp, printPopVectors);
      _state.storeFunctor(save_popvec_updater);
      checkpoint.add(*save_popvec_updater);
    }
    ///////////////////
  // Metrics
  ////////////////// 
        
  // store the contribution of the non-dominated solutions
  bool cont = _parser.getORcreateParam(false, "contribution", "Store the contribution of the archive at each gen.", '\0', "Output").value();
  if (cont)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\contribution";
#else
      std::string stmp = dirName + "/contribution";
#endif
      moeoContributionMetric < ObjectiveVector > * contribution = new moeoContributionMetric < ObjectiveVector >;
      moeoBinaryMetricSavingUpdater < MOEOT > * contribution_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*contribution, _archive, stmp);
      _state.storeFunctor(contribution_updater);
      checkpoint.add(*contribution_updater);
    }
  // store the entropy of the non-dominated solutions
  bool ent = _parser.getORcreateParam(false, "entropy", "Store the entropy of the archive at each gen.", '\0', "Output").value();
  if (ent)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\entropy";
#else
      std::string stmp = dirName + "/entropy";
#endif
      moeoEntropyMetric < ObjectiveVector > * entropy = new moeoEntropyMetric < ObjectiveVector >;
      moeoBinaryMetricSavingUpdater < MOEOT > * entropy_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*entropy, _archive, stmp);
      _state.storeFunctor(entropy_updater);
      checkpoint.add(*entropy_updater);
    }
    
     bool hyper = _parser.getORcreateParam(false, "hypervolume", "Store the hypervolume of the archive at each gen.", '\0', "Output").value();
  if (hyper)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\hypervolume";
#else
      std::string stmp = dirName + "/hypervolume";
#endif
     moeoHyperVolumeDifferenceMetric <ObjectiveVector> *hypervolume = new moeoHyperVolumeDifferenceMetric <ObjectiveVector> (true,1.1);
     moeoBinaryMetricSavingUpdater < MOEOT > * hypervolume_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*hypervolume, _archive, stmp);
     _state.storeFunctor(hypervolume_updater);
      checkpoint.add(*hypervolume_updater);
    }
    
     bool epsi = _parser.getORcreateParam(false, "EpsilonAdditive", "Store the Epsilon Additive of the archive at each gen.", '\0', "Output").value();
  if (epsi)
    {
      if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
#ifdef _MSVC
      std::string stmp = dirName + "\epsilon";
#else
      std::string stmp = dirName + "/epsilon";
#endif
     moeoVecVsVecAdditiveEpsilonBinaryMetric <ObjectiveVector> *epsilon = new moeoVecVsVecAdditiveEpsilonBinaryMetric  <ObjectiveVector>;
     moeoBinaryMetricSavingUpdater < MOEOT > * epsilon_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*epsilon, _archive, stmp);
     _state.storeFunctor(epsilon_updater);
      checkpoint.add(*epsilon_updater);
    }
    
    //Stats on archive and population
    
    // display the stats on std::cout
    // ostream & out, bool _verbose=true, std::string _delim = "\t", unsigned int _width=20, char _fill=' ' 
   // eoOStreamMonitor cout_monitor( std::cout, "\t", 10, ' '); 
   
     // display the stats on std::cout
    // ostream & out, bool _verbose=true, std::string _delim = "\t", unsigned int _width=20, char _fill=' ' 
    
     
      
     
     bool printStatsParam = _parser.getORcreateParam(true, "printStats", "Print Best/avg/feasible every gen.", '\0', "Output").value();
      
     
     if (printStatsParam)
    {
         if (! dirOK )
        dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
	#ifdef _MSVC
	std::string stmp = dirName + "\stats";
	#else
	std::string stmp = dirName + "/stats";
	#endif
      
         moeoBestObjVecStat < MOEOT > *best_stat = new moeoBestObjVecStat < MOEOT >;
	_state.storeFunctor(best_stat);
      
	moeoAverageObjVecStat < MOEOT > *average_stat = new moeoAverageObjVecStat < MOEOT >;
	_state.storeFunctor(average_stat);
	
	
	eoFeasibleStat <MOEOT> *feasible_stat =  new eoFeasibleStat <MOEOT>;
	
	eoAverageSizeStat<MOEOT> *asize_stat = new eoAverageSizeStat <MOEOT> ;
	
	checkpoint.add(*best_stat);
	checkpoint.add(*average_stat);
	checkpoint.add(*feasible_stat);
	checkpoint.add(*asize_stat);
	
  
// 	eoOStreamMonitor monitor =   new eoOStreamMonitor( std::cout, "\t", 10, ' '); 
	eoStdoutMonitor *monitor = new eoStdoutMonitor(false);
        _state.storeFunctor(monitor);
	monitor -> add(*generationCounter); 
	monitor -> add(*best_stat);
	monitor -> add(*average_stat);
	monitor -> add(*feasible_stat);
	monitor -> add(*asize_stat);
	monitor -> add(*tCounter);

	
	checkpoint.add(*monitor);
       
	//eoFileMonitor  *file_monitor =  eoFileMonitor(stmp, "\n", false, false, true); 
	eoFileMonitor *file_monitor = new eoFileMonitor(stmp);
	_state.storeFunctor(file_monitor); 
	file_monitor -> add(*generationCounter);      
	file_monitor -> add(*best_stat);
	file_monitor -> add(*average_stat);    
	file_monitor -> add(*feasible_stat);
	file_monitor -> add(*asize_stat);
        file_monitor -> add(*tCounter);

	
	checkpoint.add(*file_monitor );
	
    }

 
    
   // now some statistics on the archive and/or population:
 
   // Best ObjectVector in population
 
//     bool printBestParam  = _parser.getORcreateParam(true, "printBestStat", "Print Best/avg// every gen.", '\0', "Output");
//     
//     
//      if ( printBestParam) {
//          
//    	 if (! dirOK )
//     
//        	 dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
// 	 #ifdef _MSVC
//          std::string stmp = dirName + "\Best";
//          #else
//          std::string stmp = dirName + "/Best";
//          #endif
// 
// /*
//    moeoBestObjVecStat< MOEOT > *bestStat = NULL;   
//    
//    if ( printBestParam.value()) {
//    */
//  
//          moeoBestObjVecStat< MOEOT > *   bestStat = new moeoBestObjVecStat< MOEOT>;
// 
//          // store it
//  
//          _state.storeFunctor(bestStat);
//  
//          // add it to the checkpoint
// 
//          checkpoint.add(*bestStat);
//  
//  	}    
//        // Average Objective vector  
// 	if ( printBestParam) {
//          
//    	 if (! dirOK )
//     
//        	 dirOK = testDirRes(dirName, eraseParam.value()); // TRUE
// 	
// 	 #ifdef _MSVC
//          std::string stmp = dirName + "\Average";
//          #else
//          std::string stmp = dirName + "/Average";
//          #endif
//  
//        moeoAverageObjVecStat< MOEOT >*  averageStat = new moeoAverageObjVecStat<MOEOT>;
//  
//          // store it
//  
//         _state.storeFunctor(averageStat);
//  
//          // add it to the checkpoint
//  
//          checkpoint.add(*averageStat);
//  
//        }

   
    

  // and that's it for the (control and) output
  return checkpoint;
}

#endif /*MAKE_CHECKPOINT_DAEMOEO_H_*/