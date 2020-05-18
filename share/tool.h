//
// Created by уехЯ on 2020/5/18.
//
#pragma once

template<typename T>
void swap(T &s, T &d) {
    T t = s;
    s = d;
    d = t;
}