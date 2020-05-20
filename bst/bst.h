//
// Created by ���� on 2020/5/20.
//

#pragma once

#include "../bintree/bintree.h"

//��BinTree����BSTģ����
template<typename T>
class BST : public BinTree<T> {

protected:
    //�����С��ڵ�ĸ���
    BinNodePosi(T)_hot;

    //���ա�3 + 4���ṹ������3���ڵ㼰�Ŀ�����
    BinNodePosi(T) connect34(
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));

    //��x���丸�ס��游��ͳһ��ת����
    BinNodePosi(T)rotateAt(BinNodePosi(T)x);

public:
    //�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
    virtual BinNodePosi(T)&search(const T &e);  //����
    virtual BinNodePosi(T)insert(const T &e);   //����
    virtual bool remove(const T &e);            //ɾ��
};

#include "bst.cpp"