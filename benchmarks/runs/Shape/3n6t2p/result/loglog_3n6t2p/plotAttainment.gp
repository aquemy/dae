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
'./attainment_1380_690.txt' t '1380 - 690' w lp, \
'./attainment_1322_770.txt' t '1322 - 770' w lp, \
'./attainment_1242_828.txt' t '1242 - 828' w lp, \
'./attainment_1184_908.txt' t '1184 - 908' w lp, \
'./attainment_1104_966.txt' t '1104 - 966' w lp, \
'./attainment_1046_1046.txt' t '1046 - 1046' w lp, \
'./attainment_966_1104.txt' t '966 - 1104' w lp, \
'./attainment_908_1184.txt' t '908 - 1184' w lp, \
'./attainment_828_1242.txt' t '828 - 1242' w lp, \
'./attainment_770_1322.txt' t '770 - 1322' w lp, \
'./attainment_690_1380.txt' t '690 - 1380' w lp, \
