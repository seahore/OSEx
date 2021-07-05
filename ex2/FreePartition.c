//
// Created by think on 2021/7/5.
//

#include "FreePartition.h"
#include <stdlib.h>

FreePartition *freePartitions;

void* Allocate(size_t length) {
    for(FreePartition *prev = NULL, *next = freePartitions; next; prev = next, next = next->Next) {
        if (next->Length >= length) {
            void *ret = next->StartingAddress;
            if (next->Length == length) {
                if (!prev) {
                    FreePartition *t = freePartitions;
                    freePartitions = freePartitions->Next;
                    free(t);
                } else {
                    prev->Next = next->Next;
                    free(next);
                }
                for (FreePartition *i = next; i; i = i->Next) {
                    --i->Number;
                }
            } else {
                next->StartingAddress += length;
                next->Length -= length;
            }
            return ret;
        }
    }
}

void Free(void* addr, size_t size) {
    if(addr < (void*)0x1000) {
        return;
    }
    if(addr+size < freePartitions->StartingAddress) {
        FreePartition *part = malloc(sizeof(FreePartition));
        part->StartingAddress = addr;
        part->Length = size;
        part->Number = 1;
        part->Next = freePartitions;
        freePartitions = part;
        for(FreePartition *iter = freePartitions->Next;iter;iter = iter->Next) {
            ++iter->Number;
        }
        return;
    }
    if(addr+size == freePartitions->StartingAddress) {
        freePartitions->StartingAddress -= size;
        freePartitions->Length+=size;
        return;
    }
    for(FreePartition *prev = freePartitions, *next = freePartitions->Next; next; prev = next, next = next->Next) {
        if(addr > prev->StartingAddress + prev->Length) {
            if(addr+size < next->StartingAddress) {
                FreePartition *part = malloc(sizeof(FreePartition));
                part->StartingAddress = addr;
                part->Length = size;
                part->Number = prev->Number + 1;
                prev->Next = part;
                part->Next = next;
                for(FreePartition *i = next; i; i = i->Next) {
                    ++i->Number;
                }
                return;
            }
            if(addr+size == next->StartingAddress) {
                next->StartingAddress = addr;
                next->Length += size;
                return;
            }
        } else if(addr == prev->StartingAddress + prev->Length) {
            if(addr+size < next->StartingAddress) {
                prev->Length+=size;
                return;
            }
            if(addr+size == next->StartingAddress) {
                prev->Length+= size + next->Length;
                prev->Next = next->Next;
                free(next);
                for(FreePartition *i = prev->Next; i; i = i->Next) {
                    --i->Number;
                }
                return;
            }
        }
    }
}
