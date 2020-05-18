//
// Created by ���� on 2020/5/18.
//

#pragma once
#include "../share/tool.h"

// ������������A[lo, hi)
template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[ (_capacity = (hi - lo) >> 1) ]; _size = 0;
    for (Rank i = lo; i < hi; _elem[_size++] = A[i++]);
}

// ����
// �˴�δ����������ӽ��������ж�, ���ݲ���Ҳֻ�����ݼ򵥵ķ�������
template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return ;
    T *oldElem = _elem; _elem = new T[ (_capacity <<= 1) ];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}


// �� 1/4 ��Ϊѹ�����ٽ������� ÿ��ѹ��ռ�ÿռ����
template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1 || _capacity < _size << 2) return; // 1/4ռ����
    T *oldElem = _elem; _elem = new T[ (_capacity >>= 1) ];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}

// һ��ð�ݣ�ɨ�轻����[lo, hi)
template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}


// ���������㷨
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (lo < hi)
        if ( bubble(lo, hi--) ) break;
}

// ѡȡ���Ԫ�� [lo, hi]
template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
    T max = lo;
    while (++lo <= hi)
        if ( _elem[lo] >= _elem[max] )   // ѡ�����Ԫ�أ� ���Ԫ������ʱ��֤���ص�������Ԫ��
            max = lo;
    return max;
}

// ѡ�������㷨 [lo, hi)
template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
    while (lo < hi--)
        swap( _elem[ max(lo, hi) ], _elem[hi] );
}

// �鲢�㷨, �ϲ� [lo, mi), [mi, hi) ����������
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {

    T* A = _elem + lo; //�ϲ��������A[0, hi - lo) = _elem[lo, hi)
    int lb = mi - lo; T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi)
    for ( Rank i = 0; i < lb; B[i] = A[i++] ); //����ǰ������
    int lc = hi - mi; T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi)
    for ( Rank i = 0, j = 0, k = 0; j < lb; ) { //��B[j]��C[k]�е�С������Aĩβ
        if ( ( k < lc ) &&                ( C[k] <  B[j] )   ) A[i++] = C[k++];
        if (               ( lc <= k ) || ( B[j] <= C[k] )   ) A[i++] = B[j++];
    }
    delete [] B; //�ͷ���ʱ�ռ�B
}

// �鲢���� [lo, hi)
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if ( hi - lo < 2 ) return;
    Rank mi = (hi + lo) >> 1;
    mergeSort(lo, mi); mergeSort(mi, hi);
    merge(lo, mi, hi);
}

// ��㹹���㷨 [lo, hi]
template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
    swap( _elem[lo], _elem[ rand() % (hi - lo + 1) + lo ] );    // ���� rand() % (hi - lo + 1)  ==> [0, hi-lo]
    T pivot = _elem[lo]; Rank mi = lo;
    for (Rank i = lo + 1; i <= hi; ++i) {
        if ( _elem[i] < pivot )
            swap(_elem[++mi], _elem[i]);
    }
    swap( _elem[lo], _elem[mi] );
    return mi;
}


// ���������㷨  [lo, hi)
template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    if ( hi - lo < 2 ) return;
    Rank mi = partition(lo, hi - 1);
    quickSort(lo, mi); quickSort(mi + 1, hi);
}

// �������Ժ�����ȫ�ѽ��⣩
//void heapSort(Rank lo, Rank hi);


// �ж������Ƿ�������
template<typename T>
int Vector<T>::disordered() const {
    int n = 0 ;
    for (int i = 1; i < _size; ++i)
        if (_elem[i-1] > _elem[i])
            n++;
    return n;
}

// ��������������� [lo, hi)
template<typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
    while (lo <= --hi)
        if ( e == _elem[hi] )
            return hi;
    return hi - 1;
}


// ���������������
template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
    Rank mi;
    while ( 1 < hi - lo ) {
        mi = (lo + hi) >> 1;
        (e < _elem[mi]) ? (hi = mi) : (lo = mi + 1);
    }
    return (_elem[lo] == e) ? lo : -1;
}

// �����±������������������������ʽ���ø�Ԫ��
template<typename T>
T & Vector<T>::operator[](Rank r) const {
    return _elem[r];
}

// ���ظ�ֵ���������Ա�ֱ�ӿ�¡����
template<typename T>
Vector<T> & Vector<T>::operator=(Vector<T> const & V) {
    _elem = new T[ V._size >> 1 ]; _size = 0;
    for (int i = 0; i < V._size; _elem[_size++] = V._elem[i++]);
    return *this;
}

// ɾ����Ϊr��Ԫ��
template<typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

// ɾ����������[lo, hi)֮�ڵ�Ԫ��
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    int oldSize = _size;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return oldSize - _size;
}

// ����Ԫ��
template<typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
    expand();
    for (int i = _size; i > r; _elem[i] = _elem[--i]);
    _elem[r] = e;
    _size++;
    return r;
}

// ��[lo, hi)����
template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand() % 4) {
        case 0:
            bubbleSort(lo, hi);
            break;
        case 1:
            selectionSort(lo, hi);
            break;
        case 3:
//            mergeSort(lo, hi);    // todo �쳣��
//            break;
        default:
            quickSort(lo, hi);
            break;
    }
}

// ��[lo, hi)����
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    while (lo < hi) {
        swap( _elem[ rand() % (hi - lo) + lo ], _elem[--hi]);   // [lo, hi-1], [hi-1]
    }
}

// ����ȥ��
template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    for (int i = 1; i < _size; ++i)
        if ( find(_elem[i], 0, i) > -1 )
            remove(i);
    return oldSize - _size;
}

// ����ȥ��
template<typename T>
int Vector<T>::uniquify() {
    int oldSize = _size;
    Rank i = 0;
    for (Rank j = 1; j < _size; j++)
        if (_elem[i] != _elem[j])
            swap( _elem[++i], _elem[j] );
    _size = ++i;
    shrink();
    return  oldSize - _size;
}

//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
template<typename T>
void Vector<T>::traverse(void (* )(T &visit)) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

//������ʹ�ú������󣬿�ȫ�����޸ģ�
template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}
