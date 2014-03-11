reset
set macro

#####  Color Palette by Color Scheme Designer
#####  Palette URL: http://colorschemedesigner.com/#3K40zsOsOK-K-

   blue_000 = "#A9BDE6" # = rgb(169,189,230)
   blue_025 = "#7297E6" # = rgb(114,151,230)
   blue_050 = "#1D4599" # = rgb(29,69,153)
   blue_075 = "#2F3F60" # = rgb(47,63,96)
   blue_100 = "#031A49" # = rgb(3,26,73)

   green_000 = "#A6EBB5" # = rgb(166,235,181)
   green_025 = "#67EB84" # = rgb(103,235,132)
   green_050 = "#11AD34" # = rgb(17,173,52)
   green_075 = "#2F6C3D" # = rgb(47,108,61)
   green_100 = "#025214" # = rgb(2,82,20)

   red_000 = "#F9B7B0" # = rgb(249,183,176)
   red_025 = "#F97A6D" # = rgb(249,122,109)
   red_050 = "#E62B17" # = rgb(230,43,23)
   red_075 = "#8F463F" # = rgb(143,70,63)
   red_100 = "#6D0D03" # = rgb(109,13,3)

   brown_000 = "#F9E0B0" # = rgb(249,224,176)
   brown_025 = "#F9C96D" # = rgb(249,201,109)
   brown_050 = "#E69F17" # = rgb(230,159,23)
   brown_075 = "#8F743F" # = rgb(143,116,63)
   brown_100 = "#6D4903" # = rgb(109,73,3)

   grid_color = "#d5e0c9"
   text_color = "#6a6a6a"


   my_line_width = "1.1
   my_axis_width = "1.5"
   my_ps = "1.2"
   my_font_size = "14"

# must convert font fo svg and ps
#set term svg  size @my_export_sz fname my_font fsize my_font_size enhanced dynamic rounded
# set term png  size @my_export_sz large font my_font
# set term jpeg size @my_export_sz large font my_font
#set term wxt enhanced font my_font

set style data linespoints
set style function lines

set style line 1  linecolor rgbcolor blue_050  linewidth @my_line_width pt 7
set style line 2  linecolor rgbcolor green_050 linewidth @my_line_width pt 5
set style line 3  linecolor rgbcolor red_050   linewidth @my_line_width pt 9
set style line 4  linecolor rgbcolor brown_050 linewidth @my_line_width pt 13
set style line 5  linecolor rgbcolor blue_050  linewidth @my_line_width pt 11
set style line 6  linecolor rgbcolor green_050 linewidth @my_line_width pt 7
set style line 7  linecolor rgbcolor red_050   linewidth @my_line_width pt 5
set style line 8  linecolor rgbcolor brown_050 linewidth @my_line_width pt 9
set style line 9  linecolor rgbcolor blue_075  linewidth @my_line_width pt 13
set style line 10 linecolor rgbcolor green_075 linewidth @my_line_width pt 11
set style line 11 linecolor rgbcolor red_075   linewidth @my_line_width pt 7
set style line 12 linecolor rgbcolor brown_075 linewidth @my_line_width pt 5
set style line 13 linecolor rgbcolor blue_100  linewidth @my_line_width pt 9
set style line 14 linecolor rgbcolor green_100 linewidth @my_line_width pt 13
set style line 15 linecolor rgbcolor red_100   linewidth @my_line_width pt 11
set style line 16 linecolor rgbcolor brown_100 linewidth @my_line_width pt 7
set style line 17 linecolor rgbcolor "#224499" linewidth @my_line_width pt 5
set style increment user
set style arrow 1 filled


set terminal postscript eps enhanced color font 'Helvetica,10'
set output 'attainment_grouped.eps'

set style line 11 lc rgb '#808080' lt 1
set border 3 back ls 11
set tics nomirror
set style line 12 lc rgb '#808080' lt 0 lw 1
set grid back ls 12
set key font ",10"

set key top right

set xlabel 'Makespan'
set ylabel 'Cost'
set title 'MultiZeno : n=3 t=6 p=3'
plot  './1_3n6t3p_pareto.txt' with linespoint title '', './2_3n6t3p_pareto.txt' with linespoint title '', './3_3n6t3p_pareto.txt' with linespoint title '', './4_3n6t3p_pareto.txt' with linespoint title '',
