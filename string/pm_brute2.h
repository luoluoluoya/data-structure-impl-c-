//
// Created by 47302 on 2020/5/24.
//

#pragma once
#include <stdio.h>
#include <string.h>

int match(char *P, char *T) {
    // i ָ�����λ�ã� j ָ��ǰִ�жԱȵ�ģʽ��λ��
    size_t n = strlen(T), i = 0;    // �ı���
    size_t m = strlen(P), j = 0;    // ģʽ��

    while ( i < n-m+1 && j < m ) {
        if ( T[i+j] == P[j] )  {
            j++;
        } else {
            i++; j = 0;
        }
    }
    return i;
}
