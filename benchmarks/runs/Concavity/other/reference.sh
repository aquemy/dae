#!/bin/bash

# Configuration
refDir=$1
refFile=$2
resDir=$3
pisaDir=$4

# Reference set
#Bounds
"$pisaDir"/bound "$pisaDir"/bound_param.txt ""$refDir"/"$refFile"_pareto.txt" "$resDir"/ref/"$refFile"_bounds.txt
#Filter
"$pisaDir"/filter "$pisaDir"/filter_param.txt ""$refDir"/"$refFile"_pareto.txt" "$resDir"/ref/"$refFile"_filter.txt
#Normalize
"$pisaDir"/normalize "$pisaDir"/normalize_param.txt "$resDir"/ref/"$refFile"_bounds.txt "$resDir"/ref/"$refFile"_filter.txt "$resDir"/ref/"$refFile"_normalize.txt
