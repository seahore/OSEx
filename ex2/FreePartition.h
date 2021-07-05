//
// Created by think on 2021/7/5.
//

#ifndef _FREE_PARTITION_H
#define _FREE_PARTITION_H

#include "defs.h"

typedef struct FreePartition {
    Word Number;
    void* StartingAddress;
    size_t Length;
    struct FreePartition *Next;
}FreePartition;

extern FreePartition *freePartitions;

void* Allocate(size_t);

void Free(void*, size_t);

#endif //_FREE_PARTITION_H
