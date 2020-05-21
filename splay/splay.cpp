//
// Created by 张锐 on 2020/5/21.
//

//将节点v伸展至根
//基于二层伸展
template <typename NodePosi> inline //在节点*p与*lc（可能为空）之间建立父（左）子关系
void attachAsLChild ( NodePosi p, NodePosi lc ) { p->lc = lc; if ( lc ) lc->parent = p; }

template <typename NodePosi> inline //在节点*p与*rc（可能为空）之间建立父（右）子关系
void attachAsRChild ( NodePosi p, NodePosi rc ) { p->rc = rc; if ( rc ) rc->parent = p; }

//Splay树伸展算法：从节点v出发逐层伸展
//自下而上，反复对*v做双层伸展, 每轮之后*v都以原曾祖父（great-grand parent）为父; 若*v原先的曾祖父*gg不存在，则*v现在应为树根, 否则，*gg此后应该以*v作为左或右孩子
//双层伸展结束时，必有g == NULL，但p可能非空； 若p果真非空，则额外再做一次单旋
template <typename T>
BinNodePosi(T) Splay<T>::splay ( BinNodePosi(T) v ) {
    if ( !v ) return NULL; BinNodePosi(T) p; BinNodePosi(T) g; //*v的父亲与祖父
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

    //调整之后新树根应为被伸展的节点，故返回该节点的位置以便上层函数更新树根
    v->parent = NULL; return v;
}

//查找（重写）
template<typename T>
BinNodePosi(T)& Splay<T>::search(const T &e) {
    BinNodePosi(T) x = this->searchIn( this->_root, e, (this->_hot = NULL) );
    this->_root = splay( x ? x : this->_hot );
    return this->_root;
}

//插入（重写）
//无论e是否存在于原树中，返回时总有_root->data == e
template<typename T>
BinNodePosi(T) Splay<T>::insert(const T &e) {
    // 处理原树为空的退化情况
    if ( !this->_root ) { this->_size++; return this->_root = new BinNode<T>(e); }

    // 查找节点
    BinNodePosi(T) x = search(e); if ( e == x->data ) return x;

    BinNodePosi(T) r = this->_root; this->_size++;
    // _root 为待插入节点的父节点
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

//从伸展树中删除关键码e
//若目标节点存在且被删除，返回true；否则返回false
//删除策略为：将左子树从当前树中暂时移除； 在右子树中寻找当前元素(此次查找必定失败，且将大于当前节点且小于右子树其他元素的节点移之跟节点)； 将右子树作为新树， 左子树作为跟节点的左子树
template <typename T>
bool Splay<T>::remove ( const T& e ) {
    //若树空或目标不存在，则无法删除
    if ( !this->_root || e != search(e)->data ) return false;
    BinNodePosi(T) r = this->_root;
    if ( !HasLChild(*r) ) {
        this->_root = r->rc; if ( this->_root ) this->_root->parent = NULL;
    } else if ( !HasRChild(*r) ) {
        this->_root = r->lc; if ( this->_root ) this->_root->parent = NULL;
    } else {
        // 切除左子树
        BinNodePosi(T) lChild = this->_root->lc; lChild->parent = NULL; this->_root->lc = NULL;

        // 右子树作为新树
        this->_root = this->_root->rc;  this->_root->parent = NULL;
        search(e);
        this->_root->lc = lChild; lChild->parent = this->_root;
    }
    delete r; this->_size--; if (this->_root) this->updateHeight(this->_root);
    return true;
}
