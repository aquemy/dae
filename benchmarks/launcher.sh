#!/bin/bash

build=../build/dae
series=./Shape/3n3t2p
nbRuns=30

for instance in `ls "$series" | grep pddl` 
do 
    mkdir "$series"/"$instance"_runs
    rm "$series"/"$instance"_runs/*
    for ((i=0 ; $i < $nbRuns; i++)) 
    do 
        $build/daeibea @./daeibea.status -I=""$series"/"$instance""
        mv ./Res "$series"/"$instance"_runs/run"$i"
    done
done
