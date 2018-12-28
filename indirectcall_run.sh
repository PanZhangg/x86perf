#!/bin/sh

#Related raw events of Haswell microarchitecture CPU

EVENT1=' -e cpu/event=0x08,umask=0x01,name=ALL_TLB_MISS_PAGE_WALK/'
EVENT2=' -e cpu/event=0x3C,umask=0x01,name=UNHALTED_CYC/'
EVENT3=' -e cpu/event=0x85,umask=0x01,name=ITLB_PAGE_WALK/'
EVENT4=' -e cpu/event=0x85,umask=0x02,name=ITLB_4K_PAGE_WALK/'
EVENT5=' -e cpu/event=0x85,umask=0x10,name=ITLB_MISS_DURATION/'
EVENT6=' -e cpu/event=0x85,umask=0x20,name=ITLB_MISS_HIT_STLB_PAGE_WAKE/'
EVENT7=' -e cpu/event=0x85,umask=0x60,name=ITLB_MISS_HIT_STLB/'
EVENT8=' -e cpu/event=0xAE,umask=0x01,name=ITLB_FLUSH/'
EVENT9=' -e cpu/event=0xBC,umask=0x21,name=ITLB_LOAD_HIT/'
EVENT10=' -e cpu/event=0xA2,umask=0x01,name=STALL_RESOURCE/'
EVENT11=' -e cpu/event=0xA2,umask=0x04,name=STALL_RS/'
PERF_STAT='perf stat'
EVENTS=$EVENT10$EVENT11
PERF_CMD=$PERF_STAT$EVENTS

echo "====RANDOM IDX -O0"
gcc -DRANDOM_IDX -DINDIRECT_CALL indirectcall.c
$PERF_CMD ./a.out

echo "====FIX IDX -O0"
gcc -DINDIRECT_CALL indirectcall.c
$PERF_CMD ./a.out

echo "====RANDOM DX -O0"
gcc -DRANDOM_IDX indirectcall.c
$PERF_CMD ./a.out

echo "====FIX IDX -O0"
gcc indirectcall.c
$PERF_CMD ./a.out

#echo "====RANDOM IDX -O3"
#gcc -O3 -DRANDOM_IDX indirectcall.c
#./a.out
#
#echo "====FIX IDX -O3"
#gcc -O3 indirectcall.c
#./a.out
