
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define LOOP_ITERATION 100000000

uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

typedef uint32_t (*func_pointer_1)(void*);
typedef void (*func_pointer_2)(void*);
typedef void (*func_pointer_3)(void*);

struct abstraction_layer {
        func_pointer_1 fp_1;
        func_pointer_2 fp_2;
        func_pointer_3 fp_3;
};

uint32_t func_point_1_1(void *arg)
{
        uint32_t *i = (uint32_t *)arg;
        (*i)++;
        return *i;
}

uint32_t func_point_1_2(void *arg)
{
        uint32_t *i = (uint32_t *)arg;
        (*i) += 2;
        return *i;
}

int main()
{
        struct abstraction_layer al_1 = {.fp_1 = func_point_1_1,
                                         .fp_2 = NULL,
                                         .fp_3 = NULL };

        struct abstraction_layer al_2 = {.fp_1 = func_point_1_2,
                                         .fp_2 = NULL,
                                         .fp_3 = NULL };

        asm volatile("" ::: "memory");
        uint64_t start = trace_cpu_time_now();

        int i = 0;
        uint32_t arg = 0;
        uint32_t ret = 0;
        for(; i < LOOP_ITERATION; i++) {
            ret = al_1.fp_1((void *)&arg);
        }

        asm volatile("" ::: "memory");
        uint64_t end = trace_cpu_time_now();
        printf("ret: %d, CPU cycles: %ld\n", ret, end - start);

        asm volatile("" ::: "memory");
        start = trace_cpu_time_now();

        arg = 0;
        for(i = 0; i < LOOP_ITERATION; i++) {
            if (al_2.fp_1 == func_point_1_2) {
                ret = al_2.fp_1((void *)&arg);
            }
        }

        asm volatile("" ::: "memory");
        end = trace_cpu_time_now();
        printf("ret: %d, CPU cycles: %ld\n", ret, end - start);
}
