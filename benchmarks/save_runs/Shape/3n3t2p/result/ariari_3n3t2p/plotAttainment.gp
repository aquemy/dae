reset

set term pngcairo
set output "attainment_linear.png"

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
'./attainment_12_4.txt' t '12 - 4' w lp, \
'./attainment_10_6.txt' t '10 - 6' w lp, \
'./attainment_8_8.txt' t '8 - 8' w lp, \
'./attainment_6_10.txt' t '6 - 10' w lp, \
'./attainment_4_12.txt' t '4 - 12' w lp, \
