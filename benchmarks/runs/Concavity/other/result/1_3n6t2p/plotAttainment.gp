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
'./attainment_5090_100.txt' t '5090 - 100' w lp, \
'./attainment_5072_1080.txt' t '5072 - 1080' w lp, \
'./attainment_4092_1098.txt' t '4092 - 1098' w lp, \
'./attainment_4072_1597.txt' t '4072 - 1597' w lp, \
'./attainment_4054_2087.txt' t '4054 - 2087' w lp, \
'./attainment_3094_2096.txt' t '3094 - 2096' w lp, \
'./attainment_3054_2595.txt' t '3054 - 2595' w lp, \
'./attainment_3036_3085.txt' t '3036 - 3085' w lp, \
'./attainment_2096_3094.txt' t '2096 - 3094' w lp, \
'./attainment_2036_3593.txt' t '2036 - 3593' w lp, \
'./attainment_2018_4083.txt' t '2018 - 4083' w lp, \
'./attainment_1098_4092.txt' t '1098 - 4092' w lp, \
'./attainment_1018_4591.txt' t '1018 - 4591' w lp, \
'./attainment_1000_5081.txt' t '1000 - 5081' w lp, \
'./attainment_100_5090.txt' t '100 - 5090' w lp, \
