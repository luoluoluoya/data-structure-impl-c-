//
// Created by ���� on 2020/5/19.
//

#include <cmath>
#include "../share/tool.h"

//���½ڵ�x�߶�
//���������������
template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x ) {
    return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) );
}

//���¸߶�
//��x������������������
template <typename T>
void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) {
    while ( x ) { updateHeight ( x ); x = x->parent; }
}

//������ڵ�
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
    _size++;
    return _root = new BinNode<T>(e);
}

//e��Ϊx�����ӣ�ԭ�ޣ�����
//���в���λ�ñض�ΪҶ�ڵ㴦��height=0��, �߶ȴӷ�ڵ㿪ʼ����
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T)x, T const &e) {
    _size++;
    BinNodePosi(T) q =  x->insertAsLC(e);
    updateHeightAbove(x);
    return q;
}

//e��Ϊx���Һ��ӣ�ԭ�ޣ�����
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T)x, T const &e) {
    _size++;
    BinNodePosi(T) q =  x->insertAsRC(e);
    updateHeightAbove(x);
    return q;
}

//L��Ϊx����������
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T)x, BinTree<T> *&L) {
    // ��������
    x->lc = L->_root; if (x->lc) x->lc->parent = x;
    // �������ߺ�����С
    updateHeightAbove(x); _size+=L->_size;
    // ɾ��ԭ��
    L->_root = NULL; L->_size = 0; delete L;
    return x->lc;
}

//L��Ϊx����������
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T)x, BinTree<T> *&L) {
    // ��������
    x->rc = L->_root; if (x->rc) x->rc->parent = x;
    // �������ߺ�����С
    updateHeightAbove(x); _size+=L->_size;
    // ɾ��ԭ��
    L->_root = NULL; L->_size = 0; delete L;
    return x->rc;
}

//ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
template<typename T>
int BinTree<T>::remove(BinNodePosi(T)x) {
    FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
    updateHeightAbove ( x->parent ); //�������ȸ߶�
    int n = removeAt ( x ); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}

//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
template <typename T>
static int removeAt ( BinNodePosi(T) x ) {
    //�ݹ��������
    if ( !x ) return 0;
    //�ݹ��ͷ���������
    int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc );
    //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
    delete x; return n;
}

//���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
template <typename T>
BinTree<T>* BinTree<T>::secede( BinNodePosi(T) x ) { //assert: xΪ�������еĺϷ�λ��
    FromParentTo ( *x ) = NULL; //�ж����Ը��ڵ��ָ��
    updateHeightAbove ( x->parent ); //����ԭ�����������ȵĸ߶�
    BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
    S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}