#!/bin/bash

param=()
for i in `seq 1 9` 	 #Parameter reading $#`
do
param[i]=$1
shift
done
 
stringparam=`echo  $* | sed  's/= /=/g'`

rep=${param[4]}"Res"

./${param[1]}  @${param[2]} -Z=${param[4]} -I=${param[5]} -S=${param[9]} --resDir=$rep  $stringparam  # daemoeo Call


gen=`awk 'END {print NR}' ./${param[4]}Res/stats`

let gen=gen-1

sed -i -e "s/\t/ /g" ./${param[4]}Res/arch.$gen  # Format Adjusting 

../pisa/normalize  ../pisa/${param[3]}'_'${param[4]}'_bound' ./${param[4]}Res/arch.$gen    ./${param[4]}Res/norm_$gen 
../pisa/hyp_ind  ./${param[4]}Res/norm_$gen  ../pisa/${param[3]}'_'${param[4]}_'ref' ./${param[4]}Res/hyp_$gen  # HyperVolume Computing 	

best_sol=`awk 'NR==1 {print $1}' ./${param[4]}Res/hyp_$gen`

runtime=`awk -v gen=$gen 'NR==gen { print $8 }' ./${param[4]}Res/stats`


#if [  -z "$best_sol" ]
#then
#    reponse="UNSAT"
#else
#    reponse="SAT"
#fi

echo "Result for ParamILS: -1, $runtime, -1, $best_sol, ${param[9]}"		# Output for ParamILS

#echo "Result for ParamILS: SAT, $runtime, $runlength, $best_sol, ${param[8]}"




