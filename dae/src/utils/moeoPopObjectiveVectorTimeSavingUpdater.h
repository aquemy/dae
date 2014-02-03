/*
* <moeoPopObjectiveVectorSavingUpdater.h>
* Copyright (C)  TAO Project-Team, INRIA Saclay, 2011-2012
 
* Mostepha-Redouane Khouadjia
//-----------------------------------------------------------------------------



*/
#ifndef MOEOPOPOBJECTIVEVECTORTIMESAVINGUPDATER_H_
#define MOEOPOPOBJECTIVEVECTORTIMESAVINGUPDATER_H_

#include <fstream>
#include <string>
#include <eoPop.h>
#include <utils/eoUpdater.h>
#include <archive/moeoArchive.h>

#define MAX_BUFFER_SIZE 1000

/**
 * This class allows to save the objective vectors of the solutions contained in an archive into a file at each generation.
 */
template < class MOEOT >
class moeoPopObjectiveVectorTimeSavingUpdater : public eoUpdater
  {
  public:

    /**
     * Ctor
     * @param _arch local archive
     * @param _filename target filename
     * @param _count put this variable to true if you want a new file to be created each time () is called and to false if you only want the file to be updated
     * @param _id own ID
     */
    moeoPopObjectiveVectorTimeSavingUpdater (eoPop<MOEOT> & _pop, const std::string & _filename, time_t _interval, bool _count = false,int _id = -1) :
        pop(_pop), filename(_filename), interval(_interval), last_time(time(0)), first_time(time(0)), count(_count), id(_id), first(true)
    {}


    /**
     * Saves the fitness of the archive's members into the file
     */
    void operator()()
    {
      time_t now = time(0);
      char buff[MAX_BUFFER_SIZE];
      
      if (now >= last_time + interval or first)
      {
	    last_time = now;
	    first = false;
	
	    if (count)
            {
              if (id == -1)
                {
                  sprintf (buff, "%s.%u", filename.c_str(), (now - first_time));
                }
              else
                {
                  sprintf (buff, "%s.%u.%u", filename.c_str(), id, (now - first_time));
                }
            }
          else
            {
              if (id == -1)
                {
                  sprintf (buff, "%s", filename.c_str());
                }
              else
                {
                  sprintf (buff, "%s.%u", filename.c_str(), id);
                }
            }
          std::ofstream f(buff);
          for (unsigned int i = 0; i < pop.size (); i++)
            f << pop[i].objectiveVector() << std::endl;
          f.close ();
        }
    
    }


  private:

    /** local archive */
    eoPop<MOEOT> & pop;
    /** target filename */
    std::string filename;
    /** this variable is set to true if a new file have to be created each time () is called and to false if the file only HAVE to be updated */
    bool count;
    /** own ID */
    int id;
    const time_t interval;
    time_t last_time;
    const time_t first_time;
    bool first;
  };

#endif //MOEOARCHIVEOBJECTIVEVECTORTIMESAVINGUPDATER_H_
