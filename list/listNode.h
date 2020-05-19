//
// Created by 张锐 on 2020/5/18.
//

#pragma once

typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* // 列表节点位置

/**
 * 列表节点模板类（以双向链表形式实现）
 *
 * @tparam T
 */
template<typename T>
struct ListNode {
    // 成员
    // 数值、前驱、后继
    T data;
    ListNodePosi(T)pred;
    ListNodePosi(T)succ;

    // 构造函数
    ListNode() {} // 针对header和trailer的构造
    ListNode(T e, ListNodePosi(T)p = NULL, ListNodePosi(T)s = NULL) : data(e), pred(p), succ(s) {} // 默认构造器
    // 操作接口
    ListNodePosi(T)insertAsPred(T const &e); //紧靠当前节点之前插入新节点
    ListNodePosi(T)insertAsSucc(T const &e); //紧随当前节点之后插入新节点
};

#include "listNode.cpp"