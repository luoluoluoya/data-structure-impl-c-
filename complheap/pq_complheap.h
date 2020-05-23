//
// Created by 47302 on 2020/5/23.
//

#pragma once

#include "../vector/vector.h"
#include "../pq/pq.h"

/*
    对节点的层序遍历进行标号： 0 1 2 3 4 5 ... （对应节点存储在向量结构中的秩）
    内部节点 i 的左右子节点若存在， 分别为： 2i+1， 2(i+1)
    节点p若不为根节点，则其父节点为： floor( (p-1)/2 )
 */

/**
 * 完全二叉堆
 *
 * @tparam T
 */
template <typename T> class PQComplHeap : public PQ<T>, public Vector<T> {
protected:
    Rank percolateDown( Rank n, Rank i );  //下滤
    Rank percolateUp ( Rank i );            //上滤
    void heapify ( Rank n );                //Floyd建堆算法
public:
    PQComplHeap() { } //默认构造
    PQComplHeap ( T* A, Rank n ) { this->copyFrom ( A, 0, n ); heapify ( n ); } //批量构造
    void insert ( T );  //按照比较器确定的优先级次序，插入词条
    T getMax();         //读取优先级最高的词条
    T delMax();         //删除优先级最高的词条
};

#include "pq_complheap.cpp"