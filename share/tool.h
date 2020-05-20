//
// Created by 张锐 on 2020/5/18.
//
#pragma once

template<typename T>
void swap(T &s, T &d) {
    T t = s;
    s = d;
    d = t;
}

// 获取较大值， 相等时返回后者
template<typename T>
T max(T f, T s) {
    return f <= s ? s : f;
}