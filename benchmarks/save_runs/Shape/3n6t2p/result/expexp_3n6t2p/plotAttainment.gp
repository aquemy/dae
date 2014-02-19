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
'./attainment_40_10.txt' t '40 - 10' w lp, \
'./attainment_36_12.txt' t '36 - 12' w lp, \
'./attainment_32_14.txt' t '32 - 14' w lp, \
'./attainment_28_16.txt' t '28 - 16' w lp, \
'./attainment_24_18.txt' t '24 - 18' w lp, \
'./attainment_20_20.txt' t '20 - 20' w lp, \
'./attainment_18_24.txt' t '18 - 24' w lp, \
'./attainment_16_28.txt' t '16 - 28' w lp, \
'./attainment_14_32.txt' t '14 - 32' w lp, \
'./attainment_12_36.txt' t '12 - 36' w lp, \
'./attainment_10_40.txt' t '10 - 40' w lp, \
