#!/bin/bash
let nx=100
let ny=100
let nt=5000
if [[ $1 =~ $re ]] ;
then
	nx=$1
fi
if [[ $2 =~ $re ]] ;
then
	if [[ $1 =~ $re ]] ;
then
	ny=$1
fi
fi
if [[ $3 =~ $re ]] ;
then
	nt=$3
fi
echo ""
echo "v1 -O1"
gcc ver1.c -o ver1.out -O1
time ./ver1.out $nx $ny $nt
echo ""
echo "v2 -O1"
g++ ver2.cpp -o ver2.out -O1
time ./ver2.out $nx $ny $nt
echo ""
echo "v1 -Ofast"
gcc ver1.c -o ver1.out -Ofast
time ./ver1.out $nx $ny $nt
echo ""
echo "v2 -Ofast"
g++ ver2.cpp -o ver2.out -Ofast
time ./ver2.out $nx $ny $nt
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

