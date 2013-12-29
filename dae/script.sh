#!/bin/bash


rm -r  Res* nohup.out output run_time.xp

for i in `seq 1 10`;

do

s_time=`date +%H_%M_%S_%F`_exp

> run_time.xp

$s_time> run_time.xp

S=`awk 'NR=='$i'{print $1}' seeds`

nohup ./daemoeo @param  -S=$S < /dev/null  > output

f_time=`date +n%H_%M_%S_%F` 

$f_time > run_time.xp 

mkdir  exp_$i 

cp -r Res run_time.xp  exp_$i

zip -r exp_$i.zip exp_$i

done

#cp -r exp_$s $dir                                                                                                                                           
#zip -r -u  $dir.zip $dir                                                                                                                                    
#scp -o StrictHostKeyChecking=no -r $dir.zip mrkhouadjia@frontale.bordeaux.grid5000.fr:~/experiments/      

#nohup mpiexec -machinefile nodes -n 4 ./islandPso @tparam -I=$1 -E=$s -1=$2 -2=$3  < /dev/null  > output

