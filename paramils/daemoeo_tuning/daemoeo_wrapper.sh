#!/bin/bash

param=()
for i in `seq 1 9` 	 #Parameter reading $#`
do
param[i]=$1
shift
done
 
stringparam=`echo  $* | sed  's/= /=/g'`

rep=${param[3]}'_'${param[4]}"Res"

./${param[1]}  @${param[2]} -Z=${param[4]} -I=${param[5]} --maxTime=${param[7]} -S=${param[9]} --resDir=$rep  $stringparam  

#daemoeo Call


gen=`awk 'END {print NR}' ./$rep/stats`

let gen=gen-1

sed -i -e "s/\t/ /g" ./$rep/arch.$gen  # Format Adjusting 

sort -k1n,1n -o ./$rep/arch.$gen ./$rep/arch.$gen

../pisa/normalize  ../pisa/${param[3]}'_'${param[4]}'_bound' ./$rep/arch.$gen  ./$rep/${param[3]}'_norm_'$gen 

../pisa/hyp_ind  ../pisa/hyp_ind_param.txt ./$rep/${param[3]}'_norm_'$gen  ../pisa/${param[3]}'_'${param[4]}_'ref' ./$rep/${param[3]}'_hyp_'$gen  	 # HyperVolume Computing with PISA	

best_sol=`awk 'NR==1 {print $1}' ./$rep/${param[3]}'_hyp_'$gen`

let run_gen=gen+1

runtime=`awk 'NR=='$run_gen' { print $8 }' ./$rep/stats`


result=$best_sol #results to return 

echo "Result for ParamILS: -1, $runtime, -1, $result, ${param[9]}"		# Output for ParamILS

