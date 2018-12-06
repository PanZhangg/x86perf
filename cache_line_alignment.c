#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <xmmintrin.h>
#include <sched.h>
#include <pthread.h>

struct counter_t {
    uint32_t front_padding[15];
    uint32_t c1;
    /* 64 bytes */
    uint32_t c2;
};

struct pthread_arg_t {
    uint32_t *cnt;
    int cpu_id;
    uint64_t upper_limit;
};

static uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}

inline void
clflush(volatile void *p)
{
    asm volatile ("clflush (%0)" :: "r"(p));
}

void *
inc_count(void *arg)
{
    pid_t cur_tid = syscall(SYS_gettid);
    cpu_set_t mask;
    struct pthread_arg_t *thread_arg = (struct pthread_arg_t *)arg;
    int cpu_id = thread_arg->cpu_id;
    CPU_ZERO(&mask);
    CPU_SET(cpu_id, &mask);

    if (sched_setaffinity(cur_tid, sizeof(mask), &mask) == -1) {
        printf("CPU affinity set failded: %d\n", cpu_id);
    }
    uint64_t i = 0;
    uint64_t limit = thread_arg->upper_limit;

    uint64_t start = trace_cpu_time_now();
    for(i = 0; i < limit; i++) {
        (*(thread_arg->cnt))++;
    }
    uint64_t end = trace_cpu_time_now();

    printf("Time: %ld\n", end - start);
}

int main() {
    uint64_t limit = 0;
    printf("input count limit:\n");
    scanf("%ld", &limit);

    pthread_t tid[2];

    struct counter_t counter __attribute__((aligned(64)));

    //struct counter_t counter;
    struct counter_t *cp = &counter;
    if ((unsigned long)cp % 64 != 0) {
        printf("counter struct is not 64 byte aligned\n");
        exit(0);
    }

    memset(&counter, 0, sizeof(counter));
    struct pthread_arg_t arg1 = {.cnt = &counter.c1,
                         .cpu_id = 2,
                         .upper_limit = limit};

    struct pthread_arg_t arg2 = {.cnt = &counter.c2,
                         .cpu_id = 3,
                         .upper_limit = limit};

    int i;
    int count = 0;
    uint64_t start = trace_cpu_time_now();
    for(i = 0; i < limit; i++) {
        count++;
    }
    uint64_t end = trace_cpu_time_now();
    printf("Single Thread Time: %ld\n", end - start);

	/* flush cache contains address of cp*/
	clflush(cp);

    pthread_create(&tid[0], NULL, (void *)inc_count, &arg1);
    pthread_create(&tid[1], NULL, (void *)inc_count, &arg2);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    printf("arg cnt: %ld, %ld\n", *(arg1.cnt), *(arg2.cnt));
    return 0;
}
