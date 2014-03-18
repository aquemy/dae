/*
* <make_checkpoint_daemoeo.h>
 
//-----------------------------------------------------------------------------
**/
#ifndef MAKE_CHECKPOINT_DAEMOEO_H_
#define MAKE_CHECKPOINT_DAEMOEO_H_

#include <limits>
#include <do/make_checkpoint_moeo.h>
#include "utils/feasibleStat.h"
#include "utils/moeoPopObjectiveVectorSavingUpdater.h"
#include "utils/moeoArchiveObjectiveVectorTimeSavingUpdater.h"
#include "utils/moeoPopObjectiveVectorTimeSavingUpdater.h"
#include "utils/eoPlanStat.h"
#include <metric/moeoHyperVolumeDifferenceMetric.h>


#include <utils/checkpointing>

namespace daex {

#define DAEX_FEASIBILITY_SUFFIX "_f"
#define DAEX_UNFEASIBILITY_SUFFIX "_u"
#define DAEX_FEASIBILITY_SEP " / "
#define DAEX_LOG_SEP ", "

//! Wrap given statistic computation operators into a dual switch
template<class EOSTAT>
eoDualStatSwitch<EOSTAT>& make_dual_stat( std::string name, eoState& state )
{
    EOSTAT* stat_feasible = new EOSTAT(name+DAEX_FEASIBILITY_SUFFIX);
    state.storeFunctor( stat_feasible );

    EOSTAT* stat_unfeasible = new EOSTAT(name+DAEX_UNFEASIBILITY_SUFFIX);
    state.storeFunctor( stat_unfeasible );

    eoDualStatSwitch<EOSTAT>* dual_stat = new eoDualStatSwitch<EOSTAT>( *stat_feasible, *stat_unfeasible, DAEX_FEASIBILITY_SEP);
    state.storeFunctor( dual_stat );

    return *dual_stat;
}

template<class EOSTAT, class T>
eoDualStatSwitch<EOSTAT>& make_dual_stat_param( T& param, std::string name, eoState& state )
{
    EOSTAT* stat_feasible = new EOSTAT( param, name+DAEX_FEASIBILITY_SUFFIX);
    state.storeFunctor( stat_feasible );

    EOSTAT* stat_unfeasible = new EOSTAT( param, name+DAEX_UNFEASIBILITY_SUFFIX);
    state.storeFunctor( stat_unfeasible );

    eoDualStatSwitch<EOSTAT>* dual_stat
        = new eoDualStatSwitch<EOSTAT>( *stat_feasible, *stat_unfeasible, DAEX_FEASIBILITY_SEP);
    state.storeFunctor( dual_stat );

    return *dual_stat;
}



//! Add multi-objective (fitness-dependent) checkpoints to the checkpoint
template<class EOT>
void add_stats_multi( eoCheckPoint<EOT>& checkpoint, eoOStreamMonitor& clog_monitor, eoState & state, eoPop<EOT>& pop, moeoArchive<EOT>& archive, eoParser & parser )
{
  //typedef typename EOT::ObjectiveVector OVT;

    // NOTE: this is MANDATORY to update the pareto archive
    moeoArchiveUpdater<EOT> * arch_updater = new moeoArchiveUpdater<EOT>( archive, pop);
    state.storeFunctor( arch_updater );
    checkpoint.add( *arch_updater );

    if( eo::log.getLevelSelected() >= eo::progress ) {
        // instanciate a metric comparing two Pareto front (hence a "binary" one)
        // use OVT, the type of the objective vectors

        // get best fitness
        // for us, has the form "fitness feasibility" (e.g. "722367 1")
        eoStat<EOT,std::string>& best_fit_stat = make_dual_stat< eoBestFitnessStat<EOT> >( "BestFit", state );

        // TODO implement "better" nth_element stats with different interpolations (linear and second moment?)
        // we should use a ratio here, and not a position,
        // because the size of a [un]feasible pop is unknown at runtime
        double median_ratio = 0.5;
        eoStat<EOT,std::string>& median_stat = make_dual_stat_param< eoNthElementStat<EOT> >( median_ratio, "MedFit", state );

        checkpoint.add( best_fit_stat );
        checkpoint.add( median_stat );
        clog_monitor.add( best_fit_stat );
        clog_monitor.add( median_stat );

        // typename OVT::Type m( 0.0, true);
        // typename OVT::Type c( 0.0, true);
        //PS typename OVT::Type m( std::numeric_limits<int>::max(), false);
        //PS typename OVT::Type c( std::numeric_limits<int>::max(), false);
	//typename OVT::Type m(3000.0, false);
        //typename OVT::Type c(2000.0, false);
        //OVT ref(m,c);
	//OVT* ref = new OVT(m,c); 

	//OVT* ref = new OVT(2.0,false); // FIXME: Variable never deleted!
	//PlanningObjectiveVector* ref = new PlanningObjectiveVector;
	//	typename EOT::ObjectiveVector* ref = new typename EOT::ObjectiveVector(2.0,false);
	//ref->operator[](0) = PlanningObjectiveVector::Type(1000.0, false); // sans faire de reserve ?
	//ref->operator[](1) = PlanningObjectiveVector::Type(1000.0, false); // sans faire de reserve ?

	//(* ref)[0] = typename EOT::Fitness(1000.0, false); // sans faire de reserve ?
	//(* ref)[1] = typename EOT::Fitness(1000.0, false); // sans faire de reserve ?

	//(* ref)[0]= typename OVT::Type(3000.0, false);
	//(* ref)[1]= typename OVT::Type(2000.0, false);
	//eo::log << eo::progress << FORMAT_LEFT_FILL_W_PARAM << "******************************** REF_POINT=" << *ref << std::endl;

        //PS moeoDualHyperVolumeDifferenceMetric<OVT> * m_hypervolume = new moeoDualHyperVolumeDifferenceMetric<OVT>(true,ref);

	//moeoDualHyperVolumeMetric<typename EOT::ObjectiveVector> * m_hypervolume = new moeoDualHyperVolumeMetric<typename EOT::ObjectiveVector>(false,*ref); //PS
	//moeoDualHyperVolumeMetric<OVT> * m_hypervolume = new moeoDualHyperVolumeMetric<OVT>(true,1.1); //PS


        // moeoDualHyperVolumeDifferenceMetric<OVT> * m_hypervolume = new moeoDualHyperVolumeDifferenceMetric<OVT>(true,1.1);

        //PS eoStat<EOT,std::string>& hypervolume = make_dual_stat_param< moeoBinaryMetricStat<EOT> >( *m_hypervolume, "HypVol", state );

        //eoStat<EOT,std::string>& hypervolume = make_dual_stat_param< moeoUnaryMetricStat<EOT> >( *m_hypervolume, "HypVol", state );

        //checkpoint.add( hypervolume );
        //clog_monitor.add( hypervolume );

        // FIXME the epsilon stat cannot handle dual fitness, it must be overloaded
        // moeoVecVsVecAdditiveEpsilonBinaryMetric<OVT> * m_epsilon = new moeoVecVsVecAdditiveEpsilonBinaryMetric<OVT>;
        // eoStat<EOT,std::string>& epsilon = make_dual_stat_param< moeoBinaryMetricStat<EOT> >( *m_epsilon, "Epsi", state );
        // checkpoint.add( epsilon );
        // clog_monitor.add( epsilon );

        eoStat<EOT,std::string>& best_stat = make_dual_stat< moeoBestObjVecStat<EOT> >("Best", state );
        checkpoint.add( best_stat );
        clog_monitor.add( best_stat );

        eoStat<EOT,std::string>& average_stat = make_dual_stat< moeoAverageObjVecStat<EOT> >("Avrg", state );
        checkpoint.add( average_stat );
        clog_monitor.add( average_stat );

        moeoContributionMetric<typename EOT::ObjectiveVector> * m_contribution = new moeoContributionMetric<typename EOT::ObjectiveVector>;
        // state.storeFunctor( m_contribution ); // can't store this due to ambiguous base with a different template type // FIXME use smart pointers
        // wrap it in an eoStat
        eoStat<EOT,std::string>& contribution = make_dual_stat_param< moeoBinaryMetricStat<EOT> >( *m_contribution, "Cntrb", state );
        // add it to the checkpoint
        checkpoint.add( contribution );
        clog_monitor.add( contribution );

        // <JD> the moeo entropy metric segfaults for small distances, don't know why
        // moeoEntropyMetric<OVT> * m_entropy = new moeoEntropyMetric<OVT>;
        // // state.storeFunctor( m_entropy );
        // moeoBinaryMetricStat<EOT>* entropy = new moeoBinaryMetricStat<EOT>( *m_entropy, "Entropy" );
        // state.storeFunctor( entropy );
        // checkpoint.add( *entropy );
        // clog_monitor.add( *entropy );


        std::string out_dir = parser.valueOf<std::string>("out-dir");
#ifdef _MSVC
        std::string stmp = out_dir + "\arch";
#else
        std::string stmp = out_dir + "/arch"; // FIXME get the directory from the parser
#endif
        moeoArchiveObjectiveVectorSavingUpdater<EOT> * save_updater = new moeoArchiveObjectiveVectorSavingUpdater<EOT>(archive, stmp, /*count*/true);
        state.storeFunctor(save_updater);
        checkpoint.add(*save_updater);
    }

}





//! Add mono-objective (fitness-dependent) checkpoints to the checkpoint
template<class EOT>
void add_stats_mono( eoCheckPoint<EOT>& checkpoint, eoOStreamMonitor& clog_monitor, eoState & state )
{
#ifdef SINGLE_EVAL_ITER_DUMP
    BestMakespanStat* stat_makespan = new BestMakespanStat("BestMakespan");
    state.storeFunctor( stat_makespan );
    BestPlanStat* stat_plan = new BestPlanStat("BestPlan");
    state.storeFunctor( stat_plan );
#endif

#ifndef NDEBUG
    if( eo::log.getLevelSelected() >= eo::progress ) {
        // get best fitness
        // for us, has the form "fitness feasibility" (e.g. "722367 1")
        eoStat<EOT,std::string>& best_stat = make_dual_stat< eoBestFitnessStat<EOT> >( "Best", state );

        // TODO implement "better" nth_element stats with different interpolations (linear and second moment?)
        // we should use a ratio here, and not a position,
        // because the size of a [un]feasible pop is unknown at runtime
        double median_ratio = 0.5;
        eoStat<EOT,std::string>& median_stat = make_dual_stat_param< eoNthElementStat<EOT> >( median_ratio, "Median", state );

        checkpoint.add( best_stat );
        checkpoint.add( median_stat );
        clog_monitor.add( best_stat );
        clog_monitor.add( median_stat );
#ifdef SINGLE_EVAL_ITER_DUMP
        checkpoint.add( *stat_makespan );
        clog_monitor.add( *stat_makespan );
        checkpoint.add( *stat_plan );
        clog_monitor.add( *stat_plan );
#endif
    }

#ifdef SINGLE_EVAL_ITER_DUMP
    // Note: commented here because superseeded by the eoEvalBestPlanFileDump
    // append the plans in a file
    // std::string _filename, std::string _delim = " ", bool _keep = false, bool _header=false, bool _overwrite = false
    eoFileMonitor* file_monitor = new eoFileMonitor( plan_file, "\n", false, false, true);
    state.storeFunctor(file_monitor );
    file_monitor.add( *stat_plan );
    checkpoint.add( *file_monitor );
#endif

#endif // NDEBUG
}



template <class EOT>
eoCheckPoint<EOT> & do_make_checkpoint_op( eoContinue<EOT> & continuator,
        eoParser &
#ifndef NDEBUG // avoid warning about unused variable
        parser
#endif
        ,
        eoState & state, eoPop<EOT> &
#ifndef NDEBUG
        pop
        , eoEvalFuncCounter<EOT> & eval_counter
#endif
        , moeoArchive<EOT>& archive
)
{
    // attach a continuator to the checkpoint
    // the checkpoint is here to get some stat during the search
    eoCheckPoint<EOT> * checkpoint = new eoCheckPoint<EOT>( continuator );
    state.storeFunctor( checkpoint );
/*
#ifndef NDEBUG
    eoOStreamMonitor* clog_monitor = new eoOStreamMonitor( std::clog, DAEX_LOG_SEP, 1, ' ', true, " = ");
    state.storeFunctor( clog_monitor );

    eoGenCounter* gen_count = new eoGenCounter( 0, "Gen" );
    state.storeFunctor( gen_count );

    eoTimeCounter* time_count = new eoTimeCounter();
    state.storeFunctor( time_count );

    FeasibleRatioStat<EOT>* feasible_stat = new FeasibleRatioStat<EOT>( "Fsbl%" );
    state.storeFunctor( feasible_stat );

    eoStat<EOT,std::string>& asize_stat = make_dual_stat< eoAverageSizeStat<EOT> >( "AvSz", state );

    if( eo::log.getLevelSelected() >= eo::progress ) {

        // compute stat at each generation
        checkpoint->add( *time_count );
        checkpoint->add( *gen_count );
        checkpoint->add( *feasible_stat );
        checkpoint->add( asize_stat );
#ifndef SINGLE_EVAL_ITER_DUMP
        clog_monitor->add( eval_counter );
#endif
        clog_monitor->add( *time_count );
        clog_monitor->add( *gen_count );
        clog_monitor->add( asize_stat );
        clog_monitor->add( *feasible_stat );

        // the checkpoint should call the monitor at every generation
        checkpoint->add( *clog_monitor );
    }
    //state.formatJSON("dae_state");


    add_stats_multi( *checkpoint, *clog_monitor, state, pop, archive, parser );

    //add_stats_mono( *checkpoint, *clog_monitor, state );


    // pour plus d'output (recopiés de do/make_checkpoint)
    // un state, pour sauver l'état courant
    state.registerObject(parser);
    state.registerObject(pop);
    //state.registerObject(eo::rng);


    unsigned int out_save_freq = parser.valueOf<unsigned int>("out-save-freq");
        eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "out-save-freq" << out_save_freq << std::endl;

    std::string out_dir = parser.valueOf<std::string>("out-dir");
        eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "out-dir" << out_dir << std::endl;

    bool out_dir_erase = parser.valueOf<bool>("out-dir-erase");
        eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "out-dir-erase" << out_dir_erase << std::endl;

    bool dirOK = testDirRes( out_dir, out_dir_erase ) ;
    if( ! dirOK ) {
        eo::log << eo::warnings << "WARNING: Cannot write to " << out_dir  << std::endl;
    }

    unsigned freq = out_save_freq>0 ? out_save_freq : std::numeric_limits<unsigned int>::max();
    std::string stmp = out_dir + "/generation_";

    eoCountedStateSaver* state_saver = new eoCountedStateSaver(freq, state, stmp, true, "sav", -1);
    state.storeFunctor( state_saver );

    checkpoint->add( *state_saver );
#endif // NDEBUG
*/
    return *checkpoint;
}

////////////

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
    std::string dirName =  _parser.valueOf<std::string>("resDir");
    // shoudl we empty it if exists
    bool eraseParam = _parser.valueOf<bool>("eraseDir");
    
    bool dirOK = testDirRes( dirName, eraseParam ) ;
    if( ! dirOK ) {
        eo::log << eo::warnings << "WARNING: Cannot write to " << dirName  << std::endl;
    }
    
    

    // Dump of the whole population
    //-----------------------------
    bool printPop = _parser.valueOf<bool>("printPop");
    eoSortedPopStat<MOEOT> * popStat;
    if(printPop)
    {
        popStat = & _state.storeFunctor(new eoSortedPopStat<MOEOT>);
        checkpoint.add(*popStat);
    }
    
    bool printPlan = _parser.valueOf<bool>("printPlan");
    if (printPlan) // we do want plan dump
    {
        eoSortedPlanStat<MOEOT> * planStat = & _state.storeFunctor(new eoSortedPlanStat<MOEOT>);
        checkpoint.add(*planStat);
    }
    
   
    //////////////////////////////////
    // State savers
    //////////////////////////////
    // feed the state to state savers
    // save state every N  generation
    unsigned int freq = _parser.valueOf<unsigned int>("saveFrequency");
    if(freq > 0)
    {
#ifdef _MSVC
        std::string stmp = dirName + "\generation_";
#else
        std::string stmp = dirName + "/generation_";
#endif 
        eoCountedStateSaver* state_saver = new eoCountedStateSaver(freq, _state, stmp, true, "sav", -1);
        _state.storeFunctor( state_saver );

        checkpoint.add( *state_saver );
    }
    
    // save state every T seconds
    unsigned int saveTimeIntervalParam = _parser.valueOf<unsigned int>("saveTimeInterval");
    if (saveTimeIntervalParam > 0)
    {
#ifdef _MSVC
        std::string stmp = dirName + "\time";
#else
        std::string stmp = dirName + "/time";
#endif
      eoTimedStateSaver *stateSaver2 = new eoTimedStateSaver(saveTimeIntervalParam, _state, stmp);
      _state.storeFunctor(stateSaver2);
      checkpoint.add(*stateSaver2);
    }
    
    ///////////////////
    // Archive
    //////////////////
    // update the archive every generation
    bool updateArch = _parser.valueOf<bool>("updateArch");
    if (updateArch)
    {
        moeoArchiveUpdater < MOEOT > * updater = new moeoArchiveUpdater < MOEOT > (_archive, _pop);
        _state.storeFunctor(updater);
        checkpoint.add(*updater);
    }
    
    // store the objective vectors contained in the archive every generation
    bool storeArch = _parser.valueOf<bool>("storeArch");
  
    bool printArch = _parser.valueOf<bool>("printArch"); 
  
    if (storeArch)
    {
#ifdef _MSVC
        std::string stmp = dirName + "\arch";
#else
        std::string stmp = dirName + "/arch";
#endif
          
      moeoArchiveObjectiveVectorSavingUpdater < MOEOT > * save_updater = new moeoArchiveObjectiveVectorSavingUpdater < MOEOT > (_archive, stmp, printArch);
      _state.storeFunctor(save_updater);
      checkpoint.add(*save_updater);
    }
    
      
    unsigned int  saveIntervalArch = _parser.getORcreateParam((unsigned int)(0), "saveIntervalArch", "Save the archive's objective vectors every T seconds (0 or absent = never)", '\0', "Output").value();
  
  if (saveIntervalArch>0)
    {

#ifdef _MSVC
      std::string stmp = dirName + "\archTime";
#else
      std::string stmp = dirName + "/archTime";
#endif
        
      moeoArchiveObjectiveVectorTimeSavingUpdater < MOEOT > * saveTimeUpdater = new moeoArchiveObjectiveVectorTimeSavingUpdater < MOEOT > (_archive, stmp, saveIntervalArch, true);
      _state.storeFunctor(saveTimeUpdater);
      checkpoint.add(*saveTimeUpdater);
    }
    
  ///////////////////
  // Pop
  //////////////////
  // update the pop vectors every generation    
  
    unsigned int saveIntervalPopVectors = _parser.valueOf<unsigned int>("saveIntervalPopVectors");
  
   bool storePopVectors = _parser.getORcreateParam(false, "storePopVectors", "Store the pop's objective vectors at each gen.", '\0', "Output").value();
  
  bool printPopVectors = _parser.getORcreateParam(false, "printPopVectors", "Print the pop vectors at each gen.", '\0', "Output").value(); 

    if (saveIntervalPopVectors > 0)
    {

#ifdef _MSVC
      std::string stmp = dirName + "\popTime";
#else
      std::string stmp = dirName + "/popTime";
#endif 

    moeoPopObjectiveVectorTimeSavingUpdater< MOEOT > * save_popvec_updater = new moeoPopObjectiveVectorTimeSavingUpdater < MOEOT > (_pop, stmp, saveIntervalPopVectors, true);
      _state.storeFunctor(save_popvec_updater);
      checkpoint.add(*save_popvec_updater);
    }
  
    if (storePopVectors)
    {

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
      
#ifdef _MSVC
      std::string stmp = dirName + "\contribution_";
#else
      std::string stmp = dirName + "/contribution_";
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
      
#ifdef _MSVC
      std::string stmp = dirName + "\entropy_";
#else
      std::string stmp = dirName + "/entropy_";
#endif
      moeoEntropyMetric < ObjectiveVector > * entropy = new moeoEntropyMetric < ObjectiveVector >;
      moeoBinaryMetricSavingUpdater < MOEOT > * entropy_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*entropy, _archive, stmp);
      _state.storeFunctor(entropy_updater);
      checkpoint.add(*entropy_updater);
    }
    
     bool hyper = _parser.getORcreateParam(false, "hypervolume", "Store the hypervolume of the archive at each gen.", '\0', "Output").value();
  if (hyper)
    {
     
#ifdef _MSVC
      std::string stmp = dirName + "\hypervolume_";
#else
      std::string stmp = dirName + "/hypervolume_";
#endif
     moeoHyperVolumeDifferenceMetric <ObjectiveVector> *hypervolume = new moeoHyperVolumeDifferenceMetric <ObjectiveVector> (true,1.1);
     moeoBinaryMetricSavingUpdater < MOEOT > * hypervolume_updater = new moeoBinaryMetricSavingUpdater < MOEOT > (*hypervolume, _archive, stmp);
     _state.storeFunctor(hypervolume_updater);
      checkpoint.add(*hypervolume_updater);
    }
    
     bool epsi = _parser.getORcreateParam(false, "EpsilonAdditive", "Store the Epsilon Additive of the archive at each gen.", '\0', "Output").value();
  if (epsi)
    {
      
#ifdef _MSVC
      std::string stmp = dirName + "\epsilon_";
#else
      std::string stmp = dirName + "/epsilon_";
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
    
     
      
     
     /*bool printStatsParam = _parser.getORcreateParam(true, "printStats", "Print Best/avg/feasible every gen.", '\0', "Output").value();
      
     
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

} // namespace daex

#endif /*MAKE_CHECKPOINT_DAEMOEO_H_*/
