//
// Created by ���� on 2020/5/21.
//

#pragma once

#include "../vector/vector.h"

//B-���ڵ�λ��
#define BTNodePosi(T) BTNode<T>*

/**
 * B-���ڵ�ģ����
 *  ��������ʵ�ֳ����ڵ���Ԫ�غ��ӽڵ�ָ��Ĵ洢
 *      Ԫ�أ�     0  1  2  3  4  5
 *      ָ�룺    0  1  2  3  4  5  6
 *          elemVector(i).lchild = pointerVector[i];
 *          elemVector(i).rchild = pointerVector[i+1];
 * @tparam T
 */
template<typename T>
struct BTNode {
    // ��Ա��Ϊ���������ͳһ���ţ����߿ɸ�����Ҫ��һ����װ��
    BTNodePosi(T)parent;            //���ڵ�
    Vector<T> key;                  //�ؼ�������
    Vector<BTNodePosi(T)> child;    //�����������䳤���ܱ�key��һ��

    // ���캯����ע�⣺BTNodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ�룩
    BTNode() { parent = NULL; child.insert(0, NULL); }

    //��Ϊ���ڵ㣬���ҳ�ʼʱֻ��һ���ؼ��룬�Լ���������
    BTNode(T e, BTNodePosi(T)lc = NULL, BTNodePosi(T)rc = NULL) {
        parent = NULL;
        key.insert(0, e);
        child.insert(0, lc);
        child.insert(1, rc);
        if (lc) lc->parent = this;
        if (rc) rc->parent = this;
    }
};
