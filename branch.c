#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ARRAY_LEN ( 1 << 16 )

uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

static int
qsort_cmp(const void *a, const void *b)
{
    if ( *(const uint32_t *)a < *(const uint32_t *)b ) {
        return -1;
    } else if ( *(const uint32_t *)a == *(const uint32_t *)b ) {
        return 0;
    }
    return 1;
}

int
main(void)
{
    uint32_t array[ARRAY_LEN];

    uint32_t i = 0;
    for (; i < ARRAY_LEN; i++) {
        array[i] = rand() % 256;
    }

    asm volatile("" ::: "memory");

    uint64_t start = trace_cpu_time_now();
    #ifdef PRE_SORT
    qsort(&array, ARRAY_LEN, sizeof(uint32_t), qsort_cmp);
    printf("Sorted array\n");
    #endif
    uint64_t sum = 0;
    uint32_t ite_count = 0;
    for (; ite_count < 10000; ite_count++) {
        for (i = 0; i < ARRAY_LEN; i++) {
            if (array[i] < 128) {
                sum += array[i];
            }
        }
    }

    asm volatile("" ::: "memory");

    uint64_t end = trace_cpu_time_now();

    printf("Sum: %ld, CPU cycles: %ld\n", sum, end - start);

    return 0;
}
