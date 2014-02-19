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
'./attainment_552_276.txt' t '552 - 276' w lp, \
'./attainment_494_356.txt' t '494 - 356' w lp, \
'./attainment_414_414.txt' t '414 - 414' w lp, \
'./attainment_356_494.txt' t '356 - 494' w lp, \
'./attainment_276_552.txt' t '276 - 552' w lp, \
