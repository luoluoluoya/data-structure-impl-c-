//
// Created by 47302 on 2020/5/24.
//
#pragma once

#include <stdio.h>
#include <string.h>


//����ģʽ��P��next��
int *buildNext(char *P) {
    size_t m = strlen(P), j = 0;        //��������ָ��
    int *N = new int[m];                //next��
    int t = N[0] = -1;                  //ģʽ��ָ��
    while (j < m - 1)
        if (0 > t || P[j] == P[t]) {  //ƥ��
            //����Ҫ��ģʽ��ת�� next[j] ʱ������ǰģʽ���ĵ�j�������ı����Ա�ʧ�ܣ� �����ڹ���next��ʱ�� ����Ӧ����ȡ�����ѵ�� ��֤��
            //N(P, j) = { 0 <= t < j | P[0, t) = P[j - t, j) �� P[t] != P[j] }
            N[j] = (P[++j] != P[++t] ? t : N[t]);
        } else //ʧ��
            t = N[t];
    return N;
}

//KMP�㷨
int match(char *P, char *T) {
    int *next = buildNext(P); //����next��
    int n = (int) strlen(T), i = 0; //�ı���ָ��
    int m = (int) strlen(P), j = 0; //ģʽ��ָ��
    while (j < m && i < n) //������������ȶ��ַ�
        //��ƥ�䣬��P���Ƴ�����ࣨ�����жϵĴ��򲻿ɽ�����
        if (0 > j || T[i] == P[j]) {
            i++;j++;
        } else
            j = next[j]; //ģʽ�����ƣ�ע�⣺�ı������û��ˣ�
    delete[] next; //�ͷ�next��
    return i -j;
}
