//
// Created by think on 2021/7/14.
//

#ifndef _PCP_H
#define _PCP_H

#include <stdio.h>
#include <string.h>

typedef struct {
    int ProducerID;
}Product;

Product* Produce(int);
void ConsumeProduct(Product*);

typedef struct {
    Product **Stack;
    size_t Top;
}Buf;

extern Buf prodBuf;

void InitBuf(size_t);
void InsertProduct(Product*);
Product* GetProduct();

typedef enum {
    Ready,
    Waiting
}State;

typedef struct {
    int ID;
    char *Instr[8];
    size_t Cur;
    Product *Product;
    State State;
}BufUser;

extern BufUser **readyQ, **mutexQ, **emptyQ, **fullQ;
extern size_t rHead, rTail, mHead, mTail, eHead, eTail, fHead, fTail;

extern int mutex, empty, full;

extern const char *ProdInstr[];
extern const char *ConsInstr[];

#endif //_PCP_H
