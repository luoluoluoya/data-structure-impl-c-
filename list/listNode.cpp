//
// Created by ���� on 2020/5/18.
//

//������ǰ�ڵ�֮ǰ�����½ڵ�
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, pred, this);
    pred->succ = x;
    pred = x;
    return x;
}


//���浱ǰ�ڵ�֮������½ڵ�
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const &e) {
    ListNodePosi(T) x = new ListNode<T>(e, this, succ);
    succ->pred = x;
    succ = x;
    return x;
}
