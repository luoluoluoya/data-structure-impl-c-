//
// Created by ���� on 2020/5/18.
//

#pragma once

typedef int Rank;

// Ĭ�ϵĳ�ʼ����
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
private:
    Rank _size;
    int _capacity;
    T *_elem; //��ģ��������������
protected:
    //������������A[lo, hi)
    void copyFrom(T const *A, Rank lo, Rank hi);

    // �ռ䲻��ʱ����
    void expand();

    // װ�����ӹ�Сʱѹ��
    void shrink();

    // һ��ð�ݣ�ɨ�轻����
    bool bubble(Rank lo, Rank hi);

    // ���������㷨
    void bubbleSort(Rank lo, Rank hi);

    // ѡȡ���Ԫ��
    Rank max(Rank lo, Rank hi);

    // ѡ�������㷨
    void selectionSort(Rank lo, Rank hi);

    // �鲢�㷨
    void merge(Rank lo, Rank mi, Rank hi);

    // �鲢�����㷨
    void mergeSort(Rank lo, Rank hi);

    // ��㹹���㷨
    Rank partition(Rank lo, Rank hi);

    // ���������㷨
    void quickSort(Rank lo, Rank hi);

    // �������Ժ�����ȫ�ѽ��⣩
    // void heapSort(Rank lo, Rank hi);

public:
    // ���캯��
    // ����Ϊc����ģΪs������Ԫ�س�ʼΪv ( s <= c )
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }

    Vector(T const *A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const *A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
    // ��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�

    /**ֻ�����ʽӿ�**/
    // ��ģ
    Rank size() const { return _size; }

    // �п�
    bool empty() const { return !_size; }

    // �ж������Ƿ�������
    int disordered() const;

    // ���������������
    Rank find(T const &e) const { return find(e, 0, _size); }

    // ���������������
    Rank find(T const &e, Rank lo, Rank hi) const;

    // ���������������
    Rank search(T const &e) const { return (0 >= _size) ? -1 : search(e, 0, _size); }

    // ���������������
    Rank search(T const &e, Rank lo, Rank hi) const;

    /**��д���ʽӿ�**/
    // �����±������������������������ʽ���ø�Ԫ��
    T &operator[](Rank r) const;

    // ���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    Vector<T> &operator=(Vector<T> const &);

    // ɾ����Ϊr��Ԫ��
    T remove(Rank r);

    // ɾ����������[lo, hi)֮�ڵ�Ԫ��
    int remove(Rank lo, Rank hi);

    // ����Ԫ��
    Rank insert(Rank r, T const &e);

    // Ĭ����ΪĩԪ�ز���
    Rank insert(T const &e) { return insert(_size, e); }


    // ��[lo, hi)����
    void sort(Rank lo, Rank hi);

    // ��������
    void sort() { sort(0, _size); }


    // ��[lo, hi)����
    void unsort(Rank lo, Rank hi);

    //��������
    void unsort() { unsort(0, _size); }

    // ����ȥ��
    int deduplicate();

    // ����ȥ��
    int uniquify();

    // ����
    void traverse(void (* )(T &));  //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    template<typename VST>
    void traverse(VST &);           //������ʹ�ú������󣬿�ȫ�����޸ģ�
};

#include "vector.cpp"