//
// Created by ���� on 2020/5/19.
//

#include "binnode_macro.h"
#include "../share/tool.h"
#include "../queue/queue.h"
#include "../stack/stack.h"


//ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
template<typename T>
int BinNode<T>::size() {
    int n = 1;
    if (lc) n+=lc->size();
    if (rc) n+=rc->size();
    return n;
}

//��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
// ǰ�����������Ӳ�����
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e) {
    return lc = new BinNode<T>(e, this);
}

//��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
// ǰ���������Һ��Ӳ�����
template<typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &) {
    return rc = new BinNode<T>(e, this);
}

//ȡ��ǰ�ڵ��ֱ�Ӻ��
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

/**�ڵ�����㷨**/
//������α���ͳһ���
template<typename T>
template<typename VST>void BinNode<T>::travLevel(VST &visit) {
    Queue<BinNodePosi(T)> Q;
    Q.enqueue(this);
    while (!Q.empty()) {
        BinNodePosi(T) x = Q.dequeue();
        visit(x->data);
        if ( HasLChild(*x) ) Q.enqueue(x->lc);
        if ( HasRChild(*x) ) Q.enqueue(x->rc);
    }
}

//�����������ͳһ���
template<typename T>
template<typename VST>
void BinNode<T>::travPre(VST &visit) {
    switch ( rand() % 3 ) {
        case 1:     travPreI1 ( this, visit ); break; //������#1
        case 2:     travPreI2 ( this, visit ); break; //������#2
        default:    travPreR ( this, visit ); break; //�ݹ��
    }
}

// ������������ݹ��
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

// ������������ݹ��
template<typename T, typename VST>
static void travPreI2(BinNodePosi(T)p, VST &visit) {
    Stack<BinNodePosi(T)> S;
    while (true) {
        while (p) {
            visit(p->data);
            S.push(p->rc);
            p = p->lc;
        }
        if (!S.empty()) break;
        p = S.pop();
    }
}

// ������������ݹ��
template<typename T, typename VST>
static void travPreR(BinNodePosi(T)p, VST &visit) {
    visit(p->data);
    if ( HasLChild(*p) )    travPreR(p->lc);
    if ( HasLChild(*p) )    travPreR(p->rc);
}


//�����������ͳһ���
template<typename T>
template<typename VST>void BinNode<T>::travIn(VST &visit) {
    switch ( rand() % 5 ) {
        case 1: travInI1 ( this, visit ); break; //������#1
        case 2: travInI2 ( this, visit ); break; //������#2
        case 3: travInI3 ( this, visit ); break; //������#3
        case 4: travInI4 ( this, visit ); break; //������#4
        default: travInR ( this, visit ); break; //�ݹ��
    }
}

//�����������������
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

//�����������������
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

//�����������������
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

//�����������������
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

//������������ݹ�
template<typename T, typename VST>
static void travInR(BinNodePosi(T)p, VST &visit) {
    if (!p) return;
    travInR(p->lc);
    visit(p->data);
    travInR(p->rc);
}

//�����������ͳһ���
template<typename T>
template<typename VST>void BinNode<T>::travPost(VST &visit) {
    switch ( rand() % 2 ) {
        case 1: travPostI ( this, visit ); break;  //������
        default: travPostR ( this, visit ); break; //�ݹ��
    }
}


//�������ĺ�������������棩
// ��ջ���ǵ�ǰ�ڵ�֮�������Ϊ�����֣�����ʱ������������Ϊ��֮�����У��ҵ�HLVFL���൱�ڵݹ��������У�����ջ������ǰһ�ڵ�֮��̣���������֮
// �Զ����£�������鵱ǰ�ڵ㣨��ջ��������������; �����Һ��ӣ�������ջȻ���ת������; ʵ�����Ѳ�����,����֮ǰ������ջ���Ŀսڵ�
template <typename T, typename VST>
void travPostI (BinNodePosi(T) x, VST& visit) {
    Stack<BinNodePosi(T)> S; //����ջ
    if ( x ) S.push ( x ); //���ڵ���ջ
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

//������������ݹ��
template<typename T, typename VST>
static void travPostR(BinNodePosi(T)p, VST &visit) {
    if (!p) return;
    travPostR(p->lc);
    travPostR(p->rc);
    visit(p->data);
}


/**��ת����**/
//˳ʱ����ת
template<typename T>
BinNodePosi(T) BinNode<T>::zig() {
    BinNodePosi(T) lChild = lc;
    lc = lChild->rc;    if (lc) lc->parent = this;

    lChild->parent = parent;
    if (parent) (IsLChild( *this ) ? parent->lc : parent->rc) = lChild;

    lChild->rc = this; parent = lChild;
    return lChild;
}

//��ʱ����ת
template<typename T>
BinNodePosi(T) BinNode<T>::zag() {
    BinNodePosi(T) rChild = rc;
    rc = rChild->lc;    if (lc) lc->parent = this;

    rChild->parent = parent;
    if (parent) (IsLChild( *this ) ? parent->lc : parent->rc) = rChild;

    rChild->lc = this; parent = rChild;
    return rChild;
}
