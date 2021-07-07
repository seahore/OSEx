//
// Created by Administrator on 2021/7/6.
//

#ifndef _DISK_MANAGING_H
#define _DISK_MANAGING_H

#include "defs.h"

extern Byte bitmap[8];

int Allocate();

void Free(int);

#endif //_DISK_MANAGING_H
