#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "PCB.h"

void Run() {
    int cnt = 1;
    while(1) {
        printf("%d\t", cnt++);
        --readyQueue->TimeRemaining;
        if (!readyQueue->TimeRemaining) {
            printf("Process %hu has been completed. ", readyQueue->PID);
            PCBDeque();
        } else {
            printf("Process %hu: time remaining: %lu -> %lu, priority: %hhu -> %hhu ",
                   readyQueue->PID,
                   readyQueue->TimeRemaining + 1,
                   readyQueue->TimeRemaining,
                   readyQueue->Priority,
                   readyQueue->Priority > 1 ? readyQueue->Priority - 1 : 1);
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
    for (int i = 0; i < cnt; ++i) {
        printf("Process %d (<PID> <Time> <Prior>): ", i);
        Word pid;
        DWord time;
        unsigned int prior;
        scanf("%hu%lu%hhu", &pid, &time, &prior);
        PCBEnque(CreatePCB(pid, time, prior));
    }
    Run();
    puts("Evaluation has been terminated.");
    return 0;
}
