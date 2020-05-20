//
// Created by 张锐 on 2020/5/20.
//


/******************************************************************************************
 * "3 + 4"操作主要是为了节点失去平衡的局部的进行恢复平衡， 转化为一颗等价的二叉搜索树
 *      依据二叉搜索树：上下可变， 左右不乱的原则。
 *      失衡在局部主要体现为： zig(g), zag(v)-zig(g), zag(g), zig(v)-zag(g)等四种情况
 * 按照“3 + 4”结构联接3个节点及其四棵子树，返回重组之后的局部子树根节点位置（即b）
 * 子树根节点与上层节点之间的双向联接，均须由上层调用者完成
 * 可用于AVL和RedBlack的局部平衡调整
 ******************************************************************************************/
template<typename T>
BinNodePosi(T) BST<T>::connect34(
        BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
        BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3) {
    a->lc = T0; if (T0) T0->parent = a;
    a->rc = T1; if (T1) T1->parent = a; BinTree<T>::updateHeight(a);

    c->lc = T2; if (T2) T2->parent = c;
    c->rc = T3; if (T3) T3->parent = c; BinTree<T>::updateHeight(c);

    b->lc = a; a->parent = a;
    b->rc = c; c->parent = a; BinTree<T>::updateHeight(b);

    return b;
}

/******************************************************************************************
 * BST节点旋转变换统一算法（3节点 + 4子树），返回调整之后局部子树根节点的位置
 * 注意：尽管子树根会正确指向上层节点（如果存在），但反向的联接须由上层函数完成
 ******************************************************************************************/
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {
    BinNodePosi(T) gg;
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
    if ( IsLChild(*p) ) {       // p 为 g 的左孩子
        if ( IsLChild(*v) ) {   // g 做 zig 操作
            p->parent = g->parent;
            gg = connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {                   // v 做一次 zag 操作， g 再做一次zig操作
            v->parent = g->parent;
            gg = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {       // p 为 g 的右孩子
        if ( IsRChild(*v) ) {   // g 做 zag 操作
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
BinNodePosi(T) &BST<T>::search(const T &e) {
    return searchIn(BinTree<T>::_root, e, NULL);
}

template<typename T>
static BinNodePosi(T) searchIn(BinNodePosi(T) p, const T &e, BinNodePosi(T) &hot = NULL) {
    while ( p && (p->data != e) ) {
        hot = p;
        p = (p->data < e) ? (p->lc) : (p->rc);
    }
    return p;
}