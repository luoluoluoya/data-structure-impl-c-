//
// Created by 张锐 on 2020/5/21.
//

#pragma once

//引入B-树节点类
#include "btnode.h"
#include "../share/release.h"
/*

 */


/**
 * B-树模板类
 * ===============
    n阶B树分析：
        分支数: [ ceil(n/2), n ]； 节点数: [ ceil(n/2)-1, n-1 ]
        节点上溢时上溢节点必定恰好包含 n 个节点：(当跟节点发生上溢时，树的高度增加1)
            1. 中位数节点上溢到夫节点对应位置
            2. 左右部分分裂为两个节点
        节点下溢时下溢节点必定恰好包含 ceil(n/2)-2 个节点：(当跟节点发生下溢时，树的高度较少1)
            1. 左顾右盼（考察兄弟节点元素是否充足（ _order >= ceil(n/2) ），充足的情况下通过父节点转借兄弟节点的元素）
            2. 当兄弟节点也濒临下溢时（ _order = ceil(n/2) -1 ）. 从父节点借出一个节点来执行合并 （ 1 + ceil(n/2) -1 + ceil(n/2) -2 = 2*ceil(n/2)-2 ）
 * ===============
 * @tparam T
 */
template<typename T>
class BTree {
protected:
    int _size;          //存放的关键码总数
    int _order;         //B-树的阶次，至少为3——创建时指定，一般不能修改
    BTNodePosi(T)_root; //根节点
    BTNodePosi(T)_hot;  //BTree::search()最后访问的非空（除非树空）的节点位置
    void solveOverflow(BTNodePosi(T));  //因插入而上溢之后的分裂处理
    void solveUnderflow(BTNodePosi(T)); //因删除而下溢之后的合并处理
public:
    //构造函数：默认为最低的3阶
    BTree(int order = 3) : _order(order), _size(0) { _root = new BTNode<T>(); }

    ~BTree() { if (_root) release(_root); }     //析构函数：释放所有节点
    int const order() { return _order; }        //阶次
    int const size() { return _size; }          //规模
    BTNodePosi(T)&root() { return _root; }      //树根
    bool empty() const { return !_root; }       //判空
    BTNodePosi(T)search(const T &e);            //查找
    bool insert(const T &e);                    //插入
    bool remove(const T &e);                    //删除
};

#include "btree.cpp"