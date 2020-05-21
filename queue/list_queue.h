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
    void enqueue(T const &e) { this->insertAsLast(e); } //入队：尾部插入
    T dequeue() { return this->remove(this->first()); } //出队：首部删除
    T &front() { return this->first()->data; } //队首
};