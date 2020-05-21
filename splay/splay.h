//
// Created by 张锐 on 2020/5/21.
//

#pragma once

#include "../bst/bst.h"

/**
 * 由BST派生的Splay树模板类
 *
 * @tparam T
 */
template<typename T>
class Splay : public BST<T> {
protected:
    //将节点v伸展至根
    BinNodePosi(T)splay(BinNodePosi(T)v);
public:
    //查找（重写）
    BinNodePosi(T)&search(const T &e);
    //插入（重写）
    BinNodePosi(T)insert(const T &e);
    //删除（重写）
    bool remove(const T &e);
};

#include "splay.cpp"