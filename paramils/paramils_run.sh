#!/bin/bash

#program="nsgaII speaII ibeaepsilon ibeahyper"
program="aggregation"

#var="Add Max"
var="Add"

for i in $program
do
    for j in $var
    do
        # Create references files
        while read instance  
        do  
           ./daemoeo_tuning/pisa/bound ${instance%.*}_pareto.txt ${instance%.*}_bounds.txt
           ./daemoeo_tuning/pisa/normalize ${instance%.*}_bounds.txt ${instance%.*}_pareto.txt ${instance%.*}_ref.txt
        done < daemoeo_tuning/daemoeo-inst.txt
	    ruby param_ils_2_3_run.rb -numRun 4 -scenariofile daemoeo_tuning/$i/scenarion-$i-$j-instance.txt -validN 0 -userunlog 1
    done
done



