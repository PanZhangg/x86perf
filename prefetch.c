#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "benchmark.h"

#define ARRAY_LEN 65535
#define CACHE_LINE_LEN 64
#define PREFETCH_STEP 4
#define STEP_LEN (CACHE_LINE_LEN * PREFETCH_STEP)

inline uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

int *
init_array(void)
{
    int *a = (int *)malloc(sizeof(int) * ARRAY_LEN);
    return a;
}

inline static
void array_data_process(int *data)
{
}

int
main(void)
{
    int *array = init_array();

    int i = 0;

    for(i = 0; i < ARRAY_LEN; i += STEP_LEN) {
        array_data_process(array + i);
    }

//#ifdef INDIRECT_CALL
//BEST_TIME_NOCHECK(call_ops(), ,1000000, 1, 1);
//#else
//BEST_TIME_NOCHECK(call_ops_directly(), ,1000000, 1, 1);
//#endif

    return 0;
}
