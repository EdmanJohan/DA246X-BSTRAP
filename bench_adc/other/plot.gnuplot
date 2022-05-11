# set terminal postscript size 8,4 portrait enhanced background rgb 'white' color dashed lw 1 "cmr,12"
#set terminal epslatex size 3.0in,2.25in font ',8'
set terminal postscript size 2in,1.5in enhanced background rgb 'white' color dashed lw 1 "cmr,5"
set output 'TRNG-plot.eps'

set datafile separator ","
set key autotitle columnhead
unset key

colrrs = "#FFC380"
xTitle = "Byte value"
yTitle = "Occurrence"

set xlabel "".xTitle
set ylabel "".yTitle

set style data histograms
set format y '%.0s%c'
#set yrange [0:1000000] # 1M
set yrange [0:100000] # 100k
set ytics nomirror


set grid ytics mytics  # draw lines for each ytics and mytics
set mytics 2           # set the spacing for the mytics
set grid               # enable the grid

set xrange [0:255]
set xtics nomirror
set tics out

set linetype 1 lc rgb colrrs


#plot '../data/summary.csv' using 2 with histogram linecolor 1 # C0.0
#plot '../data/summary.csv' using 3 with histogram linecolor 1 # C1.0
#plot '../data/summary.csv' using 4 with histogram linecolor 1 # NC0.0
#plot '../data/summary.csv' using 5 with histogram linecolor 1 # NC0.1
#plot '../data/summary.csv' using 6 with histogram linecolor 1 # NC1.0
#plot '../data/summary.csv' using 7 with histogram linecolor 1 # NC1.1
plot '../data/summary.csv' using 8 with histogram linecolor 1 # TRNG
