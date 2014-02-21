set xlabel "time"
set ylabel "iterations"

set autoscale


set title "Neural Network Feedforward Times"

set grid

set datafile separator ","

plot "no_optimization.csv", "optimization.csv"
pause -1 "Hit any key to continue"
