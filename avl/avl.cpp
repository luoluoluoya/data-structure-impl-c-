//
// Created by ���� on 2020/5/21.
//

#pragma once
#include "avl_macro.h"

//���루��д��
//��_hot�������ϣ�������������g, һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬�������������½���ԭ��, g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e) {
    BinNodePosi(T) x = BST<T>::search(e); if (x) return x;
    x = new BinNode<T>(e, BST<T>::_hot); BST<T>::_size++;
    BinNodePosi(T) xx = x;
    for (BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent) {
        if ( !Balanced(*g) ) {
            (g == BinTree<T>::_root ? BinTree<T>::_root : ( g->parent->lc == g ? g->lc : g->rc )) = BST<T>::rotateAt(tallerChild( tallerChild(g) ));
            break;
        } else {
            BST<T>::updateHeight(g);
        }
    }
    return xx;
}

//ɾ������д��
//��_hot�������ϣ�������������g, һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������������ԭ����. ��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
//��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T) x = BST<T>::search ( e ); if ( !x ) return false;
    removeAt ( x, BST<T>::_hot ); BST<T>::_size--;
    for ( BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent ) {
        if ( !AvlBalanced ( *g ) )
            (g == BinTree<T>::_root ? BinTree<T>::_root : ( g->parent->lc == g ? g->lc : g->rc )) = BST<T>::rotateAt(tallerChild( tallerChild(g) ));
        BST<T>::updateHeight ( g );     //��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
    }
    return true; //ɾ���ɹ�
}

