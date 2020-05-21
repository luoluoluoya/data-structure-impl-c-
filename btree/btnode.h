//
// Created by 张锐 on 2020/5/21.
//

#pragma once

#include "../vector/vector.h"

//B-树节点位置
#define BTNodePosi(T) BTNode<T>*

/**
 * B-树节点模板类
 *  基于向量实现超级节点中元素和子节点指针的存储
 *      元素：     0  1  2  3  4  5
 *      指针：    0  1  2  3  4  5  6
 *          elemVector(i).lchild = pointerVector[i];
 *          elemVector(i).rchild = pointerVector[i+1];
 * @tparam T
 */
template<typename T>
struct BTNode {
    // 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
    BTNodePosi(T)parent;            //父节点
    Vector<T> key;                  //关键码向量
    Vector<BTNodePosi(T)> child;    //孩子向量（其长度总比key多一）

    // 构造函数（注意：BTNode只能作为根节点创建，而且初始时有0个关键码和1个空孩子指针）
    BTNode() { parent = NULL; child.insert(0, NULL); }

    //作为根节点，而且初始时只有一个关键码，以及两个孩子
    BTNode(T e, BTNodePosi(T)lc = NULL, BTNodePosi(T)rc = NULL) {
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};
