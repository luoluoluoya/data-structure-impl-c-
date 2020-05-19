//
// Created by 张锐 on 2020/5/19.
//

#pragma once

//节点位置
#define BinNodePosi(T) BinNode<T>*

//节点颜色
typedef enum { RB_RED, RB_BLACK } RBColor;

/**
 * 二叉树节点模板类
 *
 * @tparam T
 */
template<typename T>
struct BinNode {
    T data; //数值

    //父节点及左、右孩子
    BinNodePosi(T)parent;
    BinNodePosi(T)lc;
    BinNodePosi(T)rc;

    int height; //高度（通用）
    int npl; //Null Path Length（左式堆，也可直接用height代替）
    RBColor color; //颜色（红黑树）

    // 构造函数
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, BinNodePosi(T)p = NULL, BinNodePosi(T)lc = NULL, BinNodePosi(T)rc = NULL,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    /**操作接口**/
    //统计当前节点后代总数，亦即以其为根的子树的规模
    int size();

    BinNodePosi(T)insertAsLC(T const &); //作为当前节点的左孩子插入新节点
    BinNodePosi(T)insertAsRC(T const &); //作为当前节点的右孩子插入新节点

    //取当前节点的直接后继
    BinNodePosi(T)succ();

    /**节点遍历算法**/
    template<typename VST>void travLevel(VST &); //子树层次遍历
    template<typename VST>void travPre(VST &); //子树先序遍历
    template<typename VST>void travIn(VST &); //子树中序遍历
    template<typename VST>void travPost(VST &); //子树后序遍历

    // 比较器、判等器
    bool operator<(BinNode const &bn) { return data < bn.data; }    //小于
    bool operator==(BinNode const &bn) { return data == bn.data; }  //等于

    /**旋转操作**/
    BinNodePosi(T)zig(); //顺时针旋转
    BinNodePosi(T)zag(); //逆时针旋转
};

#include "binnode.cpp"