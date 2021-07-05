#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "FreePartition.h"

int main() {
    puts("Requests:\nAllocate          0 <size>\nFree              1 <addr> <size>\nCheck partitions  2\nTerminate         3\n");

    freePartitions = malloc(sizeof(FreePartition));
    freePartitions->Number = 1;
    freePartitions->StartingAddress = (void*)PRESERVED_SIZE;   // 预留，不从0x0开始
    freePartitions->Length = MEMORY_SIZE - PRESERVED_SIZE;
    freePartitions->Next = NULL;

    while(1) {
        printf("Request: ");
        int isAllocate;
        scanf("%d", &isAllocate);
        switch (isAllocate) {
            case 0: {
                size_t size;
                scanf("%llu", &size);
                Allocate(size);
                break;
            }
            case 1: {
                unsigned long long addr;
                size_t size;
                scanf("%llu%llu", &addr, &size);
                Free((void *) addr, size);
                break;
            }
            case 2:
                for(FreePartition *iter = freePartitions;iter;iter = iter->Next) {
                    printf("P%hu - addr: 0x%llx, size: %llu\n", iter->Number, iter->StartingAddress, iter->Length);
                }
                break;
            case 3:
                puts("Terminated.");
                return 0;
        }
    }
}
