set xlabel "time (seconds)"
set ylabel "iterations (number of function calls)"

set autoscale


set title "Neural Network Feedforward Times"

set grid

set datafile separator ","

plot "times.csv"
pause -1 "Hit any key to continue"
