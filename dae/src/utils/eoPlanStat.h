
//-----------------------------------------------------------------------------
// eoPlanStat.h
// (c) Mostepha Redouane Khouadjia

#ifndef _eoPlanStat_h
#define _eoPlanStat_h

#include <utils/eoStat.h>
 
template <class EOT>
class eoPlanStat : public eoStat<EOT, std::string>
{
public:

    using eoStat<EOT, std::string>::value;

  /** default Ctor, void std::string by default, as it appears
      on the description line once at beginning of evolution. and
      is meaningless there. _howMany defaults to 0, that is, the whole
          population*/
   eoPlanStat(unsigned _howMany = 0, std::string _desc ="")
         : eoStat<EOT, std::string>("", _desc), combien( _howMany) {}

/** Fills the value() of the eoParam with the dump of the population.
Adds a \n before so it does not get mixed up with the rest of the stats
that are written by the monitor it is probably used from.
*/
void operator()(const eoPop<EOT>& _pop)
{
  value() = "\n# ====== pop dump =====\n";
  unsigned howmany=combien?combien:_pop.size();
  for (unsigned i = 0; i < howmany; ++i)
  {
      std::ostringstream os;
      os << _pop[i].plan() << std::endl;

      // paranoid:
      value() += os.str();
  }
}

private:
  unsigned combien;
};


template <class EOT>
class eoSortedPlanStat : public eoSortedStat<EOT, std::string>
{
public:

    using eoSortedStat<EOT, std::string>::value;

    /** default Ctor, void std::string by default, as it appears on
        the description line once at beginning of evolution. and is
        meaningless there _howMany defaults to 0, that is, the whole
        population
    */
    eoSortedPlanStat(unsigned _howMany = 0, std::string _desc ="")
        : eoSortedStat<EOT, std::string>("", _desc) , combien( _howMany)
        {}

    /** Fills the value() of the eoParam with the dump of the
        population. Adds a \n before so it does not get mixed up with
        the rest of the stats that are written by the monitor it is
        probably used from.
    */
    void operator()(const std::vector<const EOT*>& _pop)
        {
    value() = "";                  // empty
    unsigned howMany=combien?combien:_pop.size();
    for (unsigned i = 0; i < howMany; ++i)
      {
        std::ostringstream os;
        os << (*_pop[i]).plan_copy()<< std::endl;

        // paranoid:
        value() += os.str();
      }
  }
private:
  unsigned combien;
};

#endif