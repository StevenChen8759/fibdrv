reset
set datafile separator ','
set xlabel 'Fibonacci Number(n)'
set ylabel 'time(ns)'
set xtics 0, 5, 95
set style data lines
set grid
set title 'Fibonacci Number Calculation Performance'

set term png enhanced font 'Verdana,10'
set output 'fibnum_perf.png'

plot \
"fibperf.csv" using 0:3 with linespoints linewidth 2 title "Calculate via Dynamic Programming", \
"fibperf.csv" using 0:4 with linespoints linewidth 2 title "Calculate via Fast Doubling"
