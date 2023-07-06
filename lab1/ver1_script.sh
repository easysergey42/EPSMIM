#!/bin/bash
nx=$1
ny=$2
nt=$3
gcc ver1.c -o ver1.out -Ofast
time ./ver1.out $nx $ny $nt
gnuplot << EOFMarker
nx=$nx
ny=$ny
filename="binary"
set terminal png size 900,800
set output filename.".png"
set xrange[-1:nx]
set yrange[-1:ny]
set palette gray
set title filename
plot filename binary array=(ny,nx) format="%f" with image
EOFMarker
xdg-open binary.png

