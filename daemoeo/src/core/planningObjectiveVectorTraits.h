
#ifndef PLANNINGOBJECTIVEVECTORTRAITS_H_
#define PLANNINGOBJECTIVEVECTORTRAITS_H_

//#include <moeo>
#include <core/moeoObjectiveVectorTraits.h>

/**
 * Definition of the objective vector traits for multi-objective  for planning problems
 */
class PlanningObjectiveVectorTraits : public moeoObjectiveVectorTraits
  {
  public:
  
  
    //PlanningObjectiveVectorTraits();

    /**
     * Returns true if the _ith objective have to be minimzed
     * @param _i index of the objective
     */
    static bool minimizing (int _i);


    /**
     * Returns true if the _ith objective have to be maximzed
     * @param _i index of the objective
     */
    static bool maximizing (int _i);


    /**
     * Returns the number of objectives
     */
    static unsigned int nObjectives ();

  };

#endif /*PLANNINGOBJECTIVEVECTORTRAITS_H_*/
