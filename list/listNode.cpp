//
// Created by 张锐 on 2020/5/18.
//

//紧靠当前节点之前插入新节点
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}


//紧随当前节点之后插入新节点
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
