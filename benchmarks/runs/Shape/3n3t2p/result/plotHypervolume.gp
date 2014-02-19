reset

set term pngcairo
set output "hypervolume_3n3t2p.png"

set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set key top right

set xlabel 'Makespan'
set ylabel 'Cost'
set logscale y
plot 'ariari_3n3t2p/mean_hypervolume.txt' t 'Linear' w lp, 'loglog_3n3t2p/mean_hypervolume.txt' t 'Concave' w lp, 'expexp_3n3t2p/mean_hypervolume.txt' t 'Convex' w lp
