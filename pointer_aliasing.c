#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ARRAY_LEN (1 << 24)

static inline uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

#ifdef PTR_ALIAS
static void
pointer_aliasing_f(uint32_t *a, uint32_t *b)
{
    uint64_t n = ARRAY_LEN;
    while (n--) {
        *(a++) = *b + 1;
    }
}
#endif

#ifdef ANTI_PTR_ALIAS
static void
pointer_aliasing_f(uint32_t *__restrict a, uint32_t *__restrict b)
{
    uint64_t n = ARRAY_LEN;
    while (n--) {
        *(a++) = *b + 1;
    }
}
#endif

int
main(void)
{
    uint32_t *arrayA = (uint32_t *)malloc(ARRAY_LEN * sizeof(uint32_t));

    int i = 0;
    for(; i < ARRAY_LEN; i++) {
            arrayA[i] = i;
    }

#ifdef PTR_ALIAS
    uint32_t *p = &arrayA[8];
#endif

#ifdef ANTI_PTR_ALIAS
    uint32_t v = 8;
    uint32_t *p = &v;
#endif

    /*warm up*/
    pointer_aliasing_f(arrayA, p);

    uint64_t start = trace_cpu_time_now();

    pointer_aliasing_f(arrayA, p);

    uint64_t end = trace_cpu_time_now();

    printf("arrayA[8] = %d, CPU cycles: %ld\n", arrayA[8], end - start);

    return 0;
}
