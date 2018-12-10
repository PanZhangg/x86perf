#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ARRAY_LEN ( 1 << 16)

static inline uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

static void
pointer_aliasing_f(uint32_t *a, uint32_t *b)
{
    uint64_t n = ARRAY_LEN;
    while (n--) {
        *(a++) = *(b++);
    }
}

static void
anti_pointer_aliasing_f(uint32_t *__restrict a, uint32_t *__restrict b)
{
    uint64_t n = ARRAY_LEN;
    while (n--) {
        *(a++) = *(b++);
    }
}

int
main(void)
{
    uint32_t arrayA[ARRAY_LEN];
    uint32_t arrayB[ARRAY_LEN];

    asm volatile("" ::: "memory");

    uint64_t start = trace_cpu_time_now();

    pointer_aliasing_f(&arrayA[0], &arrayB[0]);

    asm volatile("" ::: "memory");

    uint64_t end = trace_cpu_time_now();

    printf("CPU cycles: %ld\n", end - start);

    asm volatile("" ::: "memory");

    start = trace_cpu_time_now();

    anti_pointer_aliasing_f(&arrayA[0], &arrayB[0]);

    asm volatile("" ::: "memory");

    end = trace_cpu_time_now();

    printf("CPU cycles: %ld\n", end - start);

    return 0;
}
