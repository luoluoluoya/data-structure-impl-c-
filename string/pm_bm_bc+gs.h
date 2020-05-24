//
// Created by 47302 on 2020/5/24.
//

#pragma once

#include <string.h>
#include <cmath>

/**
    坏字符策略仅利用了此前（最后一次）失败比对所提供的“教训”。而实际上在此之前，还做过一系列成功的比对，而这些“经验”却被忽略了。
    好后缀: 每轮比对中的若干次（连续的）成功匹配，都对应于模式串P的一个后缀，称作“好后缀” （good suffix）。按照以上分析，必须充分利用好好后缀所提供的“经验”。

 */


//构造Bad Charactor Shift表
static int *buildBC(char *P) {
    int *bc = new int[256];
    for (int i = 0; i < 256; bc[i++] = -1);
    for (size_t m = strlen(P), j = 0; j < m; ++j) {
        bc[P[j]] = j;
    }
    return bc;
}


//构造最大匹配后缀长度表：O(m)
static int *buildSS(char *P) {
    int m = strlen(P);
    int *ss = new int[m]; //Suffix Size表
    ss[m - 1] = m; //对最后一个字符而言，与之匹配的最长后缀就是整个P串
    // 以下，从倒数第二个字符起自右向左扫描P，依次计算出ss[]其余各项
    for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--)
        if ((lo < j) && (ss[m - hi + j - 1] <= j - lo)) //情况一
            ss[j] = ss[m - hi + j - 1]; //直接利用此前已计算出的ss[]
        else { //情况二
            hi = j;
            lo = __min(lo, hi);
            while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1])) //二重循环？
                lo--; //逐个对比处于(lo, hi]前端的字符
            ss[j] = hi - lo;
        }
    return ss;
}

//构造好后缀位移量表：O(m)
int *buildGS(char *P) {
    int *ss = buildSS(P); //Suffix Size table
    size_t m = strlen(P);
    int *gs = new int[m]; //Good Suffix shift table
    for (size_t j = 0; j < m; j++) gs[j] = m; //初始化
    for (size_t i = 0, j = m - 1; j < UINT_MAX; j--) //逆向逐一扫描各字符P[j]
        if (j + 1 == ss[j]) //若P[0, j] = P[m - j - 1, m)，则
            while (i < m - j - 1) //对于P[m - j - 1]左侧的每个字符P[i]而言（二重循环？）
                gs[i++] = m - j - 1; //m - j - 1都是gs[i]的一种选择
    for (size_t j = 0; j < m - 1; j++) //画家算法：正向扫描P[]各字符，gs[j]不断递减，直至最小
        gs[m - ss[j] - 1] = m - j - 1; //m - j - 1必是其gs[m - ss[j] - 1]值的一种选择

    delete[] ss;
    return gs;
}


//Boyer-Morre算法（完全版，兼顾Bad Character与Good Suffix）
int match(char *P, char *T) {
    int *bc = buildBC(P);
    int *gs = buildGS(P);   //构造BC表和GS表
    size_t i = 0;           //模式串相对于文本串的起始位置（初始时与文本串左对齐）

    //模式串不断右移（距离可能不止一个字符）
    //从模式串最末尾的字符开始自右向左比对，若极大匹配后缀 == 整个模式串（说明已经完全匹配）返回匹配位置. 否则，适当地移动模式串位移量根据BC表和GS表选择大者
    while (strlen(T) >= i + strlen(P)) {
        int j = strlen(P) - 1;
        while (P[j] == T[i + j] && 0 <= --j);
        if (0 > j)
            break;
        else
            i += max(gs[j], j - bc[T[i + j]]);
    }
    delete[] gs;
    delete[] bc; //销毁GS表和BC表
    return i;
}