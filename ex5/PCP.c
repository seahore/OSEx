//
// Created by think on 2021/7/14.
//

#include "PCP.h"

#include <stdlib.h>

Buf prodBuf;

void InitBuf(size_t size) {
    prodBuf.Stack = malloc(sizeof(Product *) * size);
    prodBuf.Top = 0;
}

Product* Produce(int val){
    Product *p = malloc(sizeof(Product));
    p->ProducerID = val;
    return p;
}

void ConsumeProduct(Product* p) {
    free(p);
}


void InsertProduct(Product *p) {
    prodBuf.Stack[prodBuf.Top++] = p;
}

Product* GetProduct() {
    return prodBuf.Stack[--prodBuf.Top];
}

BufUser **readyQ, **mutexQ, **emptyQ, **fullQ;
size_t rHead, rTail, mHead, mTail, eHead, eTail, fHead, fTail;

int mutex, empty, full;

const char *ProdInstr[] = {
        "produce",
        "p empty",
        "p mutex",
        "insert",
        "v mutex",
        "v full",
        "loop",
        ""
};
const char *ConsInstr[] = {
        "p full",
        "p mutex",
        "fetch",
        "v mutex",
        "v empty",
        "consume",
        "loop",
        ""
};