//
// Created by ���� on 2020/5/19.
//

#include "share/tool.h"

//���½ڵ�x�ĸ߶�
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T)x) {
    return x->height = ( 1 + max(stature(x->lc),  stature(x->rc)) );
}

//���½ڵ�x�������ȵĸ߶�
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T)x) {
    while (x) {
        updateHeight(x); x = x->parent;
    }
}


//������ڵ�
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
    return _root = new BinNode<T>(e);
}


//e��Ϊx�����ӣ�ԭ�ޣ�����
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T)x, T const &e) {
    return x->insertAsLC(e);
}

//e��Ϊx���Һ��ӣ�ԭ�ޣ�����
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T)x, T const &e) {
    return x->insertAsRC(e);
}

//L��Ϊx����������
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T)x, BinTree<T> *&L) {

}

//L��Ϊx����������
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T)x, BinTree<T> *&L) {

}

//ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
template<typename T>
int BinTree<T>::remove(BinNodePosi(T)x) {

}

//������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
template<typename T>
BinTree<T> * BinTree<T>::secede(BinNodePosi(T)x) {

}