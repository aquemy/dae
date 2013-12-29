// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// eoFitContinue.h
// (c) Maarten Keijzer, GeNeura Team, 1999, 2000
/*
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: todos@geneura.ugr.es, http://geneura.ugr.es
 */
//-----------------------------------------------------------------------------

#ifndef _eoFitContinue_dae_h
#define _eoFitContinue_dae_h

#include <eoContinue.h>
#include <utils/eoLogger.h>
#include <eoFitContinue.h>
#include <daex.h>
/**
Continues until the optimum fitness level is reached.

All types which derive from eoScalarFitness is able to compare well via the operator override ( <, >, <=, ...)

 @ingroup Continuators
*/


 

template<> bool eoFitContinue<daex::Decomposition>::operator() ( const
eoPop<daex::Decomposition>& _pop )
//bool eoFitContinue<daex::Decomposition>::operator() ( const eoPop<daex::Decomposition>& _pop )
    {
     
    daex::Decomposition::Fitness  bestCurrentFitness = _pop.best_element().fitness() ;
    
        if (bestCurrentFitness >=  eoFitContinue<daex::Decomposition>::optimum)
            {
                eo::log << eo::logging << "STOP in eoFitContinue: Best fitness has reached " <<
                    bestCurrentFitness << "\n";
                return false;
            }
        return true;
    }

 

#endif
