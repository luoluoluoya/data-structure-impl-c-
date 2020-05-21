//
// Created by ���� on 2020/5/21.
//

//���ڵ�v��չ����
//���ڶ�����չ
template <typename NodePosi> inline //�ڽڵ�*p��*lc������Ϊ�գ�֮�佨���������ӹ�ϵ
void attachAsLChild ( NodePosi p, NodePosi lc ) { p->lc = lc; if ( lc ) lc->parent = p; }

template <typename NodePosi> inline //�ڽڵ�*p��*rc������Ϊ�գ�֮�佨�������ң��ӹ�ϵ
void attachAsRChild ( NodePosi p, NodePosi rc ) { p->rc = rc; if ( rc ) rc->parent = p; }

//Splay����չ�㷨���ӽڵ�v���������չ
//���¶��ϣ�������*v��˫����չ, ÿ��֮��*v����ԭ���游��great-grand parent��Ϊ��; ��*vԭ�ȵ����游*gg�����ڣ���*v����ӦΪ����, ����*gg�˺�Ӧ����*v��Ϊ����Һ���
//˫����չ����ʱ������g == NULL����p���ܷǿգ� ��p����ǿգ����������һ�ε���
template <typename T>
BinNodePosi(T) Splay<T>::splay ( BinNodePosi(T) v ) {
    if ( !v ) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; //*v�ĸ������游
    while ( ( p = v->parent ) && ( g = p->parent ) ) {
        BinNodePosi(T) gg = g->parent;
        if ( IsLChild ( *v ) )
            if ( IsLChild ( *p ) ) { //zig-zig
                attachAsLChild ( g, p->rc ); attachAsLChild ( p, v->rc );
                attachAsRChild ( p, g ); attachAsRChild ( v, p );
            } else { //zig-zag
                attachAsLChild ( p, v->rc ); attachAsRChild ( g, v->lc );
                attachAsLChild ( v, g ); attachAsRChild ( v, p );
            }
        else if ( IsRChild ( *p ) ) { //zag-zag
            attachAsRChild ( g, p->lc ); attachAsRChild ( p, v->lc );
            attachAsLChild ( p, g ); attachAsLChild ( v, p );
        } else { //zag-zig
            attachAsRChild ( p, v->lc ); attachAsLChild ( g, v->rc );
            attachAsRChild ( v, g ); attachAsLChild ( v, p );
        }
        if ( !gg ) v->parent = NULL;
        else
            ( g == gg->lc ) ? attachAsLChild ( gg, v ) : attachAsRChild ( gg, v );
        this->updateHeight ( g ); this->updateHeight ( p ); this->updateHeight ( v );
    }

    if ( (p = v->parent) ) {
        if ( IsLChild ( *v ) ) { attachAsLChild ( p, v->rc ); attachAsRChild ( v, p ); }
        else                   { attachAsRChild ( p, v->lc ); attachAsLChild ( v, p ); }
        this->updateHeight ( p ); this->updateHeight ( v );
    }

    //����֮��������ӦΪ����չ�Ľڵ㣬�ʷ��ظýڵ��λ���Ա��ϲ㺯����������
    v->parent = NULL; return v;
}

//���ң���д��
template<typename T>
BinNodePosi(T)& Splay<T>::search(const T &e) {
    BinNodePosi(T) x = this->searchIn( this->_root, e, (this->_hot = NULL) );
    this->_root = splay( x ? x : this->_hot );
    return this->_root;
}

//���루��д��
//����e�Ƿ������ԭ���У�����ʱ����_root->data == e
template<typename T>
BinNodePosi(T) Splay<T>::insert(const T &e) {
    // ����ԭ��Ϊ�յ��˻����
    if ( !this->_root ) { this->_size++; return this->_root = new BinNode<T>(e); }

    // ���ҽڵ�
    BinNodePosi(T) x = search(e); if ( e == x->data ) return x;

    BinNodePosi(T) r = this->_root; this->_size++;
    // _root Ϊ������ڵ�ĸ��ڵ�
    if (e < x->data) {
        r->parent = this->_root = new BinNode<T>(e, NULL, r->lc, r);
        if ( HasLChild(*r) ) { r->lc->parent = this->_root; r->lc = NULL; }
    } else {
        r->parent = this->_root = new BinNode<T>(e, NULL, r, r->rc);
        if ( HasRChild(*r) ) { r->rc->parent = this->_root; r->rc = NULL; }
    }
    this->updateHeightAbove(r);
    return this->_root;
}

//����չ����ɾ���ؼ���e
//��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false
//ɾ������Ϊ�����������ӵ�ǰ������ʱ�Ƴ��� ����������Ѱ�ҵ�ǰԪ��(�˴β��ұض�ʧ�ܣ��ҽ����ڵ�ǰ�ڵ���С������������Ԫ�صĽڵ���֮���ڵ�)�� ����������Ϊ������ ��������Ϊ���ڵ��������
template <typename T>
bool Splay<T>::remove ( const T& e ) {
    //�����ջ�Ŀ�겻���ڣ����޷�ɾ��
    if ( !this->_root || e != search(e)->data ) return false;
    BinNodePosi(T) r = this->_root;
    if ( !HasLChild(*r) ) {
        this->_root = r->rc; if ( this->_root ) this->_root->parent = NULL;
    } else if ( !HasRChild(*r) ) {
        this->_root = r->lc; if ( this->_root ) this->_root->parent = NULL;
    } else {
        // �г�������
        BinNodePosi(T) lChild = this->_root->lc; lChild->parent = NULL; this->_root->lc = NULL;

        // ��������Ϊ����
        this->_root = this->_root->rc;  this->_root->parent = NULL;
        search(e);
        this->_root->lc = lChild; lChild->parent = this->_root;
    }
    delete r; this->_size--; if (this->_root) this->updateHeight(this->_root);
    return true;
}
