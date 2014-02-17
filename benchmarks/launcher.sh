#!/bin/bash

nbRuns=30
build=../build/dae
folder=Shape/3n6t2p
instances=( "ariari_3n6t2p" "expexp_3n6t2p" "loglog_3n6t2p" )

for instance in "${instances[@]}"   
do 
    echo "# Instance : $instance"
    mkdir ./runs/"$folder"/runs/"$instance"_runs -p
    mkdir ./runs/"$folder"/front/ -p
    cp ./"$folder"/"$instance"_pareto.txt ./runs/"$folder"/front/

    rm ./runs/"$folder"/runs/"$instance"_runs/* -r >> /dev/null
    for ((i=0 ; $i < $nbRuns; i++)) 
    do 
        echo "- Run : $i"
        $build/daeibea @./"$folder"/daeibea.status -I="./"$folder"/"$instance".pddl" --maxTime=610
        mv ./Res ./runs/"$folder"/runs/"$instance"_runs/run"$i"
    done
    
    cp ./scripts/* ./runs/
done

