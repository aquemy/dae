#ifndef _MAKE_CONTINUE_PARAM_H_
#define	_MAKE_CONTINUE_PARAM_H_

#include "../utils/cli.h"

namespace daex {

void do_make_continue_param(eoParser &parser)
{

    parser.createParam(unsigned(100), "maxGen", "Maximum number of generations",'G',"Stopping criterion");
    parser.createParam(unsigned(100), "steadyGen", "Number of generations with no improvement",'s', "Stopping criterion");
    parser.createParam(unsigned(0), "minGen", "Minimum number of generations",'g', "Stopping criterion");
    parser.createParam((unsigned long)0, "maxEval", "Maximum number of evaluations (0 = none)", 'E', "Stopping criterion");
    parser.createParam((unsigned long)(0), "maxTime", "Maximum running time in seconds (0 = none)", 'T', "Stopping criterion");
 
#ifndef _MSC_VER
    // the CtrlC interception (Linux only I'm afraid)
    parser.createParam(false, "CtrlC", "Terminate current generation upon Ctrl C",'C', "Stopping criterion");
#endif

}

} // namespace daex

#endif // _MAKE_CONTINUE_PARAM_H_
