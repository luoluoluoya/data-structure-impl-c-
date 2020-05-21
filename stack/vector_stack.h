//
// Created by 张锐 on 2020/5/19.
//

#pragma once
#include "../vector/vector.h"

/**
 * 以向量为基类，派生出栈模板类
 *  将向量的首/末端作为栈底/顶 （向量末端动态操作复杂度为 \Theta(1) ）
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
