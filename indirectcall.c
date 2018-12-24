#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "benchmark.h"

#define OP_TYPE_NUM 5

typedef void (*open)(void);
typedef void (*close)(void);
typedef void (*write)(void);
typedef void (*read)(void);
typedef void (*add)(void);
typedef void (*delete)(void);

enum types {
    red,
    blue,
    yellow,
    black,
    white
};

void
open_type_red(void){
    
}

void
open_type_blue(void){
    
}

struct op {
    open open_fp;
    close close_fp;
    write write_fp;
    read read_fp;
    add add_fp;
    delete delete_fp;
};

struct op ops[OP_TYPE_NUM];

int
main(void)
{
    return 0;
}
