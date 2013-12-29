// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// eoCombinedEval.h
//-----------------------------------------------------------------------------

#ifndef _eoCombinedEval_h
#define _eoCombinedEval_h

#include <eoEvalFunc.h>

/**
    Combined EVAL: a proportional recombination of eoEvalFunc objects

    @ingroup Evaluators
*/
template< class EOT>
class eoCombinedEval: public eoEvalFunc<EOT> {
public:

  /** Ctor, make sure that at least one eoEvalFunc is present */
  eoCombinedEval(eoEvalFunc<EOT>& _eval, double _rate)
    : eoEvalFunc<EOT> ()
  {
    evaluators.push_back(&_init);
    rates.push_back(_rate);
  }

  void add(eoEvalFunc<EOT> & _eval, double _rate, bool _verbose)
  {
      eo::log << eo::warnings << "WARNING: the use of the verbose parameter in eoCombinedEval::add is deprecated and will be removed in the next release." << std::endl;
      add( _eval, _rate );
  }

  /** The usual method to add objects to the combination
   */
  void add(eoEval<EOT> & _eval, double _rate)
  {
    evaluators.push_back(&_eval);
    rates.push_back(_rate);
    // compute the relative rates in percent - to warn the user!
      printOn( eo::log << eo::logging );
  }

  /** outputs the operators and percentages */
  virtual void printOn(std::ostream & _os)
  {
    double total = 0;
    unsigned i;
    for (i=0; i<evaluators.size(); i++)
      total += rates[i];
    _os << "In " << className() << "\n" ;
    for (i=0; i<evaluators.size(); i++)
      _os << evaluators[i]->className() << " with rate " << 100*rates[i]/total << " %\n";
  }

  /** Performs the Eval: chooses among all evaluators
   * using roulette wheel on the rates
   */
  virtual void operator() ( EOT & _eo )
  {
    unsigned what = rng.roulette_wheel(rates); // choose one op
    (*evaluators[what])(_eo);            // apply it
    return;
  }

  virtual std::string className(void) const { return "eoCombinedEval"; }

private:
std::vector<eoEvalFunc<EOT>*> evaluators;
std::vector<double> rates;
};

#endif
