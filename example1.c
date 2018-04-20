#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <xmmintrin.h>

uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

#define XSIZE 640
#define YSIZE 480
#define IMGSIZE XSIZE * YSIZE

#ifdef ALIGN_DATA_TO_16_BYTE
#define ALIGNED_DATA __attribute__ ((aligned(16)))
#else
#define ALIGNED_DATA
#endif

struct RGB {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} ALIGNED_DATA;

struct RGB input_IMG[IMGSIZE];
unsigned char output_IMG[IMGSIZE];

struct optimize_RGB {
    unsigned char R[IMGSIZE];
    unsigned char G[IMGSIZE];
    unsigned char B[IMGSIZE];
} ALIGNED_DATA;

struct optimize_RGB opt_input_IMG;

typedef int v4si __attribute__ ((vector_size(16)));

struct simd_RGB {
    v4si R[IMGSIZE / 4];
    v4si G[IMGSIZE / 4];
    v4si B[IMGSIZE / 4];
} ALIGNED_DATA;

struct simd_RGB simd_input_IMG;

v4si simd_output_IMG[IMGSIZE / 4];

#ifdef ORIGINAL_METHOD
void convert_RGB_2_black_and_white(struct RGB *img_input, unsigned char *img_output) {
    int i;
    double op = 0;
    for(i = 0; i < IMGSIZE; i++) {
        op = (0.299 * img_input[i].R) + (0.587 * img_input[i].G) + (0.144 * img_input[i].B);
        img_output[i] = (unsigned char)op;
    }
}
#endif

#ifdef FIXED_POINT_METHOD
void convert_RGB_2_black_and_white(struct RGB *img_input, unsigned char *img_output) {
    int i;
    unsigned int op = 0;
    for(i = 0; i < IMGSIZE; i++) {
        op = (1224 * img_input[i].R) + (2404 * img_input[i].G) + (467 * img_input[i].B);
        img_output[i] = (unsigned char)(op >> 12);
    }
}
#endif


#ifdef LOOP_UNROLLING_METHOD
void convert_RGB_2_black_and_white(struct RGB *img_input, unsigned char *img_output) {
    int i;
    unsigned int op1 = 0;
    unsigned int op2 = 0;
    unsigned int op3 = 0;
    unsigned int op4 = 0;

    for(i = 0; i < IMGSIZE; i += 4) {
        op1 = (1224 * img_input[i].R) + (2404 * img_input[i].G) + (467 * img_input[i].B);
        op2 = (1224 * img_input[i + 1].R) + (2404 * img_input[i + 1].G) + (467 * img_input[i + 1].B);
        op3 = (1224 * img_input[i + 2].R) + (2404 * img_input[i + 2].G) + (467 * img_input[i + 2].B);
        op4 = (1224 * img_input[i + 3].R) + (2404 * img_input[i + 3].G) + (467 * img_input[i + 3].B);
        img_output[i] = (unsigned char)(op1 >> 12);
        img_output[i + 1] = (unsigned char)(op2 >> 12);
        img_output[i + 2] = (unsigned char)(op3 >> 12);
        img_output[i + 3] = (unsigned char)(op4 >> 12);
    }
}
#endif

#ifdef OPTIMIZED_STRUCT_METHOD
void convert_RGB_2_black_and_white(struct optimize_RGB *img_input, unsigned char *img_output) {
    int i;
    unsigned int op1 = 0;
    unsigned int op2 = 0;
    unsigned int op3 = 0;
    unsigned int op4 = 0;

    unsigned int R1 = 0;
    unsigned int R2 = 0;
    unsigned int R3 = 0;
    unsigned int R4 = 0;

    unsigned int G1 = 0;
    unsigned int G2 = 0;
    unsigned int G3 = 0;
    unsigned int G4 = 0;

    unsigned int B1 = 0;
    unsigned int B2 = 0;
    unsigned int B3 = 0;
    unsigned int B4 = 0;

#ifdef NO_INDEPENDENT_LOOP
    for(i = 0; i < IMGSIZE; i += 4) {

        R1 = 1224 * img_input->R[i];
        R2 = 1224 * img_input->R[i + 1];
        R3 = 1224 * img_input->R[i + 2];
        R4 = 1224 * img_input->R[i + 3];

        G1 = 2404 * img_input->G[i];
        G2 = 2404 * img_input->G[i + 1];
        G3 = 2404 * img_input->G[i + 2];
        G4 = 2404 * img_input->G[i + 3];

        B1 = 467 * img_input->B[i];
        B2 = 467 * img_input->B[i + 1];
        B3 = 467 * img_input->B[i + 2];
        B4 = 467 * img_input->B[i + 3];

        op1 = R1 + G1 + B1;
        op2 = R2 + G2 + B2;
        op3 = R3 + G3 + B3;
        op4 = R4 + G4 + B4;

        img_output[i] = (unsigned char)(op1 >> 12);
        img_output[i + 1] = (unsigned char)(op2 >> 12);
        img_output[i + 2] = (unsigned char)(op3 >> 12);
        img_output[i + 3] = (unsigned char)(op4 >> 12);
    }
#else
    for (i = 0; i < IMGSIZE; i += 4) {
        R1 = 1224 * img_input->R[i];
        R2 = 1224 * img_input->R[i + 1];
        R3 = 1224 * img_input->R[i + 2];
        R4 = 1224 * img_input->R[i + 3];
    }

    for (i = 0; i < IMGSIZE; i += 4) {
        G1 = 2404 * img_input->G[i];
        G2 = 2404 * img_input->G[i + 1];
        G3 = 2404 * img_input->G[i + 2];
        G4 = 2404 * img_input->G[i + 3];
    }

    for (i = 0; i < IMGSIZE; i += 4) {
        B1 = 467 * img_input->B[i];
        B2 = 467 * img_input->B[i + 1];
        B3 = 467 * img_input->B[i + 2];
        B4 = 467 * img_input->B[i + 3];
    }

    for (i = 0; i < IMGSIZE; i += 4) {
        op1 = R1 + G1 + B1;
        op2 = R2 + G2 + B2;
        op3 = R3 + G3 + B3;
        op4 = R4 + G4 + B4;

        img_output[i] = (unsigned char)(op1 >> 12);
        img_output[i + 1] = (unsigned char)(op2 >> 12);
        img_output[i + 2] = (unsigned char)(op3 >> 12);
        img_output[i + 3] = (unsigned char)(op4 >> 12);
    }
#endif
}
#endif

#ifdef SIMD_METHOD
void convert_RGB_2_black_and_white(struct simd_RGB *img_input, v4si *img_output) {
    int i = 0;
    v4si or1, og1, ob1, op1;
    v4si or2, og2, ob2, op2;
    v4si or3, og3, ob3, op3;
    v4si or4, og4, ob4, op4;

    for (; i < (IMGSIZE / 4); i += 4) {
        or1 = 1224 * img_input->R[i];
        or2 = 1224 * img_input->R[i + 1];
        or3 = 1224 * img_input->R[i + 2];
        or4 = 1224 * img_input->R[i + 3];

        og1 = 2404 * img_input->G[i];
        og2 = 2404 * img_input->G[i + 1];
        og3 = 2404 * img_input->G[i + 2];
        og4 = 2404 * img_input->G[i + 3];

        ob1 = 467 * img_input->B[i];
        ob2 = 467 * img_input->B[i + 1];
        ob3 = 467 * img_input->B[i + 2];
        ob4 = 467 * img_input->B[i + 3];

        op1 = or1 + og1 + ob1;
        op2 = or2 + og2 + ob2;
        op3 = or3 + og3 + ob3;
        op4 = or4 + og4 + ob4;

        img_output[i] = (op1 >> 12);
        img_output[i + 1] = (op2 >> 12);
        img_output[i + 2] = (op3 >> 12);
        img_output[i + 3] = (op4 >> 12);
    }
}
#endif

int
main(void)
{

    uint32_t ite_count = 0;
    asm volatile("" ::: "memory");

    uint64_t start = trace_cpu_time_now();
    for (; ite_count < 100; ite_count++) {
#ifdef OPTIMIZED_STRUCT_METHOD
        convert_RGB_2_black_and_white(&opt_input_IMG, output_IMG);
#elif defined(SIMD_METHOD)
        convert_RGB_2_black_and_white(&simd_input_IMG, simd_output_IMG);
#else
        convert_RGB_2_black_and_white(input_IMG, output_IMG);
#endif
    }

    asm volatile("" ::: "memory");

    uint64_t end = trace_cpu_time_now();

    printf("CPU cycles: %ld\n", end - start);

    return 0;
}
