#! /usr/bin/ksh
#
# run.ksh: UNIX/LINUX complement to run.bat
#
# Eckart Zitzler, ETH Zurich, Feb 18, 2005

# to be edited by the user
selectors="ibea nsga2 spea2"
variators="dtlz2 knapsack zdt6"
os="linux"

generation=2

#=================================================
# DO NOT MAKE ANY CHANGES BELOW THIS LINE
#=================================================

export os


if [[ $1 != "compare" ]] ; then
    for sel in $selectors ; do
	for var in $variators ; do
	    bash ./compute.ksh run $sel $var $generation
	done ;
    done ;
fi
    
for var in $variators ; do
    bash ./compute.ksh bounds dummy $var $generation
done ;
    
for sel in $selectors ; do
    for var in $variators ; do
	bash ./compute.ksh indicators $sel $var $generation
    done ;
done ;
    
for var in $variators ; do
    bash ./compute.ksh tests dummy $var $generation
done ;

for sel in $selectors ; do
    for var in $variators ; do
	bash ./compute.ksh eafs $sel $var $generation
    done ;
done ;

for sela in $selectors ; do
    for selb in $selectors ; do
        for var in $variators ; do
	    bash ./compute.ksh eaftests $sela $selb $var $generation
	done ;
    done ;
done ;

for sela in $selectors ; do
    for selb in $selectors ; do
        for var in $variators ; do
	    bash ./compute.ksh ranktests $sela $selb $var $generation
	done ;
    done ;
done ;

