//
// Created by 47302 on 2020/5/23.
//

#pragma once

/**
 * ���ȼ�����PQģ����
 *
 * @tparam T
 */
template<typename T>
class PQ {
public:
    //���ձȽ���ȷ�������ȼ�����������
    virtual void insert(T const e) = 0;

    //ȡ�����ȼ���ߵĴ���
    virtual T getMax() = 0;

    //ɾ�����ȼ���ߵĴ���
    virtual T delMax() = 0;
};
