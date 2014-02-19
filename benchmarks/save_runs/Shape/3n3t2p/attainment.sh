#!/bin/bash

mode=$1
nbRuns=$2
minTime=$3
maxTime=$4
timeInterval=$5
runsDir=$6
resDir=$7
refDir=$8

# Attainment
more "./plot/attainmentHeader.gp" > "$resDir"/"$mode"/plotAttainment.gp
echo "plot \\" >> "$resDir"/"$mode"/plotAttainment.gp
cat "$refDir"/"$mode"_pareto.txt | while read x y z
do   
    for time in $(seq $minTime $timeInterval $((maxTime+1))) 
    do
        nbFound=0
        # Runs
        for ((run=0 ; $run < nbRuns; run++)) 
        do
            if grep -q "$x $y" ""$runsDir"/"$mode"_runs/run"$run"/archTime."$time"" > /dev/null
            then
                nbFound=$((nbFound+1))
            fi
        done
        ratio=`ruby -e "p $nbFound/$nbRuns.0"`
        echo "$time $ratio"  >> ""$resDir"/"$mode"/attainment_"$x"_"$y".txt"
    done
    echo "'./attainment_"$x"_"$y".txt' t '"$x" - "$y"' w lp, \\" >> "$resDir"/"$mode"/plotAttainment.gp
done

