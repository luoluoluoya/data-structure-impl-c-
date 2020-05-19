//
// Created by 张锐 on 2020/5/18.
//

#include "../share/tool.h"

//列表创建时的初始化
template<typename T>
void List<T>::init() {
    header  = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ    = trailer;  header->pred    = NULL;
    trailer->pred   = header;   trailer->succ   = NULL;
    _size = 0;
}

//清除所有节点
//反复删除首节点，直至列表变空
template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (_size) remove( header->succ );
    return oldSize;
}

//复制列表中自位置p起的n项 [p, p+n)
//p 的后继元素 需大于 n 个
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while (n--) { insertAsLast( (p->data) ); p = p->succ; }
}

//有序列表的归并：当前列表中自p起的n个元素，与列表L中自q起的m个元素归并
//[p, p+n), L:[q, q+m) => [p, p+m+n)
//在q尚未移出区间之前, 若p仍在区间内且v(p) <= v(q)，则p归入合并的列表，并替换为其直接后继; 若p已超出右界或v(q) < v(p)，则将q转移至p之前
template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T> &L, ListNodePosi(T) q, int m) {
    // 借助前驱（可能是header）确定归并后区间的（新）起点
    ListNodePosi(T) pp = p->pred;
    while ( 0 < m ) {
        if ( ( 0 < n ) && ( p->data <= q->data ) ) {
            if ( q == ( p = p->succ ) )
                break;
            n--;
        } else {
            insertB ( p, L.remove ( ( q = q->succ )->pred ) ); m--;
        }
    }
    p = pp->succ;
}

//对从p开始连续的n个节点归并排序
template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
    if ( n < 2 ) return; //若待排序范围已足够小，则直接返回；
    int m = n >> 1; //以中点为界
    ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //均分列表
    mergeSort ( p, m ); mergeSort ( q, n - m ); //对前、后子列表分别排序
    merge ( p, m, *this, q, n - m ); //归并
}

//在p及其n-1个后继中选出最大者
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T)p, int n) {
    ListNodePosi(T) mx = p;
    for (ListNodePosi(T) cur = p; 1 < n; --n) {
        if ( p->data < (cur = cur->succ)->data ) mx = cur;
    }
    return mx;
}

//对从p开始连续的n个节点选择排序
template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->succ;    //待排序区间为(head, tail)
    while ( 1 < n ) {       //在至少还剩两个节点之前，在待排序区间内
        ListNodePosi(T) max = selectMax ( head->succ, n ); //找出最大者（歧义时后者优先）
        insertB ( tail, remove ( max ) ); //将其移至无序区间末尾（作为有序区间新的首元素）
        tail = tail->pred; n--;
    }
}

//对从p开始连续的n个节点插入排序
template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) {
    for ( int r = 0; r < n; r++ ) { //逐一为各节点
        insertA ( search ( p->data, r, p ), p->data ); //查找适当的位置并插入
        remove ( (p = p->succ)->pred ); //转向下一节点
    }
}

//重载，支持循秩访问（效率低）
template<typename T>
T &List<T>::operator[](Rank r) const {
    ListNodePosi(T) x = first();
    for (int i = 0; i < r; ++i)
        x = x->succ;
    return x->data;
}

//判断列表是否已排序(返回存在的逆序对数)
template<typename T>
int List<T>::disordered() const {
    int n = 0;
    ListNodePosi(T) p = first(); ListNodePosi(T) q;
    while ( (q = p->succ) != trailer) {
        if ( (p = q)->pred->data > q->data ) n++;
    }
    return n;
}

//无序区间查找
//在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
template<typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T)p) const {
    while ( 0 < n-- )
        if ( e == ( p = p->pred )->data ) return p; //逐个比对，直至命中或范围越界
    return NULL;    //p越出左边界意味着区间内不含e，查找失败
}

//有序区间查找
template<typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T)p) const {
    while ( 0 <= n-- ) //对于p的最近的n个前驱，从右向左逐个比较
    {
        if ( ( ( p = p->pred )->data ) <= e ) break; //直至命中、数值越界或范围越界
    }
    return p; //返回查找终止的位置
}


template<typename T>
T List<T>::remove(ListNodePosi(T)p) {
    T e = p->data;
    p->pred->succ = p->succ; p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}

template<typename T>
void List<T>::sort(ListNodePosi(T)p, int n) {
    switch (rand() % 3) {
        case 0:
            mergeSort(p, n);
            break;
        case 1:
            selectionSort(p, n);
            break;
        case 2:
            insertionSort(p, n);
            break;
    }
}

//无序去重
//p从首节点开始依次直到末节点,在p的r个（真）前驱中查找雷同者若的确存在，则删除之；否则秩加一
template<typename T>
int List<T>::deduplicate() {
    if ( _size < 2 ) return 0;  //平凡列表自然无重复
    int oldSize = _size;        //记录原规模
    ListNodePosi(T) p = header; Rank r = 0;
    while ( trailer != ( p = p->succ ) ) {
        ListNodePosi(T) q = find ( p->data, r, p );
        q ? remove ( q ) : r++;
    }
    return oldSize - _size; //列表规模变化量，即被删除元素总数
}

//有序去重
template<typename T>
int List<T>::uniquify() {
    //  if ( _size < 2 ) return 0; //平凡列表自然无重复
    //   int oldSize = _size; //记录原规模
    //   ListNodePosi(T) p = first(); ListNodePosi(T) q; //p为各区段起点，q为其后继
    //   while ( trailer != ( q = p->succ ) ) //反复考查紧邻的节点对(p, q)
    //      if ( p->data != q->data ) p = q; //若互异，则转向下一区段
    //      else remove ( q ); //否则（雷同），删除后者
    //   return oldSize - _size; //列表规模变化量，即被删除元素总数

    int oldSize = _size;
    ListNodePosi(T) x = first();
    while (x != trailer)
        if ( x->data == (x = x->succ)->data )remove(x->pred);
    return oldSize - _size;
}

//前后倒置
template<typename T>
void List<T>::reverse() {
    ListNodePosi(T) p = first();
    ListNodePosi(T) q = last();
    while (p != q)
        swap( (p = p->succ)->pred->data, (q = q->pred)->succ->data );
}

//遍历，依次实施visit操作（函数指针，只读或局部性修改）
template<typename T>
void List<T>::traverse(void (*visit)(T &)) {
    ListNodePosi(T) x = first();
    while (x != trailer)
        visit( (x = x->succ)->pred->data );
}

//遍历，依次实施visit操作（函数对象，可全局性修改）
template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) {
    ListNodePosi(T) x = first();
    while (x != trailer)
        visit( (x = x->succ)->pred->data );
}
