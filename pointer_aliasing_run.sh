#!/bin/sh

gcc -DPTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out

gcc -DANTI_PTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out

gcc -O2 -DPTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out

gcc -O2 -DANTI_PTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out


gcc -O3 -DPTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out

gcc -O3 -DANTI_PTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out


gcc -O4 -DPTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out

gcc -O4 -DANTI_PTR_ALIAS pointer_aliasing.c
./a.out
#perf stat -ddd ./a.out
