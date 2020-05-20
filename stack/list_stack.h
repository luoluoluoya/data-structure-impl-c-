//
// Created by ���� on 2020/5/19.
//

#pragma once
#include "../list/list.h"

/**
 * �����б��ṹʵ�ֵ�ջģ����
 *  ����̬��������һ�˼���
 * @tparam T
 */
template<typename T>
class Stack: public List<T> {
public:
    void push(T const & e) { List<T>::insertAsLast(e); }
    T pop() { return List<T>::remove( List<T>::last() ); }
    T &top() { return List<T>::last()->data; }
};