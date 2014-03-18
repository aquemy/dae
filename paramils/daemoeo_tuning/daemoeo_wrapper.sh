#!/bin/bash

exe=$1
paramFile="$1.status"
maxTime=$2
objective="Add"
instance=$3
seed=$7
instanceName=`basename $instance | cut -d. -f 1`

# Run number
runNb=0
if [ -f "../results/$exe/$instanceName/runNumber" ]; then
    runNb=`cat ../results/$exe/$instanceName/runNumber`
    runNb=$((runNb+1))
fi

echo "$runNb" > ../results/$exe/$instanceName/runNumber

resDir="../results/$exe/$instanceName/run$runNb"

for i in `seq 1 6` 	 #Parameter reading $#`
do
shift
done

stringparam=`echo  $* | sed 's/= /=/g'`

mkdir -p "$resDir" > /dev/null

echo "./$exe @$paramFile -Z=$objective -I=$instance --maxTime=$maxTime -seed=$seed -q=0 $stringparam" > command_line.txt
./$exe @$paramFile -Z=$objective -I=$instance --maxTime=$maxTime -seed=$seed -q=0 --resDir=$resDir $stringparam > test_wrapper.txt

# Get the last archive according to timestamp
lastArch=`ls -got ./$resDir | grep archTime | head -1 | awk '{print $7}'`

../pisa/normalize ${instance%.*}_bounds.txt ./$resDir/$lastArch ./$resDir/normalized_$maxTime.txt 
../pisa/hyp_ind ../pisa/hyp_ind_param.txt ./$resDir/normalized_$maxTime.txt  ${instance%.*}_ref.txt ./$resDir/hypervolume_$maxTime

best_sol=`awk 'NR==1 {print $1}' ./$resDir/hypervolume_$maxTime`

result=$best_sol #results to return 

echo "Result for ParamILS: -1, $maxTime, -1, $result, $seed"		# Output for ParamILS

