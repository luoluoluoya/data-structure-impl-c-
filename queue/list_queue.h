//
// Created by 张锐 on 2020/5/19.
//

#pragma once

#include "../list/list.h"

/**
 * 队列模板类（继承List原有接口）
 *
 * @tparam T
 */
template<typename T>
class Queue : public List<T> {
public:
    void enqueue(T const &e) { List<T>::insertAsLast(e); } //入队：尾部插入
    T dequeue() { return List<T>::remove(List<T>::first()); } //出队：首部删除
    T &front() { return List<T>::first()->data; } //队首
};