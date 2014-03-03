#!/bin/bash

#param=()
#for i in `seq 1 9` 	 #Parameter reading $#`
#do
#param[i]=$1
#shift
#done

# Run number
runNb=0
if [ -f "./runNumber" ]; then
    runNb=`cat ./runNumber`
    runNb=$((runNb+1))
fi

echo "$runNb" > ./runNumber

exe=$1
paramFile="$1.status"
maxTime=$2
objective="Add"
instance=$3
seed=$7
instanceName=`basename $instance | cut -d. -f 1`
resDir="../results/$exe/$instanceName/run$runNb"

for i in `seq 1 6` 	 #Parameter reading $#`
do
shift
done

stringparam=`echo  $* | sed 's/= /=/g'`

mkdir -p "$resDir" > /dev/null

echo "./$exe @$paramFile -Z=$objective -I=$instance --maxTime=$maxTime -seed=$seed -q=0 $stringparam" > command_line.txt
./$exe @$paramFile -Z=$objective -I=$instance --maxTime=$maxTime -seed=$seed -q=0 --resDir=$resDir $stringparam > test_wrapper.txt

../pisa/normalize ../pisa/zeno_bound ./$resDir/archTime.$maxTime  ./$resDir/zeno_norm_$maxTime 

../pisa/hyp_ind ../pisa/hyp_ind_param.txt ./$resDir/zeno_norm_$maxTime  ../pisa/zeno_ref ./$resDir/zeno_hyp_$maxTime

best_sol=`awk 'NR==1 {print $1}' ./$resDir/zeno_hyp_$maxTime`

result=$best_sol #results to return 

echo "Result for ParamILS: -1, $maxTime, -1, $result, $seed"		# Output for ParamILS

