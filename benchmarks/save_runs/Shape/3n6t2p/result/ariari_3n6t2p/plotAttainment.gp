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
'./attainment_30_10.txt' t '30 - 10' w lp, \
'./attainment_28_12.txt' t '28 - 12' w lp, \
'./attainment_26_14.txt' t '26 - 14' w lp, \
'./attainment_24_16.txt' t '24 - 16' w lp, \
'./attainment_22_18.txt' t '22 - 18' w lp, \
'./attainment_20_20.txt' t '20 - 20' w lp, \
'./attainment_18_22.txt' t '18 - 22' w lp, \
'./attainment_16_24.txt' t '16 - 24' w lp, \
'./attainment_14_26.txt' t '14 - 26' w lp, \
'./attainment_12_28.txt' t '12 - 28' w lp, \
'./attainment_10_30.txt' t '10 - 30' w lp, \
