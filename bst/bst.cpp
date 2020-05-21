//
// Created by 张锐 on 2020/5/20.
//

/******************************************************************************************
 * BST节点删除算法：删除位置x所指的节点（全局静态模板函数，适用于AVL、Splay、RedBlack等各种BST）
 * 目标x在此前经查找定位，并确认非NULL，故必删除成功；与searchIn不同，调用之前不必将hot置空
 * 返回值指向实际被删除节点的接替者，hot指向实际被删除节点的父亲——二者均有可能是NULL
 ******************************************************************************************/
//若*x的左子树为空，则可直接将*x替换为其右子树; 若右子树为空，则可对称地处理——注意：此时succ != NULL; 若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要（在右子树中）找到*x的直接后继*w, 交换*x和*w的数据元素
template<typename T>
static BinNodePosi(T)removeAt(BinNodePosi(T)&x, BinNodePosi(T)&hot) {
    BinNodePosi(T)w = x;               //实际被摘除的节点，初值同x
    BinNodePosi(T)succ = NULL;         //实际被删除节点的接替者
    if (!HasLChild (*x))
        succ = x = x->rc;
    else if (!HasRChild (*x))
        succ = x = x->lc;
    else {
        w = w->succ();
        swap(x->data, w->data);
        BinNodePosi(T)u = w->parent;
        ((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
    }
    hot = w->parent; //记录实际被删除节点的父亲
    if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
    delete w;
    return succ; //释放被摘除节点，返回接替者
}

/******************************************************************************************
 * "3 + 4"操作主要是为了节点失去平衡的局部的进行恢复平衡， 转化为一颗等价的二叉搜索树
 *      依据二叉搜索树：上下可变， 左右不乱的原则。
 *      失衡在局部主要体现为： zig(g), zag(v)-zig(g), zag(g), zig(v)-zag(g)等四种情况
 * 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
 * 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
 * 可用于AVL和RedBlack的局部平衡调整
 ******************************************************************************************/
template<typename T>
BinNodePosi(T)BST<T>::connect34(
        BinNodePosi(T)a, BinNodePosi(T)b, BinNodePosi(T)c,
        BinNodePosi(T)T0, BinNodePosi(T)T1, BinNodePosi(T)T2, BinNodePosi(T)T3) {
    a->lc = T0;
    if (T0) T0->parent = a;
    a->rc = T1;
    if (T1) T1->parent = a;
    BinTree<T>::updateHeight(a);

    c->lc = T2;
    if (T2) T2->parent = c;
    c->rc = T3;
    if (T3) T3->parent = c;
    BinTree<T>::updateHeight(c);

    b->lc = a;
    a->parent = a;
    b->rc = c;
    c->parent = a;
    BinTree<T>::updateHeight(b);

    return b;
}

/******************************************************************************************
 * BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
 * 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
 ******************************************************************************************/
template<typename T>
BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T)v) {
    BinNodePosi(T)gg;
    BinNodePosi(T)p = v->parent;
    BinNodePosi(T)g = p->parent;
    if (IsLChild(*p)) {       // p 为 g 的左孩子
        if (IsLChild(*v)) {   // g 做 zig 操作
            p->parent = g->parent;
            gg = connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {                   // v 做一次 zag 操作， g 再做一次zig操作
            v->parent = g->parent;
            gg = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {       // p 为 g 的右孩子
        if (IsRChild(*v)) {   // g 做 zag 操作
            p->parent = g->parent;
            gg = connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {                    // v 做一次 zig 操作， g 再做一次zag操作
            v->parent = g->parent;
            gg = connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
    return gg;
}

// 平衡二叉搜树的查找
template<typename T>
BinNodePosi(T)&BST<T>::search(const T &e) {
    return searchIn(BinTree<T>::_root, e, _hot = NULL);
}

//节点v（或假想的通配哨兵）的关键码等于e
#define EQUAL(e, v)  (!(v) || (e) == (v)->data)

//在以v为根的（AVL、SPLAY、rbTree等）BST子树中查找关键码e
//返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）
template <typename T>
static BinNodePosi(T) & searchIn ( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot ) {
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
    BinTree<T>::_size++; //更新全树规模
    BinTree<T>::updateHeightAbove ( x ); //更新x及其历代祖先的高度
    return x; //新插入的节点，必为叶子
}

//从BST树中删除关键码e
template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi(T)&x = search(e);
    if (!x) return false;  //确认目标存在（留意_hot的设置）
    removeAt(x);
    BinTree<T>::_size--;  //实施删除
    BinTree<T>::updateHeightAbove(_hot);                 //更新_hot及其历代祖先的高度
    return true;
}
