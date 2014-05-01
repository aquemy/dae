#ifndef __DAEX_INIT_H__
#define __DAEX_INIT_H__

#include <map>
#include <algorithm>

#include "core/decomposition.h"
#include "utils/pddl_load.h"
#include "utils/utils.h"
#include <iomanip>
#include <algorithm>

namespace daex {

template<class EOT = daex::Decomposition>
class Init : public eoInit<EOT> //Decomposition>
{

public:

    // TODO autoriser les décomposition vides ? (_min_nb = 0 )
    Init(const ChronoPartition & times, StrategyInit& _stratInit, unsigned int l_max_init_coef = 2, unsigned int min_nb = 1) :
        _times(times), 
        _min_nb(min_nb), 
        _l_max_init_coef(l_max_init_coef), 
        _l_max(20),
        stratInit(_stratInit)
    {
        assert( ! _times.empty() );

        // TODO valider le choix arbitraire du times * 2 pour le l_max
        _l_max = times.size() * _l_max_init_coef;
    };

    void operator()( EOT & decompo )
    {
        decompo.clear();

        // copie temporaire des temps au plus tot
        //_times_tmp = _times;
        std::list<TimeVal> _times_tmp;

        ChronoPartition::const_iterator it, begin = _times.begin();
        std::advance(begin, 1); // We suppose that the first key is date=0 so as to skip it, advance by one is enough. (Hyp : STL maps are implemented as red black trees so that it is garanteed to be ordered).
        for( it = begin; it != _times.end(); it++) 
        {
            // ne copie que les clefs
            _times_tmp.push_back( it->first );
        }


    // JACK n'utilise pas de paramètre min_nb, le tirage se fait toujours entre 1 et la taille de la partition
    // nombre de décompositions à produire
    unsigned int decompo_nb = std::min( 
            _min_nb + rng.random( _times_tmp.size() + 1 - _min_nb ),
            _l_max 
        );

    std::vector<TimeVal> t_candidates;
    t_candidates.reserve( decompo_nb );

    // JACK effectue le tirage des dates _avec remise_, il essaye au plus 11*size fois de tirer d'autres dates que celles déjà choisies 
    // tire des dates au hasard dans la chrono partition
    // tirage _sans remise_
    ///
    size_t i= 0;
    
    while ( i < decompo_nb && _times_tmp.size()>0) 
    {
        // supprime une date au hasard, car on ne veut pas la tirer plusieurs fois
        // et garde sa valeur dans t
        std::list<TimeVal>::iterator it = _times_tmp.begin();
        std::advance( it, rng.random( _times_tmp.size() ) );

        t_candidates.push_back(*it); 

        _times_tmp.erase( it );
	
 	    i++;
    }

    // trie le vecteur
    std::sort( t_candidates.begin(), t_candidates.end() );

#ifndef NDEBUG
    assert( t_candidates.front() < t_candidates.back() || t_candidates.front() == t_candidates.back() );
    eo::log << eo::xdebug << "\t\tDecomposition on " << std::right << std::setfill(' ') << std::setw(3) << t_candidates.size() << " partition dates, date(#atoms):";
    unsigned int nb_goals = 0;
#endif

    // créé et ajoute à la décomposition des goals aléatoirement construits avec des atomes non-mutex
    for(std::vector<TimeVal>::iterator idate = t_candidates.begin(), iend = t_candidates.end(); 
            idate != iend; idate++ ) 
    {

        // atomes tirés au hasard parmi les nomutex à la date t
        assert(_times.at(*idate).size() > 0);

        // FIXME random_subset semble retourner tous les atomes existants, et pas un sous-ensemble
        Goal goal = random_subset(nomutex(_times.at(*idate)));
        goal.setStrategy(stratInit.operator()<Goal>());
/* Already checked at the beginning of an eval
#ifndef NDEBUG
        eo::log << eo::xdebug << std::endl << "Check if atoms are no mutex...";
        eo::log.flush();
        // Check that the resulting list effectively contains no atoms that are pairwise mutualy exlusives    
        assert_noduplicate( goal.begin(), goal.end() );
        assert_nomutex( goal.begin(), goal.end() );
        eo::log << eo::xdebug << "OK" << std::endl;
#endif
*/
#ifndef NDEBUG
        eo::log << eo::xdebug
            << "\t" << std::right << std::setfill(' ') << std::setw(3) 
            << *idate 
            << "(" 
            << goal.size() 
            //<< std::left << std::setfill(' ') << std::setw(3) 
            << ")";
        nb_goals++;

        eo::log << eo::xdebug << std::endl << "Check atom's earliest start times consistency...";
        eo::log.flush();
        // assert that any atom in the goal have the same earliest start date (Fluent:init, in CPT)
        for( Goal::iterator iatom = goal.begin(), end = goal.end(); iatom != end; ++iatom ) {
            assert( (*iatom)->fluent()->init == goal.earliest_start_time() );
        }
        eo::log << eo::xdebug << "OK" << std::endl;
#endif

        // l'insère dans la décomposition
        decompo.push_back(goal);
    } // for idate in t_candidates
    decompo.invalidate();
    
    decompo.setStrategy(stratInit.operator()<EOT >());
} // 

    void l_max( unsigned int l ) { _l_max = l; }
    unsigned int l_max() const { return _l_max; }

protected:

    const ChronoPartition & _times;

   // TODO faire des tests pour vérifier si doit etre à 0 ou à 1 par défaut
    const unsigned int _min_nb;

    const unsigned int _l_max_init_coef;

    //! Taille maximale d'une décomposition
    unsigned int _l_max;
    
    StrategyInit& stratInit;
};

} // namespace daex

#endif // __DAEX_INIT_H_

