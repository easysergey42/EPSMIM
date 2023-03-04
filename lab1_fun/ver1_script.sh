#!/bin/bash
gcc ver1.c -o ver1.out
./ver1.out 100 100 5000 > /dev/null
gnuplot gnuplotscript
xdg-open binary.png

