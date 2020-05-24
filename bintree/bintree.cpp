//
// Created by 张锐 on 2020/5/19.
//

#include <cmath>
#include "../share/tool.h"

//更新节点x高度
//具体规则，因树而异
template <typename T> int BinTree<T>::updateHeight ( BinNodePosi(T) x ) {
    return x->height = 1 + max ( stature ( x->lc ), stature ( x->rc ) );
}

//更新高度
//从x出发，覆盖历代祖先
template <typename T>
void BinTree<T>::updateHeightAbove ( BinNodePosi(T) x ) {
    while ( x ) { updateHeight ( x ); x = x->parent; }
}

//插入根节点
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
    _size++;
    return _root = new BinNode<T>(e);
}

//e作为x的左孩子（原无）插入
//树中插入位置必定为叶节点处（height=0）, 高度从夫节点开始更新
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T)x, T const &e) {
    _size++;
    BinNodePosi(T) q =  x->insertAsLC(e);
    updateHeightAbove(x);
    return q;
}

//e作为x的右孩子（原无）插入
template<typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T)x, T const &e) {
    _size++;
    BinNodePosi(T) q =  x->insertAsRC(e);
    updateHeightAbove(x);
    return q;
}

//L作为x左子树接入
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T)x, BinTree<T> *&L) {
    // 子树接入
    x->lc = L->_root; if (x->lc) x->lc->parent = x;
    // 更新树高和树大小
    updateHeightAbove(x); _size+=L->_size;
    // 删除原树
    L->_root = NULL; L->_size = 0; delete L;
    return x->lc;
}

//L作为x右子树接入
template<typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T)x, BinTree<T> *&L) {
    // 子树接入
    x->rc = L->_root; if (x->rc) x->rc->parent = x;
    // 更新树高和树大小
    updateHeightAbove(x); _size+=L->_size;
    // 删除原树
    L->_root = NULL; L->_size = 0; delete L;
    return x->rc;
}

//删除以位置x处节点为根的子树，返回该子树原先的规模
template<typename T>
int BinTree<T>::remove(BinNodePosi(T)x) {
    FromParentTo ( *x ) = NULL; //切断来自父节点的指针
    updateHeightAbove ( x->parent ); //更新祖先高度
    int n = removeAt ( x ); _size -= n; return n; //删除子树x，更新规模，返回删除节点总数
}

//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
template <typename T>
static int removeAt ( BinNodePosi(T) x ) {
    //递归基：空树
    if ( !x ) return 0;
    //递归释放左、右子树
    int n = 1 + removeAt ( x->lc ) + removeAt ( x->rc );
    //释放被摘除节点，并返回删除节点总数
    delete x; return n;
}

//二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一棵独立子树返回
template <typename T>
BinTree<T>* BinTree<T>::secede( BinNodePosi(T) x ) { //assert: x为二叉树中的合法位置
    FromParentTo ( *x ) = NULL; //切断来自父节点的指针
    updateHeightAbove ( x->parent ); //更新原树中所有祖先的高度
    BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //新树以x为根
    S->_size = x->size(); _size -= S->_size; return S; //更新规模，返回分离出来的子树
}