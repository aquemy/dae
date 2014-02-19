#!/bin/bash

mode=$1
nbRuns=$2
minTime=$3
maxTime=$4
timeInterval=$5
runsDir=$6
resDir=$7
pisaDir=$8

# Hypervolume by run
for ((run=0 ; $run < nbRuns; run++)) 
do
    runResDir="$resDir"/"$mode"/run"$run"
    mkdir "$runResDir" >> /dev/null
    # Time
    for time in $(seq $minTime $timeInterval $((maxTime+1))) 
    do
        #Normalize
        "$pisaDir"/normalize "$pisaDir"/normalize_param.txt "$resDir"/ref/"$mode"_bounds.txt "$runsDir"/"$mode"_runs/run"$run"/archTime."$time" "$runResDir"/run"$run"_"$time"_normalize.txt
        #Hypevolume
        "$pisaDir"/hyp_ind "$pisaDir"/hyp_ind_param.txt "$runResDir"/run"$run"_"$time"_normalize.txt "$resDir"/ref/"$mode"_normalize.txt "$runResDir"/hypervolume."$time"
    done
done

# Average hypervolume
for time in $(seq $minTime $timeInterval $((maxTime+1))) 
do
    for ((run=0 ; $run < nbRuns; run++)) 
    do
        runResDir="$resDir"/"$mode"/run"$run"
        more "$runResDir"/hypervolume."$time" >> "$resDir"/"$mode"/hypervolume_run"$n"."$time"
    done
    awk -v n="$nbRuns" ' {S+=$1} END{print S / n}' < "$resDir"/"$mode"/hypervolume_run"$n"."$time" >> "$resDir"/"$mode"/mean_hypervolume.txt
done

# GnuPlot
more "./plot/hypervolumeHeader.gp" >> "$resDir"/"$mode"/plotHypervolume.gp
echo "plot './mean_hypervolume.txt' t '"$mode"' w lp ls 1 " >> "$resDir"/"$mode"/plotHypervolume.gp

