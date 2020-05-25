//
// Created by 张锐 on 2020/5/25.
//

#pragma once

#include "graph.h"

//针对Dijkstra算法的顶点优先级更新器
//对于uk每一尚未被发现的邻接顶点v，按Dijkstra策略做松弛,更新优先级（数）并同时更新父节点
template<typename Tv, typename Te>
struct DijkstraPU {
    virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
        if (UNDISCOVERED == g->status(v))
            if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {
                g->priority(v) = g->priority(uk) + g->weight(uk, v);
                g->parent(v) = uk;
            }
    }
};