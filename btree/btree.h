//
// Created by ���� on 2020/5/21.
//

#pragma once

//����B-���ڵ���
#include "btnode.h"
#include "../share/release.h"
/*

 */


/**
 * B-��ģ����
 * ===============
    n��B��������
        ��֧��: [ ceil(n/2), n ]�� �ڵ���: [ ceil(n/2)-1, n-1 ]
        �ڵ�����ʱ����ڵ�ض�ǡ�ð��� n ���ڵ㣺(�����ڵ㷢������ʱ�����ĸ߶�����1)
            1. ��λ���ڵ����絽��ڵ��Ӧλ��
            2. ���Ҳ��ַ���Ϊ�����ڵ�
        �ڵ�����ʱ����ڵ�ض�ǡ�ð��� ceil(n/2)-2 ���ڵ㣺(�����ڵ㷢������ʱ�����ĸ߶Ƚ���1)
            1. ������Σ������ֵܽڵ�Ԫ���Ƿ���㣨 _order >= ceil(n/2) ��������������ͨ�����ڵ�ת���ֵܽڵ��Ԫ�أ�
            2. ���ֵܽڵ�Ҳ��������ʱ�� _order = ceil(n/2) -1 ��. �Ӹ��ڵ���һ���ڵ���ִ�кϲ� �� 1 + ceil(n/2) -1 + ceil(n/2) -2 = 2*ceil(n/2)-2 ��
 * ===============
 * @tparam T
 */
template<typename T>
class BTree {
protected:
    int _size;          //��ŵĹؼ�������
    int _order;         //B-���Ľ״Σ�����Ϊ3��������ʱָ����һ�㲻���޸�
    BTNodePosi(T)_root; //���ڵ�
    BTNodePosi(T)_hot;  //BTree::search()�����ʵķǿգ��������գ��Ľڵ�λ��
    void solveOverflow(BTNodePosi(T));  //����������֮��ķ��Ѵ���
    void solveUnderflow(BTNodePosi(T)); //��ɾ��������֮��ĺϲ�����
public:
    //���캯����Ĭ��Ϊ��͵�3��
    BTree(int order = 3) : _order(order), _size(0) { _root = new BTNode<T>(); }

    ~BTree() { if (_root) release(_root); }     //�����������ͷ����нڵ�
    int const order() { return _order; }        //�״�
    int const size() { return _size; }          //��ģ
    BTNodePosi(T)&root() { return _root; }      //����
    bool empty() const { return !_root; }       //�п�
    BTNodePosi(T)search(const T &e);            //����
    bool insert(const T &e);                    //����
    bool remove(const T &e);                    //ɾ��
};

#include "btree.cpp"