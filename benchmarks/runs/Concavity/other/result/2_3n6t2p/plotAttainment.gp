reset

# define axis
# remove border on top and right and set color to gray
set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
# define grid
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set key bottom right

set xlabel 'Time (s)'
set ylabel 'Hypervolume Indicator'

set yrange [0:1.05]
set xrange [0:300]
plot \
'./attainment_20100_5090.txt' t '20100 - 5090' w lp, \
'./attainment_19080_7072.txt' t '19080 - 7072' w lp, \
'./attainment_17098_8092.txt' t '17098 - 8092' w lp, \
'./attainment_17096_9083.txt' t '17096 - 9083' w lp, \
'./attainment_16080_9593.txt' t '16080 - 9593' w lp, \
'./attainment_16078_10074.txt' t '16078 - 10074' w lp, \
'./attainment_15114_10584.txt' t '15114 - 10584' w lp, \
'./attainment_14096_11094.txt' t '14096 - 11094' w lp, \
'./attainment_14094_12085.txt' t '14094 - 12085' w lp, \
'./attainment_13078_12595.txt' t '13078 - 12595' w lp, \
'./attainment_13076_13076.txt' t '13076 - 13076' w lp, \
'./attainment_12112_13586.txt' t '12112 - 13586' w lp, \
'./attainment_11094_14096.txt' t '11094 - 14096' w lp, \
'./attainment_11092_15087.txt' t '11092 - 15087' w lp, \
'./attainment_10076_15597.txt' t '10076 - 15597' w lp, \
'./attainment_10074_16078.txt' t '10074 - 16078' w lp, \
'./attainment_9110_16588.txt' t '9110 - 16588' w lp, \
'./attainment_8092_17098.txt' t '8092 - 17098' w lp, \
'./attainment_8090_18089.txt' t '8090 - 18089' w lp, \
'./attainment_7074_18599.txt' t '7074 - 18599' w lp, \
'./attainment_7072_19080.txt' t '7072 - 19080' w lp, \
'./attainment_6108_19590.txt' t '6108 - 19590' w lp, \
'./attainment_5090_20100.txt' t '5090 - 20100' w lp, \
