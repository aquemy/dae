#include "planningObjectiveVectorTraits.h"

// the moeoObjectiveVectorTraits : minimizing 2 objectives

using namespace std;

bool PlanningObjectiveVectorTraits::minimizing (int _i)
{
  // minimizing both
  return true;
}

bool PlanningObjectiveVectorTraits::maximizing (int _i)
{
  // maximizing both
  return false;
}

unsigned int PlanningObjectiveVectorTraits::nObjectives ()
{
  // 2 objectives
  return 2;
}
