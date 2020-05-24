//
// Created by 47302 on 2020/5/24.
//

#pragma once
#include <stdio.h>
#include <string.h>

int match(char *P, char *T) {
    // i，j 指向当前对比的字符位置； i-j指向当前对齐位置
    size_t n = strlen(T), i = 0;    // 文本串
    size_t m = strlen(P), j = 0;    // 模式串

    // 模式串在文本串上逐位执行对比
    while ( i < n && j < m ) {
        if ( T[i] == P[j] ) {
            i++; j++;
        } else {
            i-=(j-1); j = 0;
        }
    }
    // 返回当前对比成功或者结束对比（失败）时的对齐位置 [0, n-m]
    return i - j;
}
