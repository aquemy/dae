#!/bin/bash

# 
nbRuns=10
minTime=0
maxTime=30
timeInterval=10
runsDir="./runs"
resDir="./result"
refDir="./front"
modes=( "1_3n6t2p" )

#
pisaDir="./exe"

# Clean
mkdir "$resDir" 2>> /dev/null

# Reference


rm "$resDir/ref" -r 2>> /dev/null
mkdir "$resDir/ref"

for mode in "${modes[@]}"    
do   
    echo "# Mode : "$mode""
    echo "## 1. Reference Set"
    bash ./reference.sh "$refDir" "$mode" "$resDir" "$pisaDir"
    
    rm "$resDir/$mode" -r 2>> /dev/null
    mkdir "$resDir/$mode"
    
    echo "## 2. Hypervolume Computation"
    bash ./hypervolume.sh "$mode" "$nbRuns" "$minTime" "$maxTime" "$timeInterval" "$runsDir" "$resDir" "$pisaDir"
    
    echo "## 3. Cumulated Pop"
    bash ./cumulated.sh "$mode" "$nbRuns" "$minTime" "$maxTime" "$timeInterval" "$runsDir" "$resDir" "$refDir"
    
    echo "## 4. Attainment Computation"
    bash ./attainment.sh "$mode" "$nbRuns" "$minTime" "$maxTime" "$timeInterval" "$runsDir" "$resDir" "$refDir"
done

