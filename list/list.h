//
// Created by ���� on 2020/5/18.
//

#pragma once

#include "listNode.h" //�����б�ڵ���

/**
 * �б�ģ����
 * @tparam T
 */
template<typename T>
class List {

private:
    // ��ģ��ͷ�ڱ���β�ڱ�
    int _size;
    ListNodePosi(T)header;
    ListNodePosi(T)trailer;

protected:

    //�б���ʱ�ĳ�ʼ��
    void init();

    //������нڵ�
    int clear();

    //�����б�����λ��p���n��
    void copyNodes(ListNodePosi(T), int);

    //�鲢
    void merge(ListNodePosi(T)&, int, List<T> &, ListNodePosi(T), int);

    //�Դ�p��ʼ������n���ڵ�鲢����
    void mergeSort(ListNodePosi(T)&, int);

    //�Դ�p��ʼ������n���ڵ�ѡ������
    void selectionSort(ListNodePosi(T), int);

    //�Դ�p��ʼ������n���ڵ��������
    void insertionSort(ListNodePosi(T), int);

public:
    // ���캯��
    List() { init(); } //Ĭ��

    //���帴���б�L
    List(List<T> const &L) { copyNodes(L.first(), L._size); }

    //�����б�L���Ե�r�����n��
    List(List<T> const &L, Rank r, int n) { copyNodes(L[r], n); }

    //�����б�����λ��p���n��
    List(ListNodePosi(T)p, int n) { copyNodes(p, n); }

    // ��������
    // �ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
    ~List() { clear(); delete header; delete trailer; }

    /**ֻ�����ʽӿ�**/
    Rank size() const { return _size; } //��ģ
    bool empty() const { return _size <= 0; } //�п�

    //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
    T &operator[](Rank r) const;

    ListNodePosi(T)first() const { return header->succ; } //�׽ڵ�λ��
    ListNodePosi(T)last() const { return trailer->pred; } //ĩ�ڵ�λ��

    //�ж�λ��p�Ƿ����Ϸ�
    //��ͷ��β�ڵ��ͬ��NULL
    bool valid(ListNodePosi(T)p) { return p && (trailer != p) && (header != p); }

    //�ж��б��Ƿ�������(���ش��ڵ��������)
    int disordered() const;

    //�����б����
    ListNodePosi(T)find(T const &e) const { return find(e, _size, trailer); }
    //�����������
    ListNodePosi(T)find(T const &e, int n, ListNodePosi(T)p) const;


    //�����б����
    ListNodePosi(T)search(T const &e) const { return search(e, _size, trailer); }
    //�����������
    ListNodePosi(T)search(T const &e, int n, ListNodePosi(T)p) const;

    //��p����n-1�������ѡ�������
    ListNodePosi(T)selectMax(ListNodePosi(T)p, int n);
    //���������
    ListNodePosi(T)selectMax() { return selectMax(header->succ, _size); }


    /**��д���ʽӿ�**/
    //��e�����׽ڵ����
    ListNodePosi(T)insertAsFirst(T const &e) { _size++; header->insertAsSucc(e); }
    //��e����ĩ�ڵ����
    ListNodePosi(T)insertAsLast(T const &e) { _size++; trailer->insertAsPred(e); }
    //��e����p�ĺ�̲���
    ListNodePosi(T)insertA(ListNodePosi(T)p, T const &e) { _size++; p->insertAsSucc(e); }
    //��e����p��ǰ������
    ListNodePosi(T)insertB(ListNodePosi(T)p, T const &e) { _size++; p->insertAsPred(e); }

    //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
    T remove(ListNodePosi(T)p);

    //ȫ�б�鲢
    // void merge(List<T> &L) { merge( first(), _size, L, L.first(), L._size ); _size+=L._size; }   // todo ?

    void sort(ListNodePosi(T)p, int n);     //�б���������
    void sort() { sort(first(), _size); }   //�б���������

    int deduplicate(); //����ȥ��
    int uniquify(); //����ȥ��

    //ǰ����
    void reverse();

    // ����
    void traverse(void (* )(T &));  //����������ʵʩvisit����������ָ�룬ֻ����ֲ����޸ģ�
    template<typename VST>
    void traverse(VST &);           //����������ʵʩvisit�������������󣬿�ȫ�����޸ģ�
};

#include "list.cpp"