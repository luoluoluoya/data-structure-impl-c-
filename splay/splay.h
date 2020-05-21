//
// Created by ���� on 2020/5/21.
//

#pragma once

#include "../bst/bst.h"

/**
 * ��BST������Splay��ģ����
 *
 * @tparam T
 */
template<typename T>
class Splay : public BST<T> {
protected:
    //���ڵ�v��չ����
    BinNodePosi(T)splay(BinNodePosi(T)v);
public:
    //���ң���д��
    BinNodePosi(T)&search(const T &e);
    //���루��д��
    BinNodePosi(T)insert(const T &e);
    //ɾ������д��
    bool remove(const T &e);
};

#include "splay.cpp"