//
// Created by 47302 on 2020/5/23.
//

#pragma once

#include "../list/list.h"

template<typename T>
class PQList: public List<T> {
public:
    //默认构造
    PQList() { }
    //批量构造
    PQList ( T* E, int n ) { while ( 0 < n-- ) this->insertAsFirst ( ( E[n] ) ); }
    void insert ( T e ) { insertAsLast ( e ); }     //直接将新元素插至队列末尾
    T getMax() { return this->selectMax()->data; }        //取出优先级最高的元素
    T delMax() { return this->remove ( this->selectMax() ); }   //删除优先级最高的元素
};