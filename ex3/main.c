#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DiskManaging.h"

void PrintBitmap(){
    for(int i=0; i<8; ++i) {
        for(int j=0; j<8; ++j) {
            putchar('0' + ((bitmap[i] >> j) % 2));
        }
        putchar('\n');
    }
    putchar('\n');
}

typedef struct Node {
    int val;
    struct Node *next;
}Node;

Node **proc;

int main() {
    memset(bitmap, 0, 8);

    printf("Number of processes: ");
    size_t numProc;
    scanf("%u", &numProc);
    proc = malloc(numProc * sizeof(void*));
    memset(proc, 0, numProc * sizeof(void*));

    while(1) {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd) {
            case 0: {
                size_t p, cnt;
                scanf("%u%u", &p, &cnt);
                if (p < numProc && cnt >= 1 && !proc[p]) {
                    proc[p] = malloc(sizeof(Node));
                    proc[p]->val = Allocate();
                    Node *iter = proc[p];
                    for (int i = 1; i < cnt; ++i) {
                        iter->next = malloc(sizeof(Node));
                        iter = iter->next;
                        iter->val = Allocate();
                    }
                    iter->next = NULL;
                }
                break;
            }
            case 1: {
                size_t p;
                scanf("%u", &p);
                if (p < numProc) {
                    Node *iter = proc[p];
                    while (iter) {
                        Free(iter->val);
                        Node *t = iter->next;
                        free(iter);
                        iter = t;
                    }
                    proc[p] = NULL;
                }
                break;
            }
            case 2:
                PrintBitmap();
                break;
            case 3:
                return 0;
        }
    }
}
