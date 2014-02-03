set xlabel 'Makespan'
set ylabel 'Cost'
set term pngcairo
set output './temp/3n6t4p_zenoMulti_plot.png'
set title 'MultiZeno : n=3 t=6 p=4'
plot  './temp/1_3n6t4p_pareto.txt' with linespoint title 'both', './temp/2_3n6t4p_pareto.txt' with linespoint title 'C : exp',
