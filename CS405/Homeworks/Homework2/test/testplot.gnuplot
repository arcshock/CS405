set border 3
set auto

set xlabel "time (seconds)"
set ylabel "iterations (number of function calls)"

set autoscale
set xtics 5

set title "Neural Network Feedforward Times"

set grid

set datafile separator ","

set style histogram clustered gap 1
set style fill solid border -1
 
 binwidth=5
 set boxwidth binwidth
 bin(x,width)=width*floor(x/width) + binwidth/2.0
  
 plot 'times.csv' using (bin($1,binwidth)):(1.0) smooth freq with boxes
#plot "times.csv"
pause -1 "Hit any key to continue"
