#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "benchmark.h"

#define OP_TYPE_NUM 5
#define RAND_ARRAY_LEN 1024

#define FUNC_RETURN_TYPE void
#define FUNC_PARAMETER void

#define OPS \
    _(open) \
    _(close) \
    _(write) \
    _(read) \
    _(add) \
    _(delete)

#define _(op) typedef FUNC_RETURN_TYPE (*op)(FUNC_PARAMETER);
OPS
#undef _

enum types {
    red,
    blue,
    yellow,
    black,
    white
};

#define LIST \
    _(red) \
    _(blue)\
    _(yellow)\
    _(black)\
    _(white)

#define FUNC_BODY {int i=0; i++;}

#undef FUNC_RETURN_TYPE
#define FUNC_RETURN_TYPE static void

#define _(color) FUNC_RETURN_TYPE open_##color(FUNC_PARAMETER) FUNC_BODY \
    FUNC_RETURN_TYPE close_##color(FUNC_PARAMETER) FUNC_BODY \
    FUNC_RETURN_TYPE write_##color(FUNC_PARAMETER) FUNC_BODY \
    FUNC_RETURN_TYPE read_##color(FUNC_PARAMETER) FUNC_BODY \
    FUNC_RETURN_TYPE add_##color(FUNC_PARAMETER) FUNC_BODY \
    FUNC_RETURN_TYPE delete_##color(FUNC_PARAMETER) FUNC_BODY

LIST

#undef _

struct op {
    open open_fp;
    close close_fp;
    write write_fp;
    read read_fp;
    add add_fp;
    delete delete_fp;
};

struct op ops[OP_TYPE_NUM];

int rand_array[RAND_ARRAY_LEN];

static
void call_ops(void) {
    int i = 0;
    for(; i < RAND_ARRAY_LEN; i++) {
        int idx = rand_array[i];
        ops[idx].open_fp();
    }
}

static
void call_ops_directly(void) {
    int i = 0;
    for(; i < RAND_ARRAY_LEN; i++) {
        int idx = rand_array[i];
        switch(idx) {
        #define _(color) case color: open_##color(); break;
        LIST
        #undef _
            default: open_red(); break;
        }
    }
}

int
main(void)
{
#define _(color) ops[color].open_fp = &open_##color; \
    ops[color].close_fp = &close_##color; \
    ops[color].write_fp = &write_##color; \
    ops[color].read_fp = &read_##color; \
    ops[color].add_fp = &add_##color; \
    ops[color].delete_fp = &delete_##color;

LIST

#undef _
    int i = 0;
    for(; i < RAND_ARRAY_LEN; i++) {
        srand((unsigned)time(NULL));
        rand_array[i] = rand() % OP_TYPE_NUM;
        rand_array[i] = 1;
    }

BEST_TIME_NOCHECK(call_ops(), ,1000000, 1, 1);

BEST_TIME_NOCHECK(call_ops_directly(), ,1000000, 1, 1);


    return 0;
}
