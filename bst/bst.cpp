//
// Created by ���� on 2020/5/20.
//


/******************************************************************************************
 * "3 + 4"������Ҫ��Ϊ�˽ڵ�ʧȥƽ��ľֲ��Ľ��лָ�ƽ�⣬ ת��Ϊһ�ŵȼ۵Ķ���������
 *      ���ݶ��������������¿ɱ䣬 ���Ҳ��ҵ�ԭ��
 *      ʧ���ھֲ���Ҫ����Ϊ�� zig(g), zag(v)-zig(g), zag(g), zig(v)-zag(g)���������
 * ���ա�3 + 4���ṹ����3���ڵ㼰���Ŀ���������������֮��ľֲ��������ڵ�λ�ã���b��
 * �������ڵ����ϲ�ڵ�֮���˫�����ӣ��������ϲ���������
 * ������AVL��RedBlack�ľֲ�ƽ�����
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
 * BST�ڵ���ת�任ͳһ�㷨��3�ڵ� + 4�����������ص���֮��ֲ��������ڵ��λ��
 * ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ�������������������ϲ㺯�����
 ******************************************************************************************/
template<typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNodePosi(T) v) {
    BinNodePosi(T) gg;
    BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
    if ( IsLChild(*p) ) {       // p Ϊ g ������
        if ( IsLChild(*v) ) {   // g �� zig ����
            p->parent = g->parent;
            gg = connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {                   // v ��һ�� zag ������ g ����һ��zig����
            v->parent = g->parent;
            gg = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {       // p Ϊ g ���Һ���
        if ( IsRChild(*v) ) {   // g �� zag ����
            p->parent = g->parent;
            gg = connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {                    // v ��һ�� zig ������ g ����һ��zag����
            v->parent = g->parent;
            gg = connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
    return gg;
}


// ƽ����������Ĳ���
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