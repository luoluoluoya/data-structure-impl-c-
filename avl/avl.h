//
// Created by ���� on 2020/5/21.
//

#pragma once

#include "../bst/bst.h"

/**
 * ��BST����AVL��ģ����
 *      AVL
 * @tparam T
 */
template<typename T>
class AVL : public BST<T> {
public:
    //���루��д��
    BinNodePosi(T)insert(const T &e);

    //ɾ������д��
    bool remove(const T &e);

    BinNodePosi(T)&search(const T &e) {

    }
};

#include "avl.cpp"