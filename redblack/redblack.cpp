//
// Created by 47302 on 2020/5/23.
//

//双红修正
//若已（递归）转至树根，则将其转黑，整树黑高度也随之递增; 否则，x的父亲p必存在， 若p为黑，则可终止调整。否则既然p为红，则x的祖父必存在，且必为黑色
//视x叔父u的颜色分别处理,u为黑色（含NULL）时RR-1, 若u为红色RR-2；
template<typename T>
void RedBlack<T>::solveDoubleRed(BinNodePosi(T)x) {
    if (IsRoot (*x)) { this->_root->color = RB_BLACK;this->_root->height++; return; }
    BinNodePosi(T)p = x->parent; if (IsBlack (p)) return;
    BinNodePosi(T)g = p->parent;
    BinNodePosi(T)u = uncle (x);

    // RR-1
    if (IsBlack(u)) {
        if (IsLChild (*x) == IsLChild (*p)) //若x与p同侧(p成为新根节点)（即zIg-zIg或zAg-zAg），则p由红转黑，x保持红
            p->color = RB_BLACK;
        else //若x与p异侧(x成为新根节点)（即zIg-zAg或zAg-zIg），则x由红转黑，p保持红
            x->color = RB_BLACK;
        g->color = RB_RED; //g必定由黑转红
        BinNodePosi(T)gg = g->parent; //曾祖父（great-grand parent）
        BinNodePosi(T)r = FromParentTo (*g) = this->rotateAt(x); //调整后的子树根节点
        r->parent = gg; //与原曾祖父联接
    } else { //RR-2
        p->color = RB_BLACK;
        p->height++; //p由红转黑
        u->color = RB_BLACK;
        u->height++; //u由红转黑
        if (!IsRoot (*g)) g->color = RB_RED; //g若非根，则转红
        solveDoubleRed(g); //继续调整g（类似于尾递归，可优化为迭代形式）
    }
}

/******************************************************************************************
 * RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
 * 分为三大类共四种情况：
 *    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
 *    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
 *    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
 ******************************************************************************************/
template <typename T> void RedBlack<T>::solveDoubleBlack ( BinNodePosi(T) r ) {
    BinNodePosi(T) p = r ? r->parent : this->_hot; if ( !p ) return;    //r的父亲
    BinNodePosi(T) s = ( r == p->lc ) ? p->rc : p->lc;                  //r的兄弟

    //兄弟s为黑
    if ( IsBlack ( s ) ) {
        BinNodePosi(T) t = NULL; //s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
        if ( IsRed ( s->rc ) ) t = s->rc; //右子
        if ( IsRed ( s->lc ) ) t = s->lc; //左子
        if ( t ) { //黑s有红孩子：BB-1
            //备份原子树根节点p颜色，并对t及其父亲、祖父
            RBColor oldColor = p->color;
            // 以下，通过旋转重平衡，并将新子树的左、右孩子染黑
            BinNodePosi(T) b = FromParentTo ( *p ) = this->rotateAt ( t ); //旋转
            if ( HasLChild ( *b ) ) { b->lc->color = RB_BLACK; updateHeight ( b->lc ); } //左子
            if ( HasRChild ( *b ) ) { b->rc->color = RB_BLACK; updateHeight ( b->rc ); } //右子
            b->color = oldColor; updateHeight ( b ); //新子树根节点继承原根节点的颜色
        } else { //黑s无红孩子
            s->color = RB_RED; s->height--; //s转红
            if ( IsRed ( p ) ) { //BB-2R
                p->color = RB_BLACK;    //p转黑，但黑高度不变
            } else { //BB-2B
                p->height--;            //p保持黑，但黑高度下降
                solveDoubleBlack ( p ); //递归上溯
            }
        }
    } else { //兄弟s为红：BB-3
        s->color = RB_BLACK; p->color = RB_RED;                    //s转黑，p转红
        BinNodePosi(T) t = IsLChild ( *s ) ? s->lc : s->rc;     //取t与其父s同侧
        this->_hot = p; FromParentTo ( *p ) = this->rotateAt ( t );   //对t及其父亲、祖父做平衡调整
        solveDoubleBlack ( r ); //继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
    }
}

//更新节点x的高度
//孩子一般黑高度相等，除非出现双黑; 红黑树中各节点左、右孩子的黑高度通常相等; 这里之所以取更大值，是便于在删除节点后的平衡调整过程中，正确更新被删除节点父亲的黑高度;
// 否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
template<typename T>
int RedBlack<T>::updateHeight(BinNodePosi(T)x) {
    x->height = max( stature(x->lc), stature(x->rc) );
    x->height = IsBlack(x) ? x->height++ : x->height ;
}

//插入（重写）
template<typename T>
BinNodePosi(T)RedBlack<T>::insert(const T &e) {
    BinNodePosi(T) & x = this->search ( e ); if ( x ) return x;
    x = new BinNode<T> ( e, this->_hot, NULL, NULL, -1 ); this->_size++;
    solveDoubleRed ( x ); return x ? x : this->_hot->parent;
}

//从红黑树中删除关键码e；若目标节点存在且被删除，返回true；否则返回false
template <typename T>
bool RedBlack<T>::remove ( const T& e ) {
    BinNodePosi(T) & x = this->search ( e ); if ( !x ) return false;
    BinNodePosi(T) r = removeAt ( x, this->_hot ); if ( ! ( --this->_size ) ) return true;
    //_hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
    //若刚被删除的是根节点，则将其置黑，并更新黑高度
    if ( ! this->_hot ) { this->_root->color = RB_BLACK; updateHeight ( this->_root ); return true; }

    //以下，原x（现r）必非根，_hot必非空

    //若所有祖先的黑深度依然平衡，则无需调整
    if ( BlackHeightUpdated ( *this->_hot ) ) return true;
    //否则，若r为红，则只需令其转黑
    if ( IsRed ( r ) ){ r->color = RB_BLACK; r->height++; return true; }
    // 以下，原x（现r）均为黑色
    solveDoubleBlack ( r ); return true; //经双黑调整后返回
}
