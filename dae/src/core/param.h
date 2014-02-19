#ifndef _DAEX_PARAM_
#define _DAEX_PARAM_

namespace daex {

class Param
{
public :

    Param()
    {
    
    }

protected :

    // General parameters
    std::string domain;
    std::string instance;
    std::string plan_file;
    unsigned int pop_size;
    unsigned int maxruns;
    // Problem
    bool is_sequential;
   
    // b_max estimation
    bool insemination;

    // Misc
    std::string plan_file;

    unsigned int l_max_init_coef;
    unsigned int l_min;  
    
    // Variation
    unsigned int radius;
    double proba_change;
    double proba_del_atom;
    double w_delgoal;
    double w_addgoal;
    double w_delatom;
    double w_addatom;
    unsigned int maxtry_candidate;
    unsigned int maxtry_mutex;
    double proba_cross;
    double proba_mut;
    
    // Eval
    
    std::string objective; // MO
	unsigned int b_max_init;
    unsigned int fitness_weight;
    unsigned int fitness_penalty;
    
    
    unsigned int b_max_fixed;
    double b_max_last_weight;
    double b_max_quantile;
    double lenght_weigth;
    double cost_weigth; 	 
    double makespan_max_weigth;
 	double  makespan_add_weigth;
	unsigned int astar_weight;
	bool rand_seed ;
  
    double b_max_increase_coef;
    double b_max_ratio;
    
    // MO - EA
    std::string fitnessParam;                    
    std::string indicatorParam;
    eoValueParam<eoParamParamType> diversityParam;
    std::string comparatorParam;
    std::string replacementParam;
    eoValueParam <eoHowMany> offspringRateParam;
    
    // Continue
    eoValueParam<unsigned> maxGenParam;
    eoValueParam<unsigned> steadyGenParam;
    eoValueParam<unsigned> minGenParam;
    eoValueParam<unsigned long> maxEvalParam;
    eoValueParam<unsigned long> maxTimeParam;
    eoValueParam<bool> ctrlCParam;
    
    // Checkpoint
    std::string dirName;
    eoValueParam<bool> eraseParam;
    bool printPop;
    bool printPlan;
    
    
    unsigned int out_save_freq;
    std::string out_dir;
    bool out_dir_erase;
    
    // MO - Evolution Engine
    // IBEA
    std::string & indicatorParam; // Epsilon - Hypervolume
    double kappa;
    double rho;
    
    // General
    eoValueParam<unsigned int> param_seed;
    
    // MPI
    unsigned int multistart_workers;
    unsigned int eval_workers;


};

namespace mo {

}

namespace moeo {

}

#endif // _DAEX_PARAM_
