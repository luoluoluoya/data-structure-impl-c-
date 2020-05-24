//
// Created by 47302 on 2020/5/24.
//

#pragma once
#include <stdio.h>
#include <string.h>

int match(char *P, char *T) {
    // i��j ָ��ǰ�Աȵ��ַ�λ�ã� i-jָ��ǰ����λ��
    size_t n = strlen(T), i = 0;    // �ı���
    size_t m = strlen(P), j = 0;    // ģʽ��

    // ģʽ�����ı�������λִ�жԱ�
    while ( i < n && j < m ) {
        if ( T[i] == P[j] ) {
            i++; j++;
        } else {
            i-=(j-1); j = 0;
        }
    }
    // ���ص�ǰ�Աȳɹ����߽����Աȣ�ʧ�ܣ�ʱ�Ķ���λ�� [0, n-m]
    return i - j;
}
