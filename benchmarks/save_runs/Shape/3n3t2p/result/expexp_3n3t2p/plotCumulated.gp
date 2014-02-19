reset

set term pngcairo
set output "cumulated_convexe.png"

set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12

set key top right

set xlabel 'Makespan'
set ylabel 'Cost / Risk'
plot './cumulative_pop.txt' t 'IBEA H' pt 11 ps 1.2, '../.././front/expexp_3n3t2p_pareto.txt' t 'Exact Pareto Front' pt 7 lc 7 ps 0.6
