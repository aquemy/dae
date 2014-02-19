#!/bin/bash

mode=$1
nbRuns=$2
minTime=$3
maxTime=$4
timeInterval=$5
runsDir=$6
resDir=$7
refDir=$8

# Cumulated pop
for ((run=0 ; $run < nbRuns; run++)) 
do
    # Time
    for time in $(seq $minTime $timeInterval $((maxTime+1))) 
    do
        more "$runsDir"/"$mode"_runs/run"$run"/archTime."$time" >> "$resDir"/"$mode"/run"$run"/cumulative_pop.txt
    done
    more "$resDir"/"$mode"/run"$run"/cumulative_pop.txt >> "$resDir"/"$mode"/cumulative_pop.txt
done

# GnuPlot
more "./plot/cumulatedHeader.gp" >> "$resDir"/"$mode"/plotCumulated.gp
echo "plot './cumulative_pop.txt' t 'IBEA H' pt 11 ps 1.2, '../../"$refDir"/"$mode"_pareto.txt' t 'Exact Pareto Front' pt 7 lc 7 ps 0.6" >> "$resDir"/"$mode"/plotCumulated.gp
