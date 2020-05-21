//
// Created by 张锐 on 2020/5/21.
//

#pragma once

#include "../bst/bst.h"

/**
 * 由BST派生AVL树模板类
 *      AVL
 * @tparam T
 */
template<typename T>
class AVL : public BST<T> {
public:
    //插入（重写）
    BinNodePosi(T)insert(const T &e);

    //删除（重写）
    bool remove(const T &e);

    BinNodePosi(T)&search(const T &e) {

    }
};

#include "avl.cpp"