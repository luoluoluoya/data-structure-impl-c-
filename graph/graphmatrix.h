//
// Created by 张锐 on 2020/5/25.
//

#pragma once

#include "../vector/vector.h"   //引入向量
#include "../graph/graph.h"     //引入图ADT
#include "vertex.h"
#include "edge.h"

/**
 * 基于向量，以邻接矩阵形式实现的图
 *
 * @tparam Tv
 * @tparam Te
 */
template<typename Tv, typename Te>
class GraphMatrix : public Graph<Tv, Te> {
private:
    Vector<Vertex<Tv> > V;          //顶点集（向量）
    Vector<Vector<Edge<Te> *> > E;  //边集（邻接矩阵）
public:
    GraphMatrix() { this->n = this->e = 0; }    //构造
    ~GraphMatrix() {                //析构
        for (int j = 0; j < this->n; j++) //所有动态创建的
            for (int k = 0; k < this->n; k++) //边记录
                delete E[j][k]; //逐条清除
    }

    /**顶点的基本操作**/
    //查询第i个顶点（0 <= i < n）
    virtual Tv &vertex(int i) { return V[i].data; }         //数据
    virtual int inDegree(int i) { return V[i].inDegree; }   //入度
    virtual int outDegree(int i) { return V[i].outDegree; } //出度
    virtual int firstNbr(int i) { return nextNbr(i, this->n); }   //首个邻接顶点
    virtual int nextNbr(int i, int j) {                     //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
        while ((-1 < j) && (!exists(i, --j)));
        return j;
    } //逆向线性试探
    virtual VStatus &status(int i) { return V[i].status; }  //状态
    virtual int &dTime(int i) { return V[i].dTime; }        //时间标签dTime
    virtual int &fTime(int i) { return V[i].fTime; }        //时间标签fTime
    virtual int &parent(int i) { return V[i].parent; }      //在遍历树中的父亲
    virtual int &priority(int i) { return V[i].priority; }  //在遍历树中的优先级数

    // 顶点的动态操作
    virtual int insert(Tv const &vertex);                   //插入顶点，返回编号
    virtual Tv remove(int i);                               //删除第i个顶点及其关联边（0 <= i < n）

    // 边的确认操作; 边(i, j)是否存在
    virtual bool exists(int i, int j) { return (0 <= i) && (i < this->n) && (0 <= j) && (j < this->n) && E[i][j] != NULL; }

    /**边的基本操作**/
    //查询顶点i与j之间的联边（0 <= i, j < n且exists(i, j)）
    virtual EType &type(int i, int j) { return E[i][j]->type; }     //边(i, j)的类型
    virtual Te &edge(int i, int j) { return E[i][j]->data; }        //边(i, j)的数据
    virtual int &weight(int i, int j) { return E[i][j]->weight; }   //边(i, j)的权重
    // 边的动态操作
    virtual void insert(Te const &edge, int w, int i, int j);       //插入权重为w的边e = (i, j)
    virtual Te remove(int i, int j);                                //删除顶点i和j之间的联边（exists(i, j)）
};

#include "graphmatrix.cpp"
