#ifndef _MAKE_INIT_PARAM_H_
#define	_MAKE_INIT_PARAM_H_

#include "../utils/cli.h"

namespace daex {

void do_make_init_param(eoParser &parser)
{
   parser.createParam( (unsigned int)2, "lmax-initcoef", "l_max will be set to the size of the chrono partition * this coefficient", 'N', "Initialization" );
            
   parser.createParam( (unsigned int)1, "lmin", "Minimum number of goals in a decomposition", 'M', "Initialization");

}

} // namespace daex

#endif // _MAKE_INIT_PARAM_H_
