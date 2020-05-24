//
// Created by 47302 on 2020/5/24.
//
#pragma once

#include <stdio.h>
#include <string.h>


//构造模式串P的next表
int *buildNext(char *P) {
    size_t m = strlen(P), j = 0;        //“主”串指针
    int *N = new int[m];                //next表
    int t = N[0] = -1;                  //模式串指针
    while (j < m - 1)
        if (0 > t || P[j] == P[t]) {  //匹配
            //当需要将模式串转到 next[j] 时，代表当前模式串的第j向已与文本串对比失败， 所以在构造next表时， 我们应当吸取这个教训； 保证：
            //N(P, j) = { 0 <= t < j | P[0, t) = P[j - t, j) 且 P[t] != P[j] }
            N[j] = (P[++j] != P[++t] ? t : N[t]);
        } else //失配
            t = N[t];
    return N;
}

//KMP算法
int match(char *P, char *T) {
    int *next = buildNext(P); //构造next表
    int n = (int) strlen(T), i = 0; //文本串指针
    int m = (int) strlen(P), j = 0; //模式串指针
    while (j < m && i < n) //自左向右逐个比对字符
        //若匹配，或P已移出最左侧（两个判断的次序不可交换）
        if (0 > j || T[i] == P[j]) {
            i++;j++;
        } else
            j = next[j]; //模式串右移（注意：文本串不用回退）
    delete[] next; //释放next表
    return i -j;
}
