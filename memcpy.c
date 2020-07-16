#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#define L2_CACHE_Half 1024 * 1024 / 2   // 1MB / 2
#define L2_CACHE_Double 1024 * 1024 * 2 // 1MB * 2
#define L3_CACHE 36608 * 1024 * 2       // 36.6MB * 2

int main(int argc, char *argv[])
{
    clock_t start, end;

    /*Array Prepare*/
    uint8_t *l3double_array = malloc(sizeof(uint8_t) * L3_CACHE);
    uint8_t *dst_array = malloc(sizeof(uint8_t) * L3_CACHE);

    for (int i = 0; i < L3_CACHE; ++i)
    {
        l3double_array[i] = 0x1;
    }
    /*Case 1: Load Half of L2 Cache Data*/
    printf("--------------------- Case 1: MEMCPY L2_CACHE_Half Data ------------------\n");

    start = clock();
    for (int i = 0; i < 1000000; ++i)
    {
        memcpy(dst_array, l3double_array, L2_CACHE_Half * sizeof(uint8_t));
    }
    end = clock();

    double elapsed = (double)((end - start) / CLOCKS_PER_SEC);
    double performance = (L2_CACHE_Half * sizeof(uint8_t) * 1000000) / (1024 * 1024) / elapsed;
    printf("Done in %f seconds\n", elapsed);
    printf("Performance: %f MB/s\n", performance);

    /*Case 2: Load Double of L2 Cache Data*/
    printf("--------------------- Case 2: MEMCPY L2_CACHE_Double Data ------------------\n");

    start = clock();
    for (int i = 0; i < 1000000; ++i)
    {
        memcpy(dst_array, l3double_array, L2_CACHE_Double * sizeof(uint8_t));
    }
    end = clock();

    elapsed = (double)((end - start) / CLOCKS_PER_SEC);
    performance = (L2_CACHE_Double * sizeof(uint8_t) * 1000000) / (1024 * 1024) / elapsed;
    printf("Done in %f seconds\n", elapsed);
    printf("Performance: %f MB/s\n", performance);

    free(l3double_array);
    free(dst_array);

    exit(EXIT_SUCCESS);
}
