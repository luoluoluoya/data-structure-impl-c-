//
// Created by 47302 on 2020/5/23.
//

#pragma once

#include "../pq/pq.h"
#include "../bintree/bintree.h"

template<typename T>
class PQLeftHeap: public PQ<T>, public BinTree<T> {
public:
    //默认构造
    PQLeftHeap() {}
    //批量构造：可改进为Floyd建堆算法
    PQLeftHeap(T *E, int n) { for (int i = 0; i < n; i++) insert(E[i]); }

    void insert(T); //按照比较器确定的优先级次序插入元素
    T getMax();     //取出优先级最高的元素
    T delMax();     //删除优先级最高的元素
};

#include "pq_leftheap.cpp"