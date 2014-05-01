#ifndef _MAKE_CHECKPOINT_PARAM_H_
#define	_MAKE_CHECKPOINT_PARAM_H_

#include "../utils/cli.h"

namespace daex {

void do_make_checkpoint_param(eoParser &parser)
{

    std::string dirName =  parser.getORcreateParam(std::string("Res"), "resDir", "Directory to store DISK outputs", '\0', "Output").value();
  
    bool eraseParam = parser.getORcreateParam(true, "eraseDir", "erase files in dirName if any", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "eraseDir" << eraseParam << std::endl;
  
    bool printPop = parser.getORcreateParam(false, "printPop", "Print sorted pop. every gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printPop" << printPop << std::endl;
       
    bool printPlan = parser.getORcreateParam(false, "printPlan", "Print sorted plan. every gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printPlan" << printPlan << std::endl;
 
    unsigned int saveFrequencyParam = parser.createParam((unsigned int)(0), "saveFrequency", "Save every F generation (0 = only final state, absent = never)", '\0', "Persistence" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "saveFrequency" << saveFrequencyParam << std::endl;

    unsigned int saveTimeIntervalParam = parser.getORcreateParam((unsigned int)(0), "saveTimeInterval", "Save every T seconds (0 or absent = never)", '\0',"Persistence" ).value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "saveTimeInterval" << saveTimeIntervalParam << std::endl;
 
    bool updateArch = parser.getORcreateParam(true, "updateArch", "Update the archive at each gen.", '\0', "Evolution Engine").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "updateArch" << updateArch << std::endl;
 
    bool storeArch = parser.getORcreateParam(false, "storeArch", "Store the archive's objective vectors at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "storeArch" << storeArch << std::endl;
  
    bool printArch = parser.getORcreateParam(false, "printArch", "Print the archive at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printArch" << printArch << std::endl;
      
    unsigned int saveIntervalArch = parser.getORcreateParam((unsigned int)(0), "saveIntervalArch", "Save the archive's objective vectors every T seconds (0 or absent = never)", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "saveIntervalArch" << saveIntervalArch << std::endl;
  
    bool printIntervalArch = parser.getORcreateParam(false, "printIntervalArch", "Print the archive at each time interval", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printIntervalArch" << printIntervalArch << std::endl;
  
    bool storePopVectors = parser.getORcreateParam(false, "storePopVectors", "Store the pop's objective vectors at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "storePopVectors" << storePopVectors << std::endl;
    
    unsigned int saveIntervalPopVectors = parser.getORcreateParam((unsigned int)(0), "saveIntervalPopVectors", "Store the pop's objective vectors  every T seconds (0 or absent = never).", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "saveIntervalPopVectors" << saveIntervalPopVectors << std::endl;
  
    bool printPopVectors = parser.getORcreateParam(false, "printPopVectors", "Print the pop vectors at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printPopVectors" << printPopVectors << std::endl;
  
    bool cont = parser.getORcreateParam(false, "contribution", "Store the contribution of the archive at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "contribution" << cont << std::endl;
  
    bool ent = parser.getORcreateParam(false, "entropy", "Store the entropy of the archive at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "entropy" << ent << std::endl;
  
    bool hyper = parser.getORcreateParam(false, "hypervolume", "Store the hypervolume of the archive at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "hypervolume" << hyper << std::endl;
   
    bool epsi = parser.getORcreateParam(false, "EpsilonAdditive", "Store the Epsilon Additive of the archive at each gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "EpsilonAdditive" << epsi << std::endl;

    bool printStatsParam = parser.getORcreateParam(true, "printStats", "Print Best/avg/feasible every gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printStats" << printStatsParam << std::endl;
    
    bool printBestParam  = parser.getORcreateParam(true, "printBestStat", "Print Best/avg// every gen.", '\0', "Output").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "printBestStat" << printBestParam << std::endl;

}

} // namespace daex

#endif // _MAKE_CHECKPOINT_PARAM_H_
