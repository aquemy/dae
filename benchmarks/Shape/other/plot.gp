set xlabel 'Makespan'
set ylabel 'Cost'
set term pngcairo
set output './temp/4n3t2p_zenoMulti_plot.png'
set title 'MultiZeno : n=4 t=3 p=2'
plot  './temp/1_4n3t2p_pareto.txt' with linespoint title 'same', './temp/2_4n3t2p_pareto.txt' with linespoint title 'exp', './temp/3_4n3t2p_pareto.txt' with linespoint title 'log', './temp/4_4n3t2p_pareto.txt' with linespoint title 'ari',
