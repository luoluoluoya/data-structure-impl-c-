//
// Created by 张锐 on 2020/5/19.
//

#pragma once

//引入二叉树节点类
#include "binnode.h"

/**
 * 二叉树模板类
 *
 * @tparam T
 */
template<typename T>
class BinTree {

private:
    int _size;  // 规模
    BinNodePosi(T)_root; // 根节点

protected:
    virtual int updateHeight(BinNodePosi(T)x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi(T)x); //更新节点x及其祖先的高度

public:
    BinTree() : _size(0), _root(NULL) {} //构造函数
    ~BinTree() { if (0 < _size) remove(_root); } //析构函数

    int size() const { return _size; }              //规模
    bool empty() const { return !_root; }           //判空
    BinNodePosi(T)root() const { return _root; }    //树根

    /**动态操作*/
    BinNodePosi(T)insertAsRoot(T const &e); //插入根节点
    BinNodePosi(T)insertAsLC(BinNodePosi(T)x, T const &e);      //e作为x的左孩子（原无）插入
    BinNodePosi(T)insertAsRC(BinNodePosi(T)x, T const &e);      //e作为x的右孩子（原无）插入
    BinNodePosi(T)attachAsLC(BinNodePosi(T)x, BinTree<T> *&L);  //L作为x左子树接入
    BinNodePosi(T)attachAsRC(BinNodePosi(T)x, BinTree<T> *&L);  //L作为x右子树接入

    int remove(BinNodePosi(T)x);            //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T> *secede(BinNodePosi(T)x);    //将子树x从当前树中摘除，并将其转换为一棵独立子树

    /**树遍历算法**/
    template<typename VST>void travLevel(VST &visit) { if (_root) _root->travLevel(visit); } //层次遍历
    template<typename VST>void travPre(VST &visit) { if (_root) _root->travPre(visit); } //先序遍历
    template<typename VST>void travIn(VST &visit) { if (_root) _root->travIn(visit); } //中序遍历
    template<typename VST>void travPost(VST &visit) { if (_root) _root->travPost(visit); } //后序遍历

    //比较器（其余自行补充）
    bool operator<(BinTree<T> const &t) { return _root && t._root && lt(_root, t._root); }
    //判等器
    bool operator==(BinTree<T> const &t) { return _root && t._root && (_root == t._root); }

//    void stretchToLPath() { stretchByZag(_root); }          //借助zag旋转，转化为左向单链
//    void stretchToRPath() { stretchByZig(_root, _size); }   //借助zig旋转，转化为右向单链
};

#include "bintree.cpp"

