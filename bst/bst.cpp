//
// Created by 张锐 on 2020/5/20.
//

#include "../share/release.h"

/******************************************************************************************
 * BST节点删除算法：删除位置x所指的节点（全局静态模板函数，适用于AVL、Splay、RedBlack等各种BST）
 * 目标x在此前经查找定位，并确认非NULL，故必删除成功；与searchIn不同，调用之前不必将hot置空
 * 返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲——二者均有可能是NULL
 ******************************************************************************************/
template <typename T>
static BinNodePosi(T) removeAt ( BinNodePosi(T) & x, BinNodePosi(T) & hot ) {
    BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
    BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
    if ( !HasLChild ( *x ) ) //若*x的左子树为空，则可
        succ = x = x->rc; //直接将*x替换为其右子树
    else if ( !HasRChild ( *x ) ) //若右子树为空，则可
        succ = x = x->lc; //对称地处理——注意：此时succ != NULL
    else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
        w = w->succ(); //（在右子树中）找到*x的直接后继*w
        swap ( x->data, w->data ); //交换*x和*w的数据元素
        BinNodePosi(T) u = w->parent;
        ( ( u == x ) ? u->rc : u->lc ) = succ = w->rc; //隔离节点*w
    }
    hot = w->parent; //记录实际被删除节点的父亲
    if ( succ ) succ->parent = hot; //并将被删除节点的接替者与hot相联
    release(w->data); release (w); return succ; //释放被摘除节点，返回接替者
}

/******************************************************************************************
 * 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
 * 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
 * 可用于AVL和RedBlack的局部平衡调整
 ******************************************************************************************/
template <typename T> BinNodePosi(T) BST<T>::connect34 (
        BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) {
    a->lc = T0; if ( T0 ) T0->parent = a;
    a->rc = T1; if ( T1 ) T1->parent = a; this->updateHeight ( a );
    c->lc = T2; if ( T2 ) T2->parent = c;
    c->rc = T3; if ( T3 ) T3->parent = c; this->updateHeight ( c );
    b->lc = a; a->parent = b;
    b->rc = c; c->parent = b; this->updateHeight ( b );
    return b; //该子树新的根节点
}

/******************************************************************************************
 * BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
 * 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
 ******************************************************************************************/
template <typename T> BinNodePosi(T) BST<T>::rotateAt ( BinNodePosi(T) v ) { //v为非空孙辈节点
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
    if ( IsLChild ( *p ) ) /* zig */
        if ( IsLChild ( *v ) ) { /* zig-zig */
            p->parent = g->parent; //向上联接
            return connect34 ( v, p, g, v->lc, v->rc, p->rc, g->rc );
        } else { /* zig-zag */
            v->parent = g->parent; //向上联接
            return connect34 ( p, v, g, p->lc, v->lc, v->rc, g->rc );
        }
    else  /* zag */
    if ( IsRChild ( *v ) ) { /* zag-zag */
        p->parent = g->parent; //向上联接
        return connect34 ( g, p, v, g->lc, p->lc, v->lc, v->rc );
    } else { /* zag-zig */
        v->parent = g->parent; //向上联接
        return connect34 ( g, v, p, g->lc, v->lc, v->rc, p->rc );
    }
}

// 平衡二叉搜树的查找
template<typename T>
BinNodePosi(T)&BST<T>::search(const T &e) {
    return searchIn(this->_root, e, _hot = NULL);
}

//节点v（或假想的通配哨兵）的关键码等于e
#define EQUAL(e, v)  (!(v) || (e) == (v)->data)

//在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
//返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）
template <typename T>
BinNodePosi(T) & BST<T>::searchIn ( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot ) {
    if ( EQUAL ( e, v ) ) return v; hot = v; //退化情况：在子树根节点v处命中
    while ( 1 ) {
        BinNodePosi(T) & c = ( e < hot->data ) ? hot->lc : hot->rc;
        if ( EQUAL ( e, c ) ) return c; hot = c;
    }
}

//将关键码e插入BST树中
//无论e是否存在于原树中，返回时总有x->data == e
template <typename T> BinNodePosi(T) BST<T>::insert ( const T& e ) {
    BinNodePosi(T) & x = search ( e ); if ( x ) return x; //确认目标不存在（留意对_hot的设置）
    x = new BinNode<T> ( e, _hot ); //创建新节点x：以e为关键码，以_hot为父
    this->_size++; //更新全树规模
    this->updateHeightAbove ( x ); //更新x及其历代祖先的高度
    return x; //新插入的节点，必为叶子
}

//从BST树中删除关键码e
template <typename T>
bool BST<T>::remove ( const T& e ) { //从BST树中删除关键码e
    BinNodePosi(T) & x = search ( e ); if ( !x ) return false; //确认目标存在（留意_hot的设置）
    removeAt ( x, _hot ); this->_size--; //实施删除
    this->updateHeightAbove ( _hot ); //更新_hot及其历代祖先的高度
    return true;
} //删除成功与否，由返回值指示
