//
// Created by 张锐 on 2020/5/19.
//

#include "share/tool.h"

//更新节点x的高度
template<typename T>
int BinTree<T>::updateHeight(BinNodePosi(T)x) {
    return x->height = ( 1 + max(stature(x->lc),  stature(x->rc)) );
}

//更新节点x及其祖先的高度
template<typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T)x) {
    while (x) {
        updateHeight(x); x = x->parent;
    }
}


//插入根节点
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
    return _root = new BinNode<T>(e);
}


//e作为x的左孩子（原无）插入
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T)x, T const &e) {
    return x->insertAsLC(e);
}

//e作为x的右孩子（原无）插入
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T)x, T const &e) {
    return x->insertAsRC(e);
}

//L作为x左子树接入
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T)x, BinTree<T> *&L) {

}

//L作为x右子树接入
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T)x, BinTree<T> *&L) {

}

//删除以位置x处节点为根的子树，返回该子树原先的规模
template<typename T>
int BinTree<T>::remove(BinNodePosi(T)x) {

}

//将子树x从当前树中摘除，并将其转换为一棵独立子树
template<typename T>
BinTree<T> * BinTree<T>::secede(BinNodePosi(T)x) {

}