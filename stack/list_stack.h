//
// Created by 张锐 on 2020/5/19.
//

#pragma once
#include "../list/list.h"

/**
 * 基于列表结构实现的栈模板类
 *  将动态操作控制一端即可
 * @tparam T
 */
template<typename T>
class Stack: public List<T> {
public:
    void push(T const & e) { List<T>::insertAsLast(e); }
    T pop() { return List<T>::remove( List<T>::last() ); }
    T &top() { return List<T>::last()->data; }
};