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
 * BST�ڵ���ת�任ͳһ�㷨��3�ڵ� + 4�����������ص���֮��ֲ��������ڵ��λ��
 * ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ�������������������ϲ㺯�����
 ******************************************************************************************/
template<typename T>
BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T)v) {
    BinNodePosi(T)gg;
    BinNodePosi(T)p = v->parent;
    BinNodePosi(T)g = p->parent;
    if (IsLChild(*p)) {       // p Ϊ g ������
        if (IsLChild(*v)) {   // g �� zig ����
            p->parent = g->parent;
            gg = connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {                   // v ��һ�� zag ������ g ����һ��zig����
            v->parent = g->parent;
            gg = connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {       // p Ϊ g ���Һ���
        if (IsRChild(*v)) {   // g �� zag ����
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
BinNodePosi(T)&BST<T>::search(const T &e) {
    return searchIn(BinTree<T>::_root, e, _hot);
}

template<typename T>
static BinNodePosi(T) &searchIn(BinNodePosi(T) &p, const T &e, BinNodePosi(T)&hot = NULL) {
    while (p && (p->data != e)) {
        hot = p;
        p = (p->data < e) ? (p->lc) : (p->rc);
    }
    return p;
}

////�ڵ�v��������ͨ���ڱ����Ĺؼ������e
//#define EQUAL(e, v)  (!(v) || (e) == (v)->data)
//
////����vΪ���ģ�AVL��SPLAY��rbTree�ȣ�BST�����в��ҹؼ���e
////����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��
//template <typename T>
//static BinNodePosi(T) & searchIn ( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot ) {
//    if ( EQUAL ( e, v ) ) return v; hot = v; //�˻���������������ڵ�v������
//    while ( 1 ) { //һ��أ��������ϵ�
//        BinNodePosi(T) & c = ( e < hot->data ) ? hot->lc : hot->rc; //ȷ�����뷽��
//        if ( EQUAL ( e, c ) ) return c; hot = c; //���з��أ���������һ��
//    } //hotʼ��ָ�����һ��ʧ�ܽڵ�
//}

//����
template<typename T>
BinNodePosi(T)BST<T>::insert(const T &e) {
    BinNodePosi(T)x = search(e);
    if (x) return x;
    x = new BinNode<T>(e, _hot);
    BinTree<T>::_size++;
    BinTree<T>::updateHeightAbove(_hot);
    return x;
}

//��BST����ɾ���ؼ���e
template<typename T>
bool BST<T>::remove(const T &e) {
    BinNodePosi(T)&x = search(e);
    if (!x) return false;  //ȷ��Ŀ����ڣ�����_hot�����ã�
    removeAt(x);
    BinTree<T>::_size--;  //ʵʩɾ��
    BinTree<T>::updateHeightAbove(_hot);                 //����_hot�����������ȵĸ߶�
    return true;
}


/******************************************************************************************
 * BST�ڵ�ɾ���㷨��ɾ��λ��x��ָ�Ľڵ㣨ȫ�־�̬ģ�庯����������AVL��Splay��RedBlack�ȸ���BST��
 * Ŀ��x�ڴ�ǰ�����Ҷ�λ����ȷ�Ϸ�NULL���ʱ�ɾ���ɹ�����searchIn��ͬ������֮ǰ���ؽ�hot�ÿ�
 * ����ֵָ��ʵ�ʱ�ɾ���ڵ�Ľ����ߣ�hotָ��ʵ�ʱ�ɾ���ڵ�ĸ��ס������߾��п�����NULL
 ******************************************************************************************/
template <typename T>
static BinNodePosi(T) removeAt ( BinNodePosi(T) & x, BinNodePosi(T) & hot ) {
    BinNodePosi(T) w = x;               //ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
    BinNodePosi(T) succ = NULL;         //ʵ�ʱ�ɾ���ڵ�Ľ�����
    if ( !HasLChild ( *x ) )        //��*x��������Ϊ�գ����
        succ = x = x->rc;              //ֱ�ӽ�*x�滻Ϊ��������
    else if ( !HasRChild ( *x ) )   //��������Ϊ�գ����
        succ = x = x->lc;              //�ԳƵش�����ע�⣺��ʱsucc != NULL
    else {                             //���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
        w = w->succ();                 //�����������У��ҵ�*x��ֱ�Ӻ��*w
        swap ( x->data, w->data );      //����*x��*w������Ԫ��
        BinNodePosi(T) u = w->parent;
        ( ( u == x ) ? u->rc : u->lc ) = succ = w->rc; //����ڵ�*w
    }
    hot = w->parent; //��¼ʵ�ʱ�ɾ���ڵ�ĸ���
    if ( succ ) succ->parent = hot; //������ɾ���ڵ�Ľ�������hot����
    delete w; return succ; //�ͷű�ժ���ڵ㣬���ؽ�����
}