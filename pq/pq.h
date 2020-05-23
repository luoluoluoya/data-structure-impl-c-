//
// Created by 47302 on 2020/5/23.
//

#pragma once

/**
 * 优先级队列PQ模板类
 *
 * @tparam T
 */
template<typename T>
class PQ {
public:
    //按照比较器确定的优先级次序插入词条
    virtual void insert(T const e) = 0;

    //取出优先级最高的词条
    virtual T getMax() = 0;

    //删除优先级最高的词条
    virtual T delMax() = 0;
};
