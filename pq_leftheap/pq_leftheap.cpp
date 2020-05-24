//
// Created by 47302 on 2020/5/23.
//

#pragma once

//根据相对优先级确定适宜的方式，合并以a和b为根节点的两个左式堆
//本算法只实现结构上的合并，堆的规模须由上层调用者负责更新
template<typename T>
static BinNodePosi(T)merge(BinNodePosi(T)a, BinNodePosi(T)b) {
    if (!a) return b; //退化情况
    if (!b) return a; //退化情况
    if (a->data < b->data) { BinNodePosi(T) t = a; a = b; b = t; }
    a->rc = merge(a->rc, b); //将a的右子堆，与b合并
    a->rc->parent = a; //并更新父子关系
    if (!a->lc || a->lc->npl < a->rc->npl) { //若有必要交换a的左、右子堆，以确保右子堆的npl不大
        BinNodePosi(T) t = a->lc; a->lc = a->rc; a->rc = t;
    }
    a->npl = a->rc ? a->rc->npl + 1 : 1;    //更新a的npl
    return a; //返回合并后的堆顶
}


//获取非空左式堆中优先级最高的词条
//按照此处约定，堆顶即优先级最高的词条
template<typename T>
T PQLeftHeap<T>::getMax() { return this->_root->data; }

//基于合并操作的词条删除算法（当前队列非空）
template<typename T>
T PQLeftHeap<T>::delMax() {
    BinNodePosi(T)lHeap = this->_root->lc; //左子堆
    BinNodePosi(T)rHeap = this->_root->rc; //右子堆
    T e = this->_root->data;
    delete this->_root;
    this->_size--;     //删除根节点
    this->_root = merge(lHeap, rHeap);           //原左右子堆合并
    if (this->_root) this->_root->parent = NULL;   //若堆非空，还需相应设置父子链接
    return e; //返回原根节点的数据项
}

//基于合并操作的词条插入算法
template<typename T>
void PQLeftHeap<T>::insert(T e) {
    BinNodePosi(T)v = new BinNode<T>(e); //为e创建一个二叉树节点.通过合并完成新节点的插入
    this->_root = merge(this->_root, v);
    this->_root->parent = NULL; //既然此时堆非空，还需相应设置父子链接
    this->_size++; //更新规模
}
