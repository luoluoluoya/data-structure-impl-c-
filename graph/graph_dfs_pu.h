//
// Created by 张锐 on 2020/5/25.
//

#pragma once

//针对DFS算法的顶点优先级更新器（后被发现者优先）
template <typename Tv, typename Te> struct DfsPU {
    virtual void operator() ( Graph<Tv, Te>* g, int uk, int v ) {
        if ( g->status ( v ) == UNDISCOVERED ) //对于uk每一尚未被发现的邻接顶点v，将其到起点距离的负数作为优先级数，更新优先级（数），更新父节点
            if ( g->priority ( v ) > g->priority ( uk ) - 1 ) {
                g->priority ( v ) = g->priority ( uk ) - 1;
                g->parent ( v ) = uk;
                return; //注意：与BfsPU()不同，这里只要有一个邻接顶点可更新，即可立即返回
            }
    }
};