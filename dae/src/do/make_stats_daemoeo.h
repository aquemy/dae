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
void  do_make_stats(eoParser& _parser, eoState& _state, eoCheckPoint<EOT>& _checkpoint, eoPop<EOT> & _pop)
{
  std::string plan_file = _parser.valueOf<std::string>("plan-file");
  
 //eoValueParam<unsigned>& popSize = _parser.getORcreateParam(unsigned(20), "popSize", "Population Size", 'P', "Evolution Engine");

     // append the plans in a file
    // std::string _filename, std::string _delim = " ", bool _keep = false, bool _header=false, bool _overwrite = false
  
 eoFileMonitor *file_monitor = new eoFileMonitor ( plan_file, "\n", false, false, true);
    
 _state.storeFunctor(file_monitor);
     
  //file_monitor-> add(_pop.best_element().fitness());

  _checkpoint.add( *file_monitor );

}



#endif
