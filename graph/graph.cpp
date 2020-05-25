//
// Created by 张锐 on 2020/5/25.
//

#pragma once

#include "../queue/queue.h"

/******************************** 广度优先搜索BFS算法 ********************************/
//assert: 0 <= s < n
template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs ( int s ) {
    reset(); int clock = 0; int v = s; //初始化
    do
        if ( UNDISCOVERED == status ( v ) ) //逐一检查所有顶点, 一旦遇到尚未发现的顶点即从该顶点出发启动一次BFS, 按序号检查，故不漏不重
            BFS ( v, clock );
    while ( s != ( v = ( ++v % n ) ) );
}

//广度优先搜索BFS算法（单个连通域）
template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS ( int v, int& clock ) {
    Queue<int> Q; //引入辅助队列
    status ( v ) = DISCOVERED; Q.enqueue ( v ); //初始化起点
    while ( !Q.empty() ) { //在Q变空之前，不断取出队首顶点v，枚举v的所有邻居u若u尚未被发现，则发现该顶点并引入树边拓展支撑树；若u已被发现，或者甚至已访问完毕，则将(v, u)归类于跨边
        int v = Q.dequeue(); dTime ( v ) = ++clock; //
        for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) )
            if ( UNDISCOVERED == status ( u ) ) {
                status ( u ) = DISCOVERED; Q.enqueue ( u );
                type ( v, u ) = TREE; parent ( u ) = v;
            } else {
                type ( v, u ) = CROSS;
            }
        status ( v ) = VISITED; //至此，当前顶点访问完毕
    }
}


/******************************** 深度优先搜索DFS算法 ********************************/
//assert: 0 <= s < n
//逐一检查所有顶点，一旦遇到尚未发现的顶点。即从该顶点出发启动一次DFS，按序号检查，故不漏不重
template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs ( int s ) {
    reset(); int clock = 0; int v = s; //初始化
    do
        if ( UNDISCOVERED == status ( v ) )
            DFS ( v, clock );
    while ( s != ( v = ( ++v % n ) ) );
}

//深度优先搜索DFS算法（单个连通域）
//发现当前顶点v，枚举v的所有邻居u并视其状态分别处理
//  1. u尚未发现，意味着支撑树可在此拓展。
//  2. u已被发现但尚未访问完毕，应属被后代指向的祖先
//  3. u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边. ( 访问时的时间区间是否存在包含关系： 存在=》前向边， 不存在 =》 跨边 )
template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS ( int v, int& clock ) {
    dTime ( v ) = ++clock; status ( v ) = DISCOVERED;
    for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) )
        switch ( status ( u ) ) {
            case UNDISCOVERED:
                type ( v, u ) = TREE; parent ( u ) = v; DFS ( u, clock ); break;
            case DISCOVERED:
                type ( v, u ) = BACKWARD; break;
            default:
                type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS; break;
        }
    status ( v ) = VISITED; fTime ( v ) = ++clock; //至此，当前顶点v方告访问完毕
}


/******************************** 优先级搜索 ********************************/
//assert: 0 <= s < n
template <typename Tv, typename Te> template <typename PU>
void Graph<Tv, Te>::pfs ( int s, PU prioUpdater ) {
    reset(); int v = s; //初始化
    do
        if ( UNDISCOVERED == status ( v ) ) //逐一检查所有顶点，一旦遇到尚未发现的顶点，即从该顶点出发启动一次PFS，按序号检查，故不漏不重
            PFS ( v, prioUpdater );
    while ( s != ( v = ( ++v % n ) ) );
}

//优先级搜索（单个连通域）
template <typename Tv, typename Te> template <typename PU>  //顶点类型、边类型、优先级更新器（通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能）
void Graph<Tv, Te>::PFS ( int s, PU prioUpdater ) {
    priority ( s ) = 0; status ( s ) = VISITED; parent ( s ) = -1;      //初始化，起点s加至PFS树中
    while ( 1 ) { //将下一顶点和边加至PFS树中
        for ( int w = firstNbr ( s ); -1 < w; w = nextNbr ( s, w ) )    //枚举s的所有邻居w， 更新顶点w的优先级及其父顶点。
            prioUpdater ( this, s, w );

        for ( int shortest = INT_MAX, w = 0; w < n; w++ )               //从尚未加入遍历树的顶点中选出下一个优先级最高的顶点
            if ( UNDISCOVERED == status ( w ) )
                if ( shortest > priority ( w ) ) { shortest = priority ( w ); s = w; }

        if ( VISITED == status ( s ) ) break;                           //直至所有顶点均已加入

        status ( s ) = VISITED; type ( parent ( s ), s ) = TREE;        //将s及与其父的联边加入遍历树
    }
}


/******************************** 最短路径Dijkstra算法：适用于一般的有向图 ********************************/
//assert: 0 <= s < n
//对于无向连通图，假设每一条边表示为方向互逆、权重相等的一对边
template <typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra ( int s ) {
    reset(); priority ( s ) = 0;
    for ( int i = 0; i < n; i++ ) { //共需引入n个顶点和n-1条边
        status ( s ) = VISITED; if ( -1 != parent ( s ) ) type ( parent ( s ), s ) = TREE; //引入当前的s

        for ( int j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) )//枚举s的所有邻居j,对邻接顶点j做松弛 (更新节点j到源点的最短路径信息作为权重)
            if ( ( status ( j ) == UNDISCOVERED ) && ( priority ( j ) > priority ( s ) + weight ( s, j ) ) ) {
                priority ( j ) = priority ( s ) + weight ( s, j ); parent ( j ) = s;
            }

        for ( int shortest = INT_MAX, j = 0; j < n; j++ )           //选出下一最近顶点
            if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) )
            { shortest = priority ( j ); s = j; }
    }
}



/******************************** 最小生成树-Prim算法 ********************************/
//assert: 0 <= s < n
//此算法可以称为“加点法”，每次迭代选择代价最小的边对应的点，加入到最小生成树中。算法从某一个顶点s开始，逐渐长大覆盖整个连通网的所有顶点。
template <typename Tv, typename Te>
void Graph<Tv, Te>::prim ( int s ) {
    reset(); priority ( s ) = 0;
    for ( int i = 0; i < n; i++ ) { //共需引入n个顶点和n-1条边

        status ( s ) = VISITED; if ( -1 != parent ( s ) ) type ( parent ( s ), s ) = TREE; //引入当前的s

        //枚举s的所有邻居j，对邻接顶点j做松弛
        for ( int j = firstNbr ( s ); -1 < j; j = nextNbr ( s, j ) ) {
            if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) {
                priority(j) = weight(s, j); parent(j) = s; //与 Dijkstra 算法唯一的不同之处(Dijkstra的权重为到源点的最短距离， 而Prim算法的权重为到当前生成子树任意节点的最短距离)
            }
        }

        //选出下一极短跨边
        for ( int shortest = INT_MAX, j = 0; j < n; j++ ) {
            if ( ( status ( j ) == UNDISCOVERED ) && ( shortest > priority ( j ) ) ){
                shortest = priority ( j ); s = j;
            }
        }
    }
}


/******************************** 基于DFS的拓扑排序算法 ********************************/
//assert: 0 <= s < n
template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort ( int s ) {
    reset(); int clock = 0; int v = s;
    Stack<Tv>* S = new Stack<Tv>; //用栈记录排序顶点
    do {
        if ( UNDISCOVERED == status ( v ) )
            if ( !TSort ( v, clock, S ) ) { //clock并非必需
                while ( !S->empty() ) //任一连通域（亦即整图）非DAG
                    S->pop(); break; //则不必继续计算，故直接返回
            }
    } while ( s != ( v = ( ++v % n ) ) );
    return S; //若输入为DAG，则S内各顶点自顶向底排序；否则（不存在拓扑排序），S空
}

//基于DFS的拓扑排序算法（单趟）
template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort ( int v, int& clock, Stack<Tv>* S ) {
    dTime ( v ) = ++clock; status ( v ) = DISCOVERED; //发现顶点v
    for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
        switch ( status ( u ) ) { //并视u的状态分别处理
            case UNDISCOVERED:
                parent ( u ) = v; type ( v, u ) = TREE;
                if ( !TSort ( u, clock, S ) ) //从顶点u处出发深入搜索
                    return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
                break;
            case DISCOVERED:
                type ( v, u ) = BACKWARD; //一旦发现后向边（非DAG），则
                return false; //不必深入，故返回并报告
            default: //VISITED (digraphs only)
                type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
                break;
        }
    status ( v ) = VISITED; S->push ( vertex ( v ) ); //顶点被标记为VISITED时，随即入栈
    return true; //v及其后代可以拓扑排序
}


/******************************** 基于DFS的BCC分解算法 ********************************/
template <typename Tv, typename Te> void Graph<Tv, Te>::bcc ( int s ) {
    reset(); int clock = 0; int v = s; Stack<int> S; //栈S用以记录已访问的顶点
    do
        if ( UNDISCOVERED == status ( v ) ) { //一旦发现未发现的顶点（新连通分量）
            BCC ( v, clock, S ); //即从该顶点出发启动一次BCC
            S.pop(); //遍历返回后，弹出栈中最后一个顶点——当前连通域的起点
        }
    while ( s != ( v = ( ++v % n ) ) );
}
#define hca(x) (fTime(x)) //利用此处闲置的fTime[]充当hca[]
template <typename Tv, typename Te> //顶点类型、边类型
void Graph<Tv, Te>::BCC ( int v, int& clock, Stack<int>& S ) { //assert: 0 <= v < n
    hca ( v ) = dTime ( v ) = ++clock; status ( v ) = DISCOVERED; S.push ( v ); //v被发现并入栈
    for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
        switch ( status ( u ) ) { //并视u的状态分别处理
            case UNDISCOVERED:
                parent ( u ) = v; type ( v, u ) = TREE; BCC ( u, clock, S ); //从顶点u处深入
                if ( hca ( u ) < dTime ( v ) ) //遍历返回后，若发现u（通过后向边）可指向v的真祖先
                    hca ( v ) = min ( hca ( v ), hca ( u ) ); //则v亦必如此
                else { //否则，以v为关节点（u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部）
                    while ( v != S.pop() ); //依次弹出当前BCC中的节点，亦可根据实际需求转存至其它结构
                    S.push ( v ); //最后一个顶点（关节点）重新入栈——分摊不足一次
                }
                break;
            case DISCOVERED:
                type ( v, u ) = BACKWARD; //标记(v, u)，并按照“越小越高”的准则
                if ( u != parent ( v ) ) hca ( v ) = min ( hca ( v ), dTime ( u ) ); //更新hca[v]
                break;
            default: //VISITED (digraphs only)
                type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS;
                break;
        }
    status ( v ) = VISITED; //对v的访问结束
}
