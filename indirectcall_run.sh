#!/bin/sh

echo "====RANDOM IDX -O0"
gcc -DRANDOM_IDX indirectcall.c
./a.out

echo "====FIX IDX -O0"
gcc indirectcall.c
./a.out

echo "====RANDOM IDX -O3"
gcc -O3 -DRANDOM_IDX indirectcall.c
./a.out

echo "====FIX IDX -O3"
gcc -O3 indirectcall.c
./a.out
