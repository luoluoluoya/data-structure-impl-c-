//
// Created by 张锐 on 2020/5/19.
//

#include "binnode_macro.h"
#include "../queue/queue.h"
#include "../stack/stack.h"


//统计当前节点后代总数，亦即以其为根的子树的规模
template<typename T>
int BinNode<T>::size() {
    int n = 1;
    if (lc) n+=lc->size();
    if (rc) n+=rc->size();
    return n;
}

//作为当前节点的左孩子插入新节点
// 前置条件：左孩子不存在
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e) {
    return lc = new BinNode<T>(e, this);
}

//作为当前节点的右孩子插入新节点
// 前置条件：右孩子不存在
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e) {
    return rc = new BinNode<T>(e, this);
}

//取当前节点的直接后继
template<typename T>
BinNodePosi(T) BinNode<T>::succ() {
    BinNodePosi(T) succ = this;
    if (rc) {
        succ = rc;
        while ( HasLChild(*succ) ) succ = succ->lc;
    } else {
        while ( IsRChild(*succ) ) succ = succ->parent;
        succ = succ->parent;
    }
    return succ;
}

/**节点遍历算法**/
//子树层次遍历统一入口
template<typename T>
template<typename VST>void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data);
        printf("(height:%d)", x->height);
        if ( HasLChild(*x) ) Q.enqueue(x->lc);
        if ( HasRChild(*x) ) Q.enqueue(x->rc);
    }
}

//子树先序遍历统一入口
template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    switch ( rand() % 3 ) {
        case 0:     travPreI1 ( this, visit ); break; //迭代版#1
        case 1:     travPreI2 ( this, visit ); break; //迭代版#2
        default:     travPreR ( this, visit ); break; //递归版
    }
}

// 子树先序遍历递归版
template<typename T, typename VST>
static void travPreI1(BinNodePosi(T)p, VST &visit) {
    Stack<BinNodePosi(T)> S;
    if (p) S.push(p);
    while (!S.empty()) {
        p = S.pop();
        visit(p->data);
        if ( HasRChild(*p) ) S.push(p->rc);
        if ( HasLChild(*p) ) S.push(p->lc);
    }
}

// 子树先序遍历递归版
template<typename T, typename VST>
static void travPreI2(BinNodePosi(T)p, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        while (p) {
            visit(p->data);
            S.push(p->rc);
            p = p->lc;
        }
        if (S.empty()) break;
        p = S.pop();
    }
}

// 子树先序遍历递归版
template<typename T, typename VST>
static void travPreR(BinNodePosi(T)p, VST &visit) {
    visit(p->data);
    if ( HasLChild(*p) )    travPreR(p->lc, visit);
    if ( HasLChild(*p) )    travPreR(p->rc, visit);
}

//子树中序遍历统一入口
template<typename T>
template<typename VST>void BinNode<T>::travIn(VST &visit) {
    switch ( rand() % 5 ) {
        case 1: travInI1 ( this, visit ); break; //迭代版#1
        case 2: travInI2 ( this, visit ); break; //迭代版#2
        case 3: travInI3 ( this, visit ); break; //迭代版#3
        case 4: travInI4 ( this, visit ); break; //迭代版#4
        default: travInR ( this, visit ); break; //递归版
    }
}

//子树中序遍历迭代版
template<typename T, typename VST>
static void travInI1(BinNodePosi(T)p, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        while (p) {
            S.push(p);
            p = p->lc;
        }
        if (S.empty()) break;
        p = S.pop();
        visit(p->data);
        p = p->rc;
    }
}

//子树中序遍历迭代版
template<typename T, typename VST>
static void travInI2(BinNodePosi(T)p, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        if (p) {
            S.push(p);
            p = p->lc;
        } else if (!S.empty()) {
            p = S.pop();
            visit(p->data);
            p = p->rc;
        } else {
            break;
        }
    }
}

//子树中序遍历迭代版
template<typename T, typename VST>
static void travInI3(BinNodePosi(T)p, VST &visit) {
    bool backtrack = false;
    while (true) {
        while ( !backtrack && HasLChild(*p) )
            p = p->lc;
        visit(p->data);
        if ( HasRChild(*p) ) {
            backtrack = false;
            p = p->rc;
        } else {
            if ( !(p = p->succ()) ) break;
            backtrack = true;
        }
    }
}

//子树中序遍历迭代版
template<typename T, typename VST>
static void travInI4(BinNodePosi(T)p, VST &visit) {
    while (true) {
        while ( HasLChild(*p) ) p = p->lc;
        visit(p->data);
        while ( !HasRChild( *p) ) {
            if ( !(p = p->succ()) ) return;
            visit(p->data);
        }
        p = p->rc;
    }
}

//子树中序遍历递归
template<typename T, typename VST>
static void travInR(BinNodePosi(T)p, VST &visit) {
    if (!p) return;
    travInR(p->lc, visit);
    visit(p->data);
    travInR(p->rc, visit);
}

//子树后序遍历统一入口
template<typename T>
template<typename VST>void BinNode<T>::travPost(VST &visit) {
    switch ( rand() % 2 ) {
        case 1: travPostI ( this, visit ); break;  //迭代版
        default: travPostR ( this, visit ); break; //递归版
    }
}


//二叉树的后序遍历（迭代版）
// 若栈顶非当前节点之父（则必为其右兄），此时需在以其右兄为根之子树中，找到HLVFL（相当于递归深入其中）弹出栈顶（即前一节点之后继），并访问之
// 自顶而下，反复检查当前节点（即栈顶）尽可能向左; 若有右孩子，优先入栈然后才转至左孩子; 实不得已才向右,返回之前，弹出栈顶的空节点
template <typename T, typename VST>
void travPostI (BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; //辅助栈
    if ( x ) S.push ( x ); //根节点入栈
    while ( !S.empty() ) {
        if ( S.top() != x->parent ) {
            while ( BinNodePosi(T) x = S.top() ) {
                if ( HasLChild ( *x ) ) {
                    if ( HasRChild ( *x ) ) S.push ( x->rc );
                    S.push ( x->lc );
                } else {
                    S.push ( x->rc );
                }
            }
            S.pop();
        }
        x = S.pop(); visit ( x->data );
    }
}

//子树后序遍历递归版
template<typename T, typename VST>
static void travPostR(BinNodePosi(T)p, VST &visit) {
    if (!p) return;
    travPostR(p->lc, visit);
    travPostR(p->rc, visit);
    visit(p->data);
}


/**旋转操作**/
//顺时针旋转
template<typename T>
BinNodePosi(T) BinNode<T>::zig() {
    BinNodePosi(T) lChild = lc;
    lc = lChild->rc;    if (lc) lc->parent = this;

    lChild->parent = parent;
    if (parent) (IsLChild( *this ) ? parent->lc : parent->rc) = lChild;

    lChild->rc = this; parent = lChild;
    return lChild;
}

//逆时针旋转
template<typename T>
BinNodePosi(T) BinNode<T>::zag() {
    BinNodePosi(T) rChild = rc;
    rc = rChild->lc;    if (lc) lc->parent = this;

    rChild->parent = parent;
    if (parent) (IsLChild( *this ) ? parent->lc : parent->rc) = rChild;

    rChild->lc = this; parent = rChild;
    return rChild;
}
