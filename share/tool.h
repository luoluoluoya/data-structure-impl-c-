//
// Created by ���� on 2020/5/18.
//
#pragma once

template<typename T>
void swap(T &s, T &d) {
    T t = s;
    s = d;
    d = t;
}

// ��ȡ�ϴ�ֵ�� ���ʱ���غ���
template<typename T>
T max(T f, T s) {
    return f <= s ? s : f;
}