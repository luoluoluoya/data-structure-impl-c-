//
// Created by ���� on 2020/5/19.
//

#pragma once

#include "../list/list.h"

/**
 * ����ģ���ࣨ�̳�Listԭ�нӿڣ�
 *
 * @tparam T
 */
template<typename T>
class Queue : public List<T> {
public:
    void enqueue(T const &e) { List<T>::insertAsLast(e); } //��ӣ�β������
    T dequeue() { return List<T>::remove(List<T>::first()); } //���ӣ��ײ�ɾ��
    T &front() { return List<T>::first()->data; } //����
};