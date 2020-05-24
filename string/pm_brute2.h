//
// Created by 47302 on 2020/5/24.
//

#pragma once
#include <stdio.h>
#include <string.h>

int match(char *P, char *T) {
    // i 指向对齐位置， j 指向当前执行对比的模式串位置
    size_t n = strlen(T), i = 0;    // 文本串
    size_t m = strlen(P), j = 0;    // 模式串

    while ( i < n-m+1 && j < m ) {
        if ( T[i+j] == P[j] )  {
            j++;
        } else {
            i++; j = 0;
        }
    }
    return i;
}
