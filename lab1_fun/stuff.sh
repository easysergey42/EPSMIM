#!/bin/bash
gcc make_array.c -o make_array
./make_array 600
gnuplot gnuplotscript
xdg-open binary.png
