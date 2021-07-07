#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "PCB.h"

void Run() {
    int cnt = 1;
    while(1) {
        printf("%d\t", cnt++);
        printf("Ready queue: ");
        for(PCB *iter = readyQueue;iter;iter=iter->next){
            printf("%hu, ", iter->PID);
        }
        --readyQueue->TimeRemaining;
        if (!readyQueue->TimeRemaining) {
            printf("process %hu runs and then be completed. ", readyQueue->PID);
            PCBDeque();
        } else {
            printf("process %hu runs. ", readyQueue->PID);
            PCBReenque();
        }
        if (!readyQueue) {
            puts("No process is ready now.");
            return;
        }
        putchar('\n');
    }
}


int main() {
    int cnt;
    printf("Enter the number of process: ");
    scanf("%d", &cnt);
    if (cnt > 0) {
        for (int i = 0; i < cnt; ++i) {
            printf("Register %d/%d (<PID> <Time> <Prior>): ", i + 1, cnt);
            Word pid;
            DWord time;
            unsigned int prior;
            scanf("%hu%lu%hhu", &pid, &time, &prior);
            PCBEnque(CreatePCB(pid, time, prior));
        }
    }
    Run();
    puts("Evaluation has been terminated.");
    return 0;
}
