//
// Created by ���� on 2020/5/19.
//

#pragma once
#include "../list/list.h"

/**
 * �����б�ṹʵ�ֵ�ջģ����
 *  ����̬��������һ�˼���
 * @tparam T
 */
template<typename T>
class Stack: public List<T> {
public:
    void push(T const & e) { this->insertAsLast(e); }
    T pop() { return this->remove( this->last() ); }
    T &top() { return this->last()->data; }
};