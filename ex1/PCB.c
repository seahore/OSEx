//
// Created by Administrator on 2021/7/4.
//

#include <stdlib.h>
#include "PCB.h"

PCB *readyQueue;

PCB* CreatePCB(Word pid, DWord timeConsuming, Byte priority) {
    PCB* pcb = malloc(sizeof(PCB));
    pcb->PID = pid;
    pcb->TimeRemaining = timeConsuming;
    pcb->Priority = priority;
    pcb->next = NULL;
    return pcb;
}

void PCBEnque(PCB *process) {
    process->status = Ready;
    if(!readyQueue) {
        readyQueue = process;
        return;
    }
    if(readyQueue->Priority < process->Priority) {
        process->next = readyQueue;
        readyQueue = process;
        return;
    }
    PCB *iter = readyQueue;
    while(iter->next) {
        if(iter->Priority >= process->Priority && iter->next->Priority < process->Priority) {
            process->next = iter->next;
            iter->next = process;
            return;
        }
        iter = iter->next;
    }
    iter->next = process;
}

void PCBReenque() {
    if(readyQueue->Priority > 1) {
        --readyQueue->Priority;
    }
    PCB *tmp = readyQueue;
    readyQueue = readyQueue->next;
    tmp->next = NULL;
    PCBEnque(tmp);
}

PCB* PCBDeque() {
    readyQueue->status = End;
    PCB *tmp = readyQueue;
    readyQueue = readyQueue->next;
    return tmp;
}