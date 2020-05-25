//
// Created by 张锐 on 2020/5/25.
//

#pragma once

#define EdgePosi(Te) Edge<Te>*

/**
 * 边对象
 *
 * @tparam Te
 */
template<typename Te>
struct Edge {
    Te data;
    int weight;
    EType type;     //数据、权重、类型

    //构造
    Edge(Te const &d, int w) : data(d), weight(w), type(UNDETERMINED) {}
};
