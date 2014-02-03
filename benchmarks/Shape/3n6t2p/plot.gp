set xlabel 'Makespan'
set ylabel 'Cost'
set term pngcairo
set output './temp/3n6t2p_zenoMulti_plot.png'
set title 'MultiZeno : n=3 t=6 p=2'
plot  './temp/ariari_3n6t2p_pareto.txt' with linespoint title 'Ari / Ari', './temp/loglog_3n6t2p_pareto.txt' with linespoint title 'Log / Log', './temp/expexp_3n6t2p_pareto.txt' with linespoint title 'Exp / Exp', './temp/sqrtsqrt_3n6t2p_pareto.txt' with linespoint title 'Sqrt / Sqrt', './temp/ariexp_3n6t2p_pareto.txt' with linespoint title 'Ari / Exp', './temp/explog_3n6t2p_pareto.txt' with linespoint title 'Exp / Log',
