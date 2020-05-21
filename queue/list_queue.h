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
    void enqueue(T const &e) { this->insertAsLast(e); } //��ӣ�β������
    T dequeue() { return this->remove(this->first()); } //���ӣ��ײ�ɾ��
    T &front() { return this->first()->data; } //����
};