//
// Created by 47302 on 2020/5/23.
//

#pragma once

#include "../pq/pq.h"
#include "../bintree/bintree.h"

template<typename T>
class PQLeftHeap: public PQ<T>, public BinTree<T> {
public:
    //Ĭ�Ϲ���
    PQLeftHeap() {}
    //�������죺�ɸĽ�ΪFloyd�����㷨
    PQLeftHeap(T *E, int n) { for (int i = 0; i < n; i++) insert(E[i]); }

    void insert(T); //���ձȽ���ȷ�������ȼ��������Ԫ��
    T getMax();     //ȡ�����ȼ���ߵ�Ԫ��
    T delMax();     //ɾ�����ȼ���ߵ�Ԫ��
};

#include "pq_leftheap.cpp"