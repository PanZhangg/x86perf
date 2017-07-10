#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define N 128

int a[N][N], b[N][N], c[N][N], d[N][N];

void
init_arrays()
{
    int i, j;
    for (i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
        	a[i][j] = i + j;
        	b[i][j] = i + j;
        	c[i][j] = i + j;
        	d[i][j] = i + j;
    	}
	}
}

#ifdef LOOP_DIST
void
foo(void)
{
    int i, j;
    for (i = 1; i < N; i++) {
		for (j = 1; j < N; j ++) {
			a[i][j] = b[i][j] + c[i][j];
		}
		for (j = 1; j < N; j ++) {
			d[i][j] = a[i - 1][j - 1] * 2;
		}
    }

}

#elif LOOP_DIST_COMPLETE
void
foo(void)
{
    int i, j;
    for (i = 1; i < N; i++) {
		for (j = 1; j < N; j ++) {
			a[i][j] = b[i][j] + c[i][j];
		}
	}

    for (i = 1; i < N; i++) {
		for (j = 1; j < N; j ++) {
			d[i][j] = a[i - 1][j - 1] * 2;
		}
    }

}

#else

void
foo(void)
{
    int i, j;
    for (i = 1; i < N; i++) {
		for (j = 1; j < N; j ++) {
			a[i][j] = b[i][j] + c[i][j];
			d[i][j] = a[i - 1][j - 1] * 2;
		}
    }
}

#endif

uint64_t
trace_cpu_time_now(void)
{
    uint32_t a, d;
    asm volatile ("rdtsc":"=a" (a), "=d" (d));
    return (uint64_t)a + ((uint64_t)d << (uint64_t)32);
}


int
main(void)
{


    init_arrays();

    uint64_t start = trace_cpu_time_now();

    asm volatile("" ::: "memory");

    foo();

    asm volatile("" ::: "memory");

    uint64_t end = trace_cpu_time_now();

    printf("CPU cycles: %ld\n", end - start);

    return 0;
}
