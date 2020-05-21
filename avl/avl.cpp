//
// Created by 张锐 on 2020/5/21.
//

#pragma once
#include "avl_macro.h"

//插入（重写）
//从_hot出发向上，逐层检查各代祖先g, 一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树重新接入原树, g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
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

//删除（重写）
//从_hot出发向上，逐层检查各代祖先g, 一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至原父亲. 并更新其高度（注意：即便g未失衡，高度亦可能降低）
//可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
template<typename T>
bool AVL<T>::remove(const T &e) {
    BinNodePosi(T) x = BST<T>::search ( e ); if ( !x ) return false;
    removeAt ( x, BST<T>::_hot ); BST<T>::_size--;
    for ( BinNodePosi(T) g = BST<T>::_hot; g; g = g->parent ) {
        if ( !AvlBalanced ( *g ) )
            (g == BinTree<T>::_root ? BinTree<T>::_root : ( g->parent->lc == g ? g->lc : g->rc )) = BST<T>::rotateAt(tallerChild( tallerChild(g) ));
        BST<T>::updateHeight ( g );     //并更新其高度（注意：即便g未失衡，高度亦可能降低）
    }
    return true; //删除成功
}

