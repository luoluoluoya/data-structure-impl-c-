//
// Created by ���� on 2020/5/21.
//

#pragma once
#include "avl_macro.h"

//���루��д��
//��_hot�������ϣ�������������g, һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬�������������½���ԭ��, g����󣬾ֲ������߶ȱ�Ȼ��ԭ�������������ˣ��ʵ����漴����
template<typename T>
BinNodePosi(T) AVL<T>::insert(const T &e) {
    BinNodePosi(T) x = this->search(e); if (x) return x;    // todo  searchδ�������ã�
    BinNodePosi(T) xx = x = new BinNode<T>(e, this->_hot); this->_size++;
    for (BinNodePosi(T) g = this->_hot; g; g = g->parent) {
        if ( !Balanced(*g) ) {
            FromParentTo(*g) = this->rotateAt(tallerChild( tallerChild(g) ));
            break;
        } else {
            this->updateHeight(g);
        }
    }
    return xx;
}

//ɾ������д��
//��_hot�������ϣ�������������g, һ������gʧ�⣬�򣨲��á�3 + 4���㷨��ʹ֮���⣬��������������ԭ����. ��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
//��������Omega(logn)�ε������������Ƿ�����������ȫ���߶Ⱦ����ܽ���
template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T) x = this->search ( e ); if ( !x ) return false;
    removeAt ( x, this->_hot ); this->_size--;
    for ( BinNodePosi(T) g = this->_hot; g; g = g->parent ) {
        if ( !AvlBalanced ( *g ) )
            FromParentTo(*g) = this->rotateAt(tallerChild( tallerChild(g) ));
        this->updateHeight ( g );     //��������߶ȣ�ע�⣺����gδʧ�⣬�߶�����ܽ��ͣ�
    }
    return true; //ɾ���ɹ�
}

