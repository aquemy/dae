 
#ifndef MAKE_AGGREGATION_MOEO_H_
#define MAKE_AGGREGATION_MOEO_H_

#include <stdlib.h>
#include <eoContinue.h>
#include <eoEvalFunc.h>
#include <eoGeneralBreeder.h>
#include <eoGenOp.h>
#include <utils/eoParser.h>
#include <utils/eoState.h>

#include <algo/moeoEA.h>
#include <algo/moeoEasyEA.h>
#include <algo/moeoIBEA.h>

namespace daex {

void do_make_aggregation_param(eoParser &parser)
{
    double  alpha = parser.createParam( (double)0.5, "alpha",
        "Aggregation param for the fitness func. (alp.* makespan + (1-alp.) (cost/risk))", 'x', "Evaluation" ).value();

 	double minObj1 = parser.createParam((double)0.0, "minObj1", "minimum value of first Objective",'\0',"Evaluation").value();

	double maxObj1 = parser.createParam((double)10e3, "maxObj1", "maximum value of first Objective",'\0',"Evaluation").value();

	double minAddObj2 = parser.createParam((double)0.0, "minAddObj2", "minimum value of second Objective (cost case)",'\0',"Evaluation").value();

	double maxAddObj2 = parser.createParam((double)10e3, "maxAddObj2","minimum value of second Objective (cost case)",'\0', "Evaluation").value();

	double minMaxObj2 = parser.createParam((double)0.0, "minMaxObj2","minimum value of second Objective (risk case))", '\0',"Evaluation").value();

	double maxMaxObj2 = parser.createParam((double)10e3, "maxMaxObj2", "maximum value of second Objective (risk case)", '\0',"Evaluation").value();
     	 
    bool normalize = parser.getORcreateParam(true, "normalize", "Normalize the objective function before the evaluation step",'n', "Evaluation").value();

	 std::string strategy_level = parser.createParam( (std::string) "pop", "strategy", "Strategy to adapt for Yahsp search (pop,indiv,goal)", '\0', "Evaluation").value();
	  
    double  proba_strateg_indiv= parser.createParam((double)0.0, "proba_indiv", 
	   "Probabilty of  mutation for  yahsp strategies on inidividual level", 'f', "Evaluation").value();
	   
    double  proba_strateg_goal= parser.createParam((double)0.0, "proba_goal", 
	   "Probabilty of   mutation for yahsp strategies on goal level", 'u', "Evaluation").value();

}


} // namespace daex

#endif /*MAKE_AGGREGATION_MOEO_H_*/
