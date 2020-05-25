//
// Created by 张锐 on 2020/5/25.
//

#pragma once

/**
 * 顶点对象
 *
 * @tparam Tv
 */
template<typename Tv>
struct Vertex {
    Tv data;
    int inDegree, outDegree;
    VStatus status;     //数据、出入度数、状态

    int dTime, fTime;   //时间标签

    int parent;
    int priority;       //在遍历树中的父节点、优先级数

    //构造新顶点
    Vertex(Tv const &d = (Tv) 0) :
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};
