#ifndef _MAKE_CHECKPOINT_PARAM_H_
#define	_MAKE_CHECKPOINT_PARAM_H_

#include "../utils/cli.h"

namespace daex {

void do_make_checkpoint_param(eoParser &parser)
{

    std::string dirName =  parser.getORcreateParam(std::string("Res"), "resDir", "Directory to store DISK outputs", '\0', "Output").value();
  
    bool eraseParam = parser.getORcreateParam(true, "eraseDir", "erase files in dirName if any", '\0', "Output").value();
  
    bool printPop = parser.getORcreateParam(false, "printPop", "Print sorted pop. every gen.", '\0', "Output").value();
       
    bool printPlan = parser.getORcreateParam(false, "printPlan", "Print sorted plan. every gen.", '\0', "Output").value();
 
    unsigned int saveFrequencyParam = parser.createParam((unsigned int)(0), "saveFrequency", "Save every F generation (0 = only final state, absent = never)", '\0', "Persistence" ).value();

    unsigned int saveTimeIntervalParam = parser.getORcreateParam((unsigned int)(0), "saveTimeInterval", "Save every T seconds (0 or absent = never)", '\0',"Persistence" ).value();
 
    bool updateArch = parser.getORcreateParam(true, "updateArch", "Update the archive at each gen.", '\0', "Evolution Engine").value();
 
    bool storeArch = parser.getORcreateParam(false, "storeArch", "Store the archive's objective vectors at each gen.", '\0', "Output").value();
  
    bool printArch = parser.getORcreateParam(false, "printArch", "Print the archive at each gen.", '\0', "Output").value(); 
      
    unsigned int saveIntervalArch = parser.getORcreateParam((unsigned int)(0), "saveIntervalArch", "Save the archive's objective vectors every T seconds (0 or absent = never)", '\0', "Output").value();
  
    bool printIntervalArch = parser.getORcreateParam(false, "printIntervalArch", "Print the archive at each time interval", '\0', "Output").value();  
  
    bool storePopVectors = parser.getORcreateParam(false, "storePopVectors", "Store the pop's objective vectors at each gen.", '\0', "Output").value();
    
    unsigned int saveIntervalPopVectors = parser.getORcreateParam((unsigned int)(0), "saveIntervalPopVectors", "Store the pop's objective vectors  every T seconds (0 or absent = never).", '\0', "Output").value();
  
    bool printPopVectors = parser.getORcreateParam(false, "printPopVectors", "Print the pop vectors at each gen.", '\0', "Output").value(); 
  
    bool cont = parser.getORcreateParam(false, "contribution", "Store the contribution of the archive at each gen.", '\0', "Output").value();
  
    bool ent = parser.getORcreateParam(false, "entropy", "Store the entropy of the archive at each gen.", '\0', "Output").value();
  
    bool hyper = parser.getORcreateParam(false, "hypervolume", "Store the hypervolume of the archive at each gen.", '\0', "Output").value();
   
    bool epsi = parser.getORcreateParam(false, "EpsilonAdditive", "Store the Epsilon Additive of the archive at each gen.", '\0', "Output").value();

    bool printStatsParam = parser.getORcreateParam(true, "printStats", "Print Best/avg/feasible every gen.", '\0', "Output").value();
    
    bool printBestParam  = parser.getORcreateParam(true, "printBestStat", "Print Best/avg// every gen.", '\0', "Output").value();

}

} // namespace daex

#endif // _MAKE_CHECKPOINT_PARAM_H_
