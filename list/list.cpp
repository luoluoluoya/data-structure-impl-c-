//
// Created by ���� on 2020/5/18.
//

#include "../share/tool.h"

//�б���ʱ�ĳ�ʼ��
template<typename T>
void List<T>::init() {
    header  = new ListNode<T>;
    trailer = new ListNode<T>;
    header->succ    = trailer;  header->pred    = NULL;
    trailer->pred   = header;   trailer->succ   = NULL;
    _size = 0;
}

//������нڵ�
//����ɾ���׽ڵ㣬ֱ���б���
template<typename T>
int List<T>::clear() {
    int oldSize = _size;
    while (_size) remove( header->succ );
    return oldSize;
}

//�����б�����λ��p���n�� [p, p+n)
//p �ĺ��Ԫ�� ����� n ��
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
    init();
    while (n--) { insertAsLast( (p->data) ); p = p->succ; }
}

//�����б�Ĺ鲢����ǰ�б�����p���n��Ԫ�أ����б�L����q���m��Ԫ�ع鲢
//[p, p+n), L:[q, q+m) => [p, p+m+n)
//��q��δ�Ƴ�����֮ǰ, ��p������������v(p) <= v(q)����p����ϲ����б����滻Ϊ��ֱ�Ӻ��; ��p�ѳ����ҽ��v(q) < v(p)����qת����p֮ǰ
template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T> &L, ListNodePosi(T) q, int m) {
    // ����ǰ����������header��ȷ���鲢������ģ��£����
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

//�Դ�p��ʼ������n���ڵ�鲢����
template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n) {
    if ( n < 2 ) return; //��������Χ���㹻С����ֱ�ӷ��أ�
    int m = n >> 1; //���е�Ϊ��
    ListNodePosi(T) q = p; for ( int i = 0; i < m; i++ ) q = q->succ; //�����б�
    mergeSort ( p, m ); mergeSort ( q, n - m ); //��ǰ�������б�ֱ�����
    merge ( p, m, *this, q, n - m ); //�鲢
}

//��p����n-1�������ѡ�������
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T)p, int n) {
    ListNodePosi(T) mx = p;
    for (ListNodePosi(T) cur = p; 1 < n; --n) {
        if ( p->data < (cur = cur->succ)->data ) mx = cur;
    }
    return mx;
}

//�Դ�p��ʼ������n���ڵ�ѡ������
template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
    ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
    for ( int i = 0; i < n; i++ ) tail = tail->succ;    //����������Ϊ(head, tail)
    while ( 1 < n ) {       //�����ٻ�ʣ�����ڵ�֮ǰ���ڴ�����������
        ListNodePosi(T) max = selectMax ( head->succ, n ); //�ҳ�����ߣ�����ʱ�������ȣ�
        insertB ( tail, remove ( max ) ); //����������������ĩβ����Ϊ���������µ���Ԫ�أ�
        tail = tail->pred; n--;
    }
}

//�Դ�p��ʼ������n���ڵ��������
template<typename T>
void List<T>::insertionSort(ListNodePosi(T) p, int n) {
    for ( int r = 0; r < n; r++ ) { //��һΪ���ڵ�
        insertA ( search ( p->data, r, p ), p->data ); //�����ʵ���λ�ò�����
        remove ( (p = p->succ)->pred ); //ת����һ�ڵ�
    }
}

//���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
template<typename T>
T &List<T>::operator[](Rank r) const {
    ListNodePosi(T) x = first();
    for (int i = 0; i < r; ++i)
        x = x->succ;
    return x->data;
}

//�ж��б��Ƿ�������(���ش��ڵ��������)
template<typename T>
int List<T>::disordered() const {
    int n = 0;
    ListNodePosi(T) p = first(); ListNodePosi(T) q;
    while ( (q = p->succ) != trailer) {
        if ( (p = q)->pred->data > q->data ) n++;
    }
    return n;
}

//�����������
//�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�����e�������
template<typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T)p) const {
    while ( 0 < n-- )
        if ( e == ( p = p->pred )->data ) return p; //����ȶԣ�ֱ�����л�ΧԽ��
    return NULL;    //pԽ����߽���ζ�������ڲ���e������ʧ��
}

//�����������
template<typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T)p) const {
    while ( 0 <= n-- ) //����p�������n��ǰ����������������Ƚ�
    {
        if ( ( ( p = p->pred )->data ) <= e ) break; //ֱ�����С���ֵԽ���ΧԽ��
    }
    return p; //���ز�����ֹ��λ��
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

//����ȥ��
//p���׽ڵ㿪ʼ����ֱ��ĩ�ڵ�,��p��r�����棩ǰ���в�����ͬ������ȷ���ڣ���ɾ��֮�������ȼ�һ
template<typename T>
int List<T>::deduplicate() {
    if ( _size < 2 ) return 0;  //ƽ���б���Ȼ���ظ�
    int oldSize = _size;        //��¼ԭ��ģ
    ListNodePosi(T) p = header; Rank r = 0;
    while ( trailer != ( p = p->succ ) ) {
        ListNodePosi(T) q = find ( p->data, r, p );
        q ? remove ( q ) : r++;
    }
    return oldSize - _size; //�б��ģ�仯��������ɾ��Ԫ������
}

//����ȥ��
template<typename T>
int List<T>::uniquify() {
    //  if ( _size < 2 ) return 0; //ƽ���б���Ȼ���ظ�
    //   int oldSize = _size; //��¼ԭ��ģ
    //   ListNodePosi(T) p = first(); ListNodePosi(T) q; //pΪ��������㣬qΪ����
    //   while ( trailer != ( q = p->succ ) ) //����������ڵĽڵ��(p, q)
    //      if ( p->data != q->data ) p = q; //�����죬��ת����һ����
    //      else remove ( q ); //������ͬ����ɾ������
    //   return oldSize - _size; //�б��ģ�仯��������ɾ��Ԫ������

    int oldSize = _size;
    ListNodePosi(T) x = first();
    while (x != trailer)
        if ( x->data == (x = x->succ)->data )remove(x->pred);
    return oldSize - _size;
}

//ǰ����
template<typename T>
void List<T>::reverse() {
    ListNodePosi(T) p = first();
    ListNodePosi(T) q = last();
    while (p != q)
        swap( (p = p->succ)->pred->data, (q = q->pred)->succ->data );
}

//����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
template<typename T>
void List<T>::traverse(void (*visit)(T &)) {
    ListNodePosi(T) x = first();
    while (x != trailer)
        visit( (x = x->succ)->pred->data );
}

//����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
template<typename T>
template<typename VST>
void List<T>::traverse(VST &visit) {
    ListNodePosi(T) x = first();
    while (x != trailer)
        visit( (x = x->succ)->pred->data );
}
