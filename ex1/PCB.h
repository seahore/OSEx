//
// Created by Administrator on 2021/7/4.
//

#ifndef _PCB_H
#define _PCB_H

#include "defs.h"

typedef enum{
     Ready = 0,
    End = 1
}Status;

typedef struct PCB {
    Word PID;
    DWord TimeRemaining;
    Status status;
    Byte Priority;
    struct PCB* next;
}PCB;

extern PCB *readyQueue;

PCB* CreatePCB(Word, DWord, Byte);
void PCBEnque(PCB*);
void PCBReenque();
PCB* PCBDeque();

#endif //_PCB_H
