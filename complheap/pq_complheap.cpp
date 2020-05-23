//
// Created by 47302 on 2020/5/23.
//

#include "pq_complheap_macro.h"

// 对向量前n个词条中的第i个实施下滤，i < n; 返回下滤抵达的位置（亦i亦j）
template<typename T>
Rank PQComplHeap<T>::percolateDown(Rank n, Rank i) {
    Rank j;
    //只要i非j，则二者换位，并继续考查下降后的i
    while (i != (j = ProperParent(this->_elem, n, i))) {
        T e = this->_elem[i]; this->_elem[i] = this->_elem[j];this->_elem[j] = e;
        i = j;
    }
    return i;
}

template<typename T>
Rank PQComplHeap<T>::percolateUp(Rank i) {
    T e = this->_elem[i]; Rank p = Parent(i);
    //只要i非j，则二者换位，并继续考查下降后的i
    while ( -1 < p && this->_elem[p] > this->_elem[i] ) {
        this->_elem[i] = this->_elem[p];
        i = p;
    }
    this->_elem[i] = e;
    return i;
}

template<typename T>
void PQComplHeap<T>::heapify(Rank n) {
    Rank p = LastInternal(n);
    while (InHeap(n, p))
        percolateDown(n, p--);
}

template<typename T>
void PQComplHeap<T>::insert(T e) {
    Vector<T>::insert(e);
    percolateUp(this->_size-1);
}

template<typename T>
T PQComplHeap<T>::getMax() {
    return this->_elem[0];
}

template<typename T>
T PQComplHeap<T>::delMax() {
    T e = this->_elem[0];
    this->_elem[0] = this->_elem[--this->_size];
    percolateDown(this->_size, 0);
    return e;
}
