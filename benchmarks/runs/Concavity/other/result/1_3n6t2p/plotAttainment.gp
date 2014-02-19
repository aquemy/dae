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
'./attainment_4074_2078.txt' t '4074 - 2078' w lp, \
'./attainment_3094_2096.txt' t '3094 - 2096' w lp, \
'./attainment_3076_3076.txt' t '3076 - 3076' w lp, \
'./attainment_2096_3094.txt' t '2096 - 3094' w lp, \
'./attainment_2078_4074.txt' t '2078 - 4074' w lp, \
'./attainment_1098_4092.txt' t '1098 - 4092' w lp, \
'./attainment_1080_5072.txt' t '1080 - 5072' w lp, \
'./attainment_100_5090.txt' t '100 - 5090' w lp, \
