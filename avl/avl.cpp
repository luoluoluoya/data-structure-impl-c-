//
// Created by 张锐 on 2020/5/21.
//

#pragma once
#include "avl_macro.h"

//插入（重写）
//从_hot出发向上，逐层检查各代祖先g, 一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树重新接入原树, g复衡后，局部子树高度必然复原；其祖先亦必如此，故调整随即结束
//无论e是否存在于原树中，总有AVL::insert(e)->data == e
template <typename T>
BinNodePosi(T) AVL<T>::insert ( const T& e ) {
    BinNodePosi(T) & x = this->search ( e ); if ( x ) return x;
    BinNodePosi(T) xx = x = new BinNode<T> ( e, this->_hot ); this->_size++;
    for ( BinNodePosi(T) g = this->_hot; g; g = g->parent ) {
        if ( !AvlBalanced ( *g ) ) {
            BinNodePosi(T) &pp = FromParentTo ( *g );
            pp = this->rotateAt ( tallerChild ( tallerChild ( g ) ) );
            break;
        } else
            this->updateHeight ( g );
    }
    return xx;
}

//删除（重写）
//从_hot出发向上，逐层检查各代祖先g, 一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至原父亲. 并更新其高度（注意：即便g未失衡，高度亦可能降低）
//可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
template <typename T> bool AVL<T>::remove ( const T& e ) { //从AVL树中删除关键码e
    BinNodePosi(T) & x = this->search ( e ); if ( !x ) return false; //确认目标存在（留意_hot的设置）
    removeAt ( x, this->_hot ); this->_size--; //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
    for ( BinNodePosi(T) g = this->_hot; g; g = g->parent ) { //从_hot出发向上，逐层检查各代祖先g
        //一旦发现g失衡，则（采用“3 + 4”算法）使之复衡，并将该子树联至
        if ( !AvlBalanced ( *g ) ) {
            BinNodePosi(T) &pp = FromParentTo ( *g );
            g = pp = this->rotateAt ( tallerChild ( tallerChild ( g ) ) ); //原父亲
        }

        this->updateHeight ( g ); //并更新其高度（注意：即便g未失衡，高度亦可能降低）
    } //可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
    return true; //删除成功
} //若目标节点存在且被删除，返回true；否则返回false
