#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

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

int getCMDSize(int argc1, char *argv1[]){
    int opt, flags=0;
    char *avalue, *bvalue;

    char *optstring = "s:";
    while ((opt = getopt(argc1, argv1, optstring)) != -1)
    {
        switch (opt)
        {
        case 's':
            flags = 1;
            avalue = optarg;
            break;
        default:
            flags = 5;
        }
    }
    
    if(flags==1){
        return atoi(avalue);
    }
    else{
        return 0;
    }
}

int main(int argc, char *argv[])
{

    /*Base and Loop*/
    int base = 0;
    int loop = LOOP_1M_TIMES;
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

    double *input_value;
    int input_size = (int)getCMDSize(argc, argv);
    printf("The size input is : %dKB\n", input_size);
    int size_in_bytes = input_size * 1024;
 
    if (input_size != 0)
    {
        /*Case:  Memcpy specified data*/
    
        printf("--------------------- Case: MEMCPY %dKB Data ------------------\n", input_size);

        start = clock();
        for (int i = 0; i < loop; ++i)
        {
            src_array[i]++;
            memcpy(dst_array, src_array, size_in_bytes * sizeof(uint8_t));
        }
        end = clock();

        double elapsed = (double)((end - start) / CLOCKS_PER_SEC);
        double performance = (size_in_bytes * sizeof(uint8_t) * loop) / (1024 * 1024) / elapsed;
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


    free(src_array);
    free(dst_array);

    exit(EXIT_SUCCESS);
}

