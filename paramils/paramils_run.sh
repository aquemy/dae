#!/bin/bash

#program="nsgaII speaII ibeaepsilon ibeahyper"
program="ibeahyper"

#var="Add Max"
var="Add"

for i in $program
do
    for j in $var
    do

	nohup ruby param_ils_2_3_run.rb -numRun 0 -scenariofile daemoeo_tuning/$i/scenarion-$i-$j-instance.txt -validN 100 #&
     done
done

