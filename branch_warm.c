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

static uint32_t result[2];
static uint32_t array[ARRAY_LEN];

inline static void
process_a_when_less(uint32_t *a) {
    result[1] = *a + 1;
}

inline static void
process_a_when_larger(uint32_t *a, uint8_t flag) {
    result[flag] = *a - 1;
}

int
main(void)
{

    uint32_t i = 0;
    for (; i < ARRAY_LEN; i++) {
        array[i] = rand() % 256;
    }

    asm volatile("" ::: "memory");

    uint64_t start = trace_cpu_time_now();
    uint64_t sum = 0;
    uint32_t ite_count = 0;

#ifdef WARM
    for (; ite_count < 10000; ite_count++) {
        for (i = 0; i < ARRAY_LEN; i++) {
            result[0] = 0;
            if (array[i] < 128) {
                process_a_when_larger(&array[i], 0);
                process_a_when_less(&array[i]);
            } else {
                process_a_when_larger(&array[i], 1);
            }
            sum += result[1];
        }
    }
#else
    for (; ite_count < 10000; ite_count++) {
        for (i = 0; i < ARRAY_LEN; i++) {
            if (array[i] < 128) {
                sum += array[i] + 1;
            } else {
                sum += array[i] - 1;
            }
        }
    }
#endif

    asm volatile("" ::: "memory");

    uint64_t end = trace_cpu_time_now();

    printf("Sum: %ld, CPU cycles: %ld\n", sum, (end - start) / 10000);

    return 0;
}
