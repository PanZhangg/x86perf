#!/bin/sh

echo "PERF OPTIMIZE EXAMPLE"

echo "======================="
echo "ORIGINAL METHOD"
echo "======================="

bin_name="example1_original"
echo "No compiler optimize:"
gcc -g example1.c -D ORIGINAL_METHOD -o "$bin_name"
./"$bin_name"

echo "Data aligned:"
gcc -g example1.c -D ORIGINAL_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D ORIGINAL_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D ORIGINAL_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O3 optimize:"
gcc -g -O3 example1.c -D ORIGINAL_METHOD -o example
./example

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D ORIGINAL_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "======================="
echo "FIXED_POINT_METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D FIXED_POINT_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D FIXED_POINT_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D FIXED_POINT_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D FIXED_POINT_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O3 optimize:"
gcc -g -O3 example1.c -D FIXED_POINT_METHOD -o example
./example

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D FIXED_POINT_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "======================="
echo "LOOP_UNROLLING_METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D LOOP_UNROLLING_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D LOOP_UNROLLING_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O2 optimize:"
gcc -g -O2 example1.c -D LOOP_UNROLLING_METHOD -o example
./example

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D LOOP_UNROLLING_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "-O3 optimize:"
gcc -g -O3 example1.c -D LOOP_UNROLLING_METHOD -o example
./example

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D LOOP_UNROLLING_METHOD -D ALIGN_DATA_TO_16_BYTE -o example
./example

echo "======================="
echo "OPTIMIZED_STRUCT_METHOD_NO_INDEPENDENT_LOOP"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o example
./example

echo "Data aligned:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -D ALIGN_DATA_TO_16_BYTE -D NO_INDEPENDENT_LOOP -o example
./example

bin_name="example1_opt_no_idpdt_loop_O2"
echo "-O2 optimize:"
gcc -g -O2 -ftree-vectorize -msse2 example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o $bin_name
./$bin_name
gcc -g -S -O2 example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o "$bin_name.s"

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -ftree-vectorize -msse2 -D OPTIMIZED_STRUCT_METHOD -D ALIGN_DATA_TO_16_BYTE -D NO_INDEPENDENT_LOOP -o example
./example

bin_name="example1_opt_no_idpdt_loop_O3"
echo "-O3 optimize:"
gcc -g -O3 example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o $bin_name
./$bin_name
gcc -g -S -O3 example1.c -D OPTIMIZED_STRUCT_METHOD -D NO_INDEPENDENT_LOOP -o "$bin_name.s"

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D OPTIMIZED_STRUCT_METHOD -D ALIGN_DATA_TO_16_BYTE -D NO_INDEPENDENT_LOOP -o example
./example


echo "======================="
echo "OPTIMIZED_STRUCT_METHOD_WITH_INDEPENDENT_LOOP"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D OPTIMIZED_STRUCT_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D ALIGN_DATA_TO_16_BYTE -D OPTIMIZED_STRUCT_METHOD -o example
./example

bin_name="example1_opt_idpdt_loop_O2"
echo "-O2 optimize:"
gcc -g -O2 -ftree-vectorize -msse2 example1.c -D OPTIMIZED_STRUCT_METHOD -o $bin_name
./$bin_name
gcc -g -S -O2 example1.c -D OPTIMIZED_STRUCT_METHOD -o "bin_name.s"

bin_name="example1_opt_idpdt_loop_O2_aligned"
echo "-O2 optimize AND data aligned:"
gcc -g -O2 -ftree-vectorize -msse2 example1.c -D ALIGN_DATA_TO_16_BYTE -D OPTIMIZED_STRUCT_METHOD -o $bin_name
./$bin_name

bin_name="example1_opt_idpdt_loop_O3"
echo "-O3 optimize:"
gcc -g -O3 example1.c -D OPTIMIZED_STRUCT_METHOD -o $bin_name
./$bin_name
gcc -g -S -O3 example1.c -D OPTIMIZED_STRUCT_METHOD -o $bin_name.s

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D ALIGN_DATA_TO_16_BYTE -D OPTIMIZED_STRUCT_METHOD -o example
./example

echo "======================="
echo "SIMD_METHOD"
echo "======================="

echo "No compiler optimize:"
gcc -g example1.c -D SIMD_METHOD -o example
./example

echo "Data aligned:"
gcc -g example1.c -D ALIGN_DATA_TO_16_BYTE -D SIMD_METHOD -o example
./example

bin_name="example1_simd"
echo "-O2 optimize:"
gcc -g -O2 example1.c -D SIMD_METHOD -o $bin_name
./$bin_name

echo "-O2 optimize AND data aligned:"
gcc -g -O2 example1.c -D ALIGN_DATA_TO_16_BYTE -D SIMD_METHOD -o example
./example

echo "-O3 optimize:"
gcc -g -O3 example1.c -D SIMD_METHOD -o example
./example

echo "-O3 optimize AND data aligned:"
gcc -g -O3 example1.c -D ALIGN_DATA_TO_16_BYTE -D SIMD_METHOD -o example
./example
