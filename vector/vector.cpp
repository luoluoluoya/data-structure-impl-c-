//
// Created by 张锐 on 2020/5/18.
//

#pragma once
#include "../share/tool.h"

// 复制数组区间A[lo, hi)
template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    _elem = new T[ (_capacity = (hi - lo) >> 1) ]; _size = 0;
    for (Rank i = lo; i < hi; _elem[_size++] = A[i++]);
}

// 扩容
// 此处未基于填充因子进行扩容判断, 扩容策略也只是依据简单的翻倍策略
template<typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return ;
    T *oldElem = _elem; _elem = new T[ (_capacity <<= 1) ];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}


// 以 1/4 作为压缩的临界条件， 每次压缩占用空间减半
template<typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1 || _capacity < _size << 2) return; // 1/4占用率
    T *oldElem = _elem; _elem = new T[ (_capacity >>= 1) ];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete [] oldElem;
}

// 一次冒泡（扫描交换）[lo, hi)
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


// 起泡排序算法
template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (lo < hi)
        if ( bubble(lo, hi--) ) break;
}

// 选取最大元素 [lo, hi]
template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
    T max = lo;
    while (++lo <= hi)
        if ( _elem[lo] >= _elem[max] )   // 选择最大元素； 多个元素命中时保证返回的是最考后的元素
            max = lo;
    return max;
}

// 选择排序算法 [lo, hi)
template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
    while (lo < hi--)
        swap( _elem[ max(lo, hi) ], _elem[hi] );
}

// 归并算法, 合并 [lo, mi), [mi, hi) 有序子向量
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {

    T* A = _elem + lo; //合并后的向量A[0, hi - lo) = _elem[lo, hi)
    int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) = _elem[lo, mi)
    for ( Rank i = 0; i < lb; B[i] = A[i++] ); //复制前子向量
    int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)
    for ( Rank i = 0, j = 0, k = 0; j < lb; ) { //将B[j]和C[k]中的小者续至A末尾
        if ( ( k < lc ) &&                ( C[k] <  B[j] )   ) A[i++] = C[k++];
        if (               ( lc <= k ) || ( B[j] <= C[k] )   ) A[i++] = B[j++];
    }
    delete [] B; //释放临时空间B
}

// 归并排序 [lo, hi)
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if ( hi - lo < 2 ) return;
    Rank mi = (hi + lo) >> 1;
    mergeSort(lo, mi); mergeSort(mi, hi);
    merge(lo, mi, hi);
}

// 轴点构造算法 [lo, hi]
template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
    swap( _elem[lo], _elem[ rand() % (hi - lo + 1) + lo ] );    // 置乱 rand() % (hi - lo + 1)  ==> [0, hi-lo]
    T pivot = _elem[lo]; Rank mi = lo;
    for (Rank i = lo + 1; i <= hi; ++i) {
        if ( _elem[i] < pivot )
            swap(_elem[++mi], _elem[i]);
    }
    swap( _elem[lo], _elem[mi] );
    return mi;
}


// 快速排序算法  [lo, hi)
template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    if ( hi - lo < 2 ) return;
    Rank mi = partition(lo, hi - 1);
    quickSort(lo, mi); quickSort(mi + 1, hi);
}

// 堆排序（稍后结合完全堆讲解）
//void heapSort(Rank lo, Rank hi);


// 判断向量是否已排序
template<typename T>
int Vector<T>::disordered() const {
    int n = 0 ;
    for (int i = 1; i < _size; ++i)
        if (_elem[i-1] > _elem[i])
            n++;
    return n;
}

// 无序向量整体查找 [lo, hi)
template<typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
    while (lo <= --hi)
        if ( e == _elem[hi] )
            return hi;
    return hi - 1;
}


// 有序向量区间查找
template<typename T>
Rank Vector<T>::search(T const &e, Rank lo, Rank hi) const {
    Rank mi;
    while ( 1 < hi - lo ) {
        mi = (lo + hi) >> 1;
        (e < _elem[mi]) ? (hi = mi) : (lo = mi + 1);
    }
    return (_elem[lo] == e) ? lo : -1;
}

// 重载下标操作符，可以类似于数组形式引用各元素
template<typename T>
T & Vector<T>::operator[](Rank r) const {
    return _elem[r];
}

// 重载赋值操作符，以便直接克隆向量
template<typename T>
Vector<T> & Vector<T>::operator=(Vector<T> const & V) {
    _elem = new T[ V._size >> 1 ]; _size = 0;
    for (int i = 0; i < V._size; _elem[_size++] = V._elem[i++]);
    return *this;
}

// 删除秩为r的元素
template<typename T>
T Vector<T>::remove(Rank r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

// 删除秩在区间[lo, hi)之内的元素
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    int oldSize = _size;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return oldSize - _size;
}

// 插入元素
template<typename T>
Rank Vector<T>::insert(Rank r, T const &e) {
    expand();
    for (int i = _size; i > r; _elem[i] = _elem[--i]);
    _elem[r] = e;
    _size++;
    return r;
}

// 对[lo, hi)排序
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
//            mergeSort(lo, hi);    // todo 异常？
//            break;
        default:
            quickSort(lo, hi);
            break;
    }
}

// 对[lo, hi)置乱
template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    while (lo < hi) {
        swap( _elem[ rand() % (hi - lo) + lo ], _elem[--hi]);   // [lo, hi-1], [hi-1]
    }
}

// 无序去重
template<typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    for (int i = 1; i < _size; ++i)
        if ( find(_elem[i], 0, i) > -1 )
            remove(i);
    return oldSize - _size;
}

// 有序去重
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

//遍历（使用函数指针，只读或局部性修改）
template<typename T>
void Vector<T>::traverse(void (* )(T &visit)) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}

//遍历（使用函数对象，可全局性修改）
template<typename T>
template<typename VST>
void Vector<T>::traverse(VST &visit) {
    for (int i = 0; i < _size; ++i) {
        visit(_elem[i]);
    }
}
