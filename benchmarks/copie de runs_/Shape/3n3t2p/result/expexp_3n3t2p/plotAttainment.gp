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
'./attainment_16_4.txt' t '16 - 4' w lp, \
'./attainment_12_6.txt' t '12 - 6' w lp, \
'./attainment_8_8.txt' t '8 - 8' w lp, \
'./attainment_6_12.txt' t '6 - 12' w lp, \
'./attainment_4_16.txt' t '4 - 16' w lp, \
