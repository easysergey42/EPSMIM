#!/bin/bash
let nx=1000
let ny=1000
let nt=100
gcc main.c -o main -Ofast
time ./main $nx $ny $nt
gnuplot << EOFMarker
nx=$nx
ny=$ny
filename="output/binary"
set terminal png size 1100,1000
set output filename.".png"
set xrange[-1:nx]
set yrange[-1:ny]
set palette gray
set title "painting"
plot filename binary array=(ny,nx) format="%f" with image
EOFMarker
xdg-open output/binary.png

