#ifndef PLANNING_STATE_H_
#define PLANNING_STATE_H_

enum PlanningState
{
    Feasible,
    UnfeasibleIntermediate,
    UnfeasibleFinal,
    UnfeasibleTooLong,
    Unfeasible // Default unfeasible state should be at the end to handle it easily
};

#endif
