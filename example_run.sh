#!/bin/bash

echo "PERF OPTIMIZE EXAMPLE"

echo "======================="
echo "ORIGINAL METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D ORIGINAL_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D ORIGINAL_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D ORIGINAL_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D ORIGINAL_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "======================="
echo "FIXED_POINT_METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D FIXED_POINT_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D FIXED_POINT_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D FIXED_POINT_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D FIXED_POINT_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "======================="
echo "LOOP_UNROLLING_METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D LOOP_UNROLLING_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D LOOP_UNROLLING_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D LOOP_UNROLLING_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D LOOP_UNROLLING_METHOD -D ALIGN_DATA_TO_64_BYTE -o example
./example

echo "======================="
echo "OPTIMIZED_STRUCT_METHOD_NO_INDEPENDENT_LOOP"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o example
./example

echo "Data aligned:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -D ALIGN_DATA_TO_64_BYTE -D NO_INDEPENDENT_LOOP -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D OPTIMIZED_STRUCT_METHOD -D ALIGN_DATA_TO_64_BYTE -D NO_INDEPENDENT_LOOP -o example
./example


echo "======================="
echo "OPTIMIZED_STRUCT_METHOD_WITH_INDEPENDENT_LOOP"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D ALIGN_DATA_TO_64_BYTE -D OPTIMIZED_STRUCT_METHOD -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D OPTIMIZED_STRUCT_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D ALIGN_DATA_TO_64_BYTE -D OPTIMIZED_STRUCT_METHOD -o example
./example
