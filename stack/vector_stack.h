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
    void push(T const & e) { Vector<T>::insert( Vector<T>::size(), e ); }
    T pop() { return  Vector<T>::remove( Vector<T>::size() - 1 ); }
    T &top() { return (*this)[ Vector<T>::size() - 1 ]; }
};
