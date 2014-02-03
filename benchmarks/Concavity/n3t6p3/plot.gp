set xlabel 'Makespan'
set ylabel 'Cost'
set term pngcairo
set output './temp/3n6t3p_zenoMulti_plot.png'
set title 'MultiZeno : n=3 t=6 p=3'
plot  './temp/1_3n6t3p_pareto.txt' with linespoint title '1', './temp/2_3n6t3p_pareto.txt' with linespoint title '2', './temp/3_3n6t3p_pareto.txt' with linespoint title '3', './temp/4_3n6t3p_pareto.txt' with linespoint title '4',
