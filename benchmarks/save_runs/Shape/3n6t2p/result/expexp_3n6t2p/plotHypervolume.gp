reset

set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror

set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set style line 1 lc rgb '#8b1a0e' pt 4 ps 1 lt 1

set key top right

set logscale y

set xlabel 'Time (s)'
set ylabel 'Hypervolume Indicator'
plot './mean_hypervolume.txt' t 'expexp_3n6t2p' w lp ls 1 
