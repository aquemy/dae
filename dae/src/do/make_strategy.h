#ifndef _MAKE_STRATEGY_PARAM_H_
#define	_MAKE_STRATEGY_PARAM_H_

#include "../utils/cli.h"

namespace daex {

void do_make_strategy_param(eoParser &parser)
{
    std::string level = parser.createParam( (std::string)"Pop", "strat-level", "Level for strategy (Pop,Indi,Goal)", 'l', "Strategy").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "strat-level" << level << std::endl;

    std::string indicator = parser.createParam( (std::string)"DeltaPlus", "strat-indicator", "Measure the evolution between to evaluation (Hypervolume, Epsilon, DeltaPlus, DeltaProd, DeltaExp)", 'F', "Strategy").value();
    eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "strat-indicator" << indicator << std::endl;

   bool effect = parser.createParam( (bool)true, "effect-estimation", "Estimate the effect of objective to ponderate quality.", 'e', "Strategy").value();
   eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "effect-estimation" << effect << std::endl;
   
   std::string quality = parser.createParam( (std::string)"AQA", "quality-assessment", "Quality assessment strategy (AQA : average quality, EQA : extreme value)", ' ', "Strategy").value();
   eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "quality-assessment" << quality << std::endl;
   
   std::string update = parser.createParam( (std::string)"PM", "strat-update", "Quality update method (PM : probability matching, AP : adaptive pursuit)", 'u', "Strategy").value();
   eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "strat-update" << update << std::endl;
   
   bool jump = parser.createParam( (bool)true, "strat-jump", "Jump detection in average quality using Page-Hinkley test.", 'j', "Strategy").value();
   eo::log << eo::logging << FORMAT_LEFT_FILL_W_PARAM << "strat-jump" << jump << std::endl;
}


} // namespace daex

#endif // _MAKE_STRATEGY_H_
