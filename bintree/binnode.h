//
// Created by ���� on 2020/5/19.
//

#pragma once

//�ڵ�λ��
#define BinNodePosi(T) BinNode<T>*

//�ڵ���ɫ
typedef enum { RB_RED, RB_BLACK } RBColor;

/**
 * �������ڵ�ģ����
 *
 * @tparam T
 */
template<typename T>
struct BinNode {
    T data; //��ֵ

    //���ڵ㼰���Һ���
    BinNodePosi(T)parent;
    BinNodePosi(T)lc;
    BinNodePosi(T)rc;

    int height; //�߶ȣ�ͨ�ã�
    int npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
    RBColor color; //��ɫ���������

    // ���캯��
    BinNode() : parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}

    BinNode(T e, BinNodePosi(T)p = NULL, BinNodePosi(T)lc = NULL, BinNodePosi(T)rc = NULL,
            int h = 0, int l = 1, RBColor c = RB_RED) :
            data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}

    /**�����ӿ�**/
    //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
    int size();

    BinNodePosi(T)insertAsLC(T const &); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
    BinNodePosi(T)insertAsRC(T const &); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�

    //ȡ��ǰ�ڵ��ֱ�Ӻ��
    BinNodePosi(T)succ();

    /**�ڵ�����㷨**/
    template<typename VST>void travLevel(VST &); //������α���
    template<typename VST>void travPre(VST &); //�����������
    template<typename VST>void travIn(VST &); //�����������
    template<typename VST>void travPost(VST &); //�����������

    // �Ƚ������е���
    bool operator<(BinNode const &bn) { return data < bn.data; }    //С��
    bool operator==(BinNode const &bn) { return data == bn.data; }  //����

    /**��ת����**/
    BinNodePosi(T)zig(); //˳ʱ����ת
    BinNodePosi(T)zag(); //��ʱ����ת
};

#include "binnode.cpp"