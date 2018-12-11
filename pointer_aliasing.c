#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "benchmark.h"

#define ARRAY_LEN (1 << 24)

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
    uint32_t v = arrayA[8];
    uint32_t *p = &v;
#endif

    BEST_TIME_NOCHECK(pointer_aliasing_f(arrayA, p), ,10,1,1);

    return 0;
}
