//
// Created by 张锐 on 2020/5/25.
//

#pragma once

//针对Prim算法的顶点优先级更新器
template <typename Tv, typename Te> struct PrimPU {
    virtual void operator() ( Graph<Tv, Te>* g, int uk, int v ) {
        //对于uk每一尚未被发现的邻接顶点v按Prim策略做松弛,更新优先级（数）,更新父节点
        if ( UNDISCOVERED == g->status ( v ) )  {
            if ( g->priority ( v ) > g->weight ( uk, v ) ) {
                g->priority ( v ) = g->weight ( uk, v );
                g->parent ( v ) = uk;
            }
        }
    }
};
