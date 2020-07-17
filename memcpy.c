#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>

#define L2_CACHE_HALF 1024 * 1024 / 2    // 1MB / 2
#define L2_CACHE 1024 * 1024             // 1MB
#define L3_CACHE 36608 * 1024            // 36.6MB
#define L3_CACHE_HALF 36608 * 1024 / 2   // 36.6MB / 2
#define L3_CACHE_DOUBLE 36608 * 1024 * 2 // 36.6MB * 2
#define LOOP_1M_TIMES 1000000            //1M
#define LOOP_50K_TIMES 50000             //50K
#define LOOP_5K_TIMES 5000               //5K

#define STEP_ONE_THIRD_MB 1024 * 1024 / 3 // 0.3 M
#define STEP_TEN_MB 10 * 1024 * 1024      // 10 M
#define STEP_THIRTY_MB 30 * 1024 * 1024   // 30 M

int main(int argc, char *argv[])
{
    /*Base and Loop*/
    int base = 0;
    int loop = 0;
    char *types = (char *)malloc(50 * sizeof(char));

    clock_t start, end;

    /*Array Prepare*/
    uint8_t *src_array = malloc(sizeof(uint8_t) * L3_CACHE_DOUBLE);
    uint8_t *dst_array = malloc(sizeof(uint8_t) * L3_CACHE_DOUBLE);

    /*Source Array Initialization*/
    for (int i = 0; i < L3_CACHE_DOUBLE; ++i)
    {
        src_array[i] = 0x1;
    }

#ifdef L2HALF
    base = L2_CACHE_HALF;
    loop = LOOP_1M_TIMES;
    types = "L2_CACHE_HALF";
#elif L2FULL
    base = L2_CACHE;
    loop = LOOP_1M_TIMES;
    types = "L2_CACHE";
#elif L3HALF
    base = L3_CACHE_HALF;
    loop = LOOP_50K_TIMES;
    types = "L3_CACHE_HALF";
#elif L3FULL
    base = L3_CACHE;
    loop = LOOP_5K_TIMES;
    types = "L3_CACHE";
#endif

    if (base != 0)
    {
        /*Case: Load Half of L2 Cache Data*/
        printf("--------------------- Case: MEMCPY %s Data ------------------\n", types);

        start = clock();
        for (int i = 0; i < loop; ++i)
        {
            memcpy(dst_array, src_array, base * sizeof(uint8_t));
        }
        end = clock();

        double elapsed = (double)((end - start) / CLOCKS_PER_SEC);
        double performance = (base * sizeof(uint8_t) * loop) / (1024 * 1024) / elapsed;
        printf("Done in %f seconds\n", elapsed);
        printf("Performance: %f MB/s\n", performance);
    }

    else
    {

        base = L2_CACHE_HALF;
        loop = LOOP_1M_TIMES;

        /*Case: Load Different Trunks of Data*/
        printf("------------------ Case: MEMCPY BY STEP ------------------\n");
        while (base <= sizeof(uint8_t) * L3_CACHE_DOUBLE)
        {
            if (base < L2_CACHE)
            {
                printf("------------------ Memcpy Data < L2 Cache ------------------\n");
            }
            else if (L2_CACHE == base)
            {
                printf("------------------ Memcpy Data = L2 Cache ------------------\n");
            }
            else if (base < L3_CACHE)
            {
                printf("------------------ Memcpy Data < L3 Cache ------------------\n");
            }
            else if (L3_CACHE == base)
            {
                printf("------------------ Memcpy Data = L3 Cache ------------------\n");
            }
            else
            {
                printf("------------------ Memcpy Data > L3 Cache ------------------\n");
            }

            printf("Memcpy %f MB of Data\n", (float)base / (1024 * 1024));

            start = clock();
            for (int i = 0; i < loop; ++i)
            {
                memcpy(dst_array, src_array, base);
            }
            end = clock();

            double elapsed = (double)((end - start) / CLOCKS_PER_SEC);
            double performance = (base * sizeof(uint8_t) * loop) / (1024 * 1024) / elapsed;
            printf("Done in %f seconds\n", elapsed);
            printf("Performance: %f MB/s\n\n", performance);

            if (base < L2_CACHE)
            {
                base += STEP_ONE_THIRD_MB * sizeof(uint8_t);
            }
            else
            {
                base += STEP_THIRTY_MB * sizeof(uint8_t);
                loop = LOOP_5K_TIMES;
            }
        }
    }
    // double elapsed = (double)((end - start) / CLOCKS_PER_SEC);
    // double performance = (L2_CACHE_HALF * sizeof(uint8_t) * 1000000) / (1024 * 1024) / elapsed;
    // printf("Done in %f seconds\n", elapsed);
    // printf("Performance: %f MB/s\n", performance);

    // /*Case 2: Load Double of L2 Cache Data*/
    // printf("--------------------- Case 2: MEMCPY L2_CACHE_Double Data ------------------\n");

    // start = clock();
    // for (int i = 0; i < 1000000; ++i)
    // {
    //     memcpy(dst_array, src_array, L2_CACHE_DOUBLE * sizeof(uint8_t));
    // }
    // end = clock();

    // elapsed = (double)((end - start) / CLOCKS_PER_SEC);
    // performance = (L2_CACHE_Double * sizeof(uint8_t) * 1000000) / (1024 * 1024) / elapsed;
    // printf("Done in %f seconds\n", elapsed);
    // printf("Performance: %f MB/s\n", performance);

    free(src_array);
    free(dst_array);

    exit(EXIT_SUCCESS);
}
