//
// Created by 张锐 on 2020/5/25.
//

#pragma once

//针对BFS算法的顶点优先级更新器 （先被发现者优先）
//priority(v)
template<typename Tv, typename Te>
struct BfsPU {
    virtual void operator()(Graph <Tv, Te> *g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v,将其到起点的距离作为优先级数,更新优先级（数）和父节点
            if (g->priority(v) > g->priority(uk) + 1) {
                g->priority(v) = g->priority(uk) + 1;
                g->parent(v) = uk;
            }
    }
};