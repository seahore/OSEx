//
// Created by think on 2021/7/8.
//

#include <stdio.h>
#include <stdlib.h>
#include "PCP.h"

int main() {
    size_t prodCnt, consCnt;
    printf("Number of producers: ");
    scanf("%zd", &prodCnt);
    printf("Number of consumers: ");
    scanf("%zd", &consCnt);

    readyQ = malloc(sizeof(BufUser *) * (prodCnt + consCnt + 1));
    mutexQ = malloc(sizeof(BufUser *) * 2);
    emptyQ = malloc(sizeof(BufUser *) * (prodCnt + consCnt + 1));
    fullQ = malloc(sizeof(BufUser *) * (prodCnt + consCnt + 1));
    rHead = rTail = mHead = mTail = eHead = eTail = fHead = fTail = 0;

    for (int i = 0; i < prodCnt; ++i) {
        BufUser *u = malloc(sizeof(BufUser));
        u->ID = 100 + i;
        for (int j = 0; j < 8; ++j) {
            u->Instr[j] = malloc(sizeof(char) * (strlen(ProdInstr[j]) + 1));
            strcpy(u->Instr[j], ProdInstr[j]);
        }
        u->Cur = 0;
        u->State = Ready;
        u->Product = NULL;
        readyQ[rTail++] = u;
    }
    for (int i = 0; i < consCnt; ++i) {
        BufUser *u = malloc(sizeof(BufUser));
        u->ID = 200 + i;
        for (int j = 0; j < 8; ++j) {
            u->Instr[j] = malloc(sizeof(char) * (strlen(ConsInstr[j]) + 1));
            strcpy(u->Instr[j], ConsInstr[j]);
        }
        u->Cur = 0;
        u->State = Ready;
        u->Product = NULL;
        readyQ[rTail++] = u;
    }

    size_t bufSize;
    printf("Buffer size: ");
    scanf("%zd", &bufSize);
    prodBuf.Stack = malloc(sizeof(Product) * bufSize);
    prodBuf.Top = 0;
    mutex = 1;
    empty = bufSize;
    full = 0;

    char instr[9], attr[9];
    for (int i = 1;getchar()=='\n'; ++i) {
        printf("%d\t", i);

        if (rHead >= prodCnt + consCnt + 1) rHead = 0;
        if (rTail >= prodCnt + consCnt + 1) rTail = 0;
        if (mHead >= 2) mHead = 0;
        if (mTail >= 2) mTail = 0;
        if (eHead >= prodCnt + consCnt + 1) eHead = 0;
        if (eTail >= prodCnt + consCnt + 1) eTail = 0;
        if (fHead >= prodCnt + consCnt + 1) fHead = 0;
        if (fTail >= prodCnt + consCnt + 1) fTail = 0;

        printf("ready: ");
        for(size_t i = rHead; i!=rTail; i = i>=prodCnt + consCnt?0: i+1) {
            printf("%d ", readyQ[i]->ID);
        }
        printf("\n\tmutex waiting: ");
        if(mHead != mTail) {
            printf("%d", mutexQ[mHead]->ID);
        }
        printf("\n\tempty waiting: ");
        for(size_t i = eHead; i!=eTail; i = i>=prodCnt + consCnt?0: i+1) {
            printf("%d ", emptyQ[i]->ID);
        }
        printf("\n\tfull waiting: ");
        for(size_t i = fHead; i!=fTail; i = i>=prodCnt + consCnt?0: i+1) {
            printf("%d ", fullQ[i]->ID);
        }
        putchar('\n');
        printf("\tmutex: %d | empty: %d | full: %d\n\t", mutex, empty, full);

        if(rHead==rTail) {
            perror("Deadlocked.");
        }

        BufUser *u = readyQ[rHead++];
        sscanf(u->Instr[u->Cur], "%s%s", instr, attr);
        if (!strcmp(instr, "produce")) {
            printf("Process %d produced a product.\n", u->ID);
            u->Product = Produce(u->ID);
        } else if (!strcmp(instr, "insert")) {
            printf("Process %d inserted a product into buffer.\n", u->ID);
            InsertProduct(u->Product);
            u->Product = NULL;
        } else if (!strcmp(instr, "p")) {
            if (!strcmp(attr, "mutex")) {
                printf("Process %d p(mutex)", u->ID);
                --mutex;
                if (mutex < 0) {
                    puts(" and waits.");
                    u->State = Waiting;
                    mutexQ[mTail++] = u;
                    continue;
                }
            } else if (!strcmp(attr, "empty")) {
                printf("Process %d p(empty)", u->ID);
                --empty;
                if (empty < 0) {
                    puts(" and waits.");
                    u->State = Waiting;
                    emptyQ[eTail++] = u;
                    continue;
                }
            } else if (!strcmp(attr, "full")) {
                printf("Process %d p(full)", u->ID);
                --full;
                if (full < 0) {
                    puts(" and waits.");
                    u->State = Waiting;
                    fullQ[fTail++] = u;
                    continue;
                }
            }
            puts(".");
        } else if (!strcmp(instr, "v")) {
            if (!strcmp(attr, "mutex")) {
                printf("Process %d v(mutex)", u->ID);
                ++mutex;
                if (mutex <= 0) {
                    printf(" and awakens process %d", mutexQ[mHead]->ID);
                    ++mutexQ[mHead]->Cur;
                    mutexQ[mHead]->State = Ready;
                    readyQ[rTail++] = mutexQ[mHead++];
                }
            } else if (!strcmp(attr, "empty")) {
                printf("Process %d v(empty)", u->ID);
                ++empty;
                if (empty <= 0) {
                    printf(" and awakens process %d", emptyQ[eHead]->ID);
                    ++emptyQ[eHead]->Cur;
                    emptyQ[eHead]->State = Ready;
                    readyQ[rTail++] = emptyQ[eHead++];
                }
            } else if (!strcmp(attr, "full")) {
                printf("Process %d v(full)", u->ID);
                ++full;
                if (full <= 0) {
                    printf(" and awakens process %d", fullQ[fHead]->ID);
                    ++fullQ[fHead]->Cur;
                    fullQ[fHead]->State = Ready;
                    readyQ[rTail++] = fullQ[fHead++];
                }
            }
            if (rTail >= prodCnt + consCnt + 1) rTail = 0;
            puts(".");
        } else if (!strcmp(instr, "fetch")) {
            printf("Process %d fetched a product from buffer.\n", u->ID);
            u->Product = GetProduct();
        } else if (!strcmp(instr, "consume")) {
            printf("Process %d consumes its product.\n", u->ID);
            ConsumeProduct(u->Product);
            u->Product = NULL;
        } else if(!strcmp(instr, "loop")) {
            printf("Process %d loops.\n", u->ID);
            u->Cur = 0;
            readyQ[rTail++] = u;
            continue;
        }
        ++u->Cur;
        readyQ[rTail++] = u;
    }
}
