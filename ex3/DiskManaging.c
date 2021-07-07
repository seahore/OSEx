//
// Created by Administrator on 2021/7/6.
//

#include "DiskManaging.h"

Byte bitmap[8];

int Allocate() {
    int bytePos = 0, bitPos = 0;
    for (; bytePos < 8 && (0xFF & bitmap[bytePos]) == 0xFF; ++bytePos);
    for (Byte t = bitmap[bytePos]; t % 2; ++bitPos, t >>= 1);
    bitmap[bytePos] += 1 << bitPos;
    return 8 * bytePos + bitPos;
}

void Free(int pos) {
    int bytePos = pos / 8, bitPos = pos % 8;
    bitmap[bytePos] -= 1 << bitPos;
}
