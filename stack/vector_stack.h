//
// Created by ���� on 2020/5/19.
//

#pragma once
#include "../vector/vector.h"

/**
 * ������Ϊ���࣬������ջģ����
 *  ����������/ĩ����Ϊջ��/�� ������ĩ�˶�̬�������Ӷ�Ϊ \Theta(1) ��
 *
 * @tparam T
 */
template<typename T>
class Stack: public Vector<T> {
public:
    void push(T const & e) { this->insert( this->size(), e ); }
    T pop() { return  this->remove( this->size() - 1 ); }
    T &top() { return (*this)[ this->size() - 1 ]; }
};
