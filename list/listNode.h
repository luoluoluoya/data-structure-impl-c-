//
// Created by ���� on 2020/5/18.
//

#pragma once

typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* // �б�ڵ�λ��

/**
 * �б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
 *
 * @tparam T
 */
template<typename T>
struct ListNode {
    // ��Ա
    // ��ֵ��ǰ�������
    T data;
    ListNodePosi(T)pred;
    ListNodePosi(T)succ;

    // ���캯��
    ListNode() {} // ���header��trailer�Ĺ���
    ListNode(T e, ListNodePosi(T)p = NULL, ListNodePosi(T)s = NULL) : data(e), pred(p), succ(s) {} // Ĭ�Ϲ�����
    // �����ӿ�
    ListNodePosi(T)insertAsPred(T const &e); //������ǰ�ڵ�֮ǰ�����½ڵ�
    ListNodePosi(T)insertAsSucc(T const &e); //���浱ǰ�ڵ�֮������½ڵ�
};

#include "listNode.cpp"