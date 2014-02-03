set xlabel 'Makespan'
set ylabel 'Cost'
set term pngcairo
set output './temp/3n9t2p_zenoMulti_plot.png'
set title 'MultiZeno : n=3 t=9 p=2'
plot  './temp/ariari_3n9t2p_pareto.txt' with linespoint title 'Ari / Ari', './temp/loglog_3n9t2p_pareto.txt' with linespoint title 'Log / Log', './temp/expexp_3n9t2p_pareto.txt' with linespoint title 'Exp / Exp', './temp/sqrtsqrt_3n9t2p_pareto.txt' with linespoint title 'Sqrt / Sqrt', './temp/ariexp_3n9t2p_pareto.txt' with linespoint title 'Ari / Exp', './temp/explog_3n9t2p_pareto.txt' with linespoint title 'Exp / Log',
