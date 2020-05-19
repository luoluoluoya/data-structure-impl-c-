//
// Created by ���� on 2020/5/19.
//

#pragma once

//����������ڵ���
#include "binnode.h"

/**
 * ������ģ����
 *
 * @tparam T
 */
template<typename T>
class BinTree {

private:
    int _size;  // ��ģ
    BinNodePosi(T)_root; // ���ڵ�

protected:
    virtual int updateHeight(BinNodePosi(T)x); //���½ڵ�x�ĸ߶�
    void updateHeightAbove(BinNodePosi(T)x); //���½ڵ�x�������ȵĸ߶�

public:
    BinTree() : _size(0), _root(NULL) {} //���캯��
    ~BinTree() { if (0 < _size) remove(_root); } //��������

    int size() const { return _size; }              //��ģ
    bool empty() const { return !_root; }           //�п�
    BinNodePosi(T)root() const { return _root; }    //����

    /**��̬����*/
    BinNodePosi(T)insertAsRoot(T const &e); //������ڵ�
    BinNodePosi(T)insertAsLC(BinNodePosi(T)x, T const &e);      //e��Ϊx�����ӣ�ԭ�ޣ�����
    BinNodePosi(T)insertAsRC(BinNodePosi(T)x, T const &e);      //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
    BinNodePosi(T)attachAsLC(BinNodePosi(T)x, BinTree<T> *&L);  //L��Ϊx����������
    BinNodePosi(T)attachAsRC(BinNodePosi(T)x, BinTree<T> *&L);  //L��Ϊx����������

    int remove(BinNodePosi(T)x);            //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
    BinTree<T> *secede(BinNodePosi(T)x);    //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������

    /**�������㷨**/
    template<typename VST>void travLevel(VST &visit) { if (_root) _root->travLevel(visit); } //��α���
    template<typename VST>void travPre(VST &visit) { if (_root) _root->travPre(visit); } //�������
    template<typename VST>void travIn(VST &visit) { if (_root) _root->travIn(visit); } //�������
    template<typename VST>void travPost(VST &visit) { if (_root) _root->travPost(visit); } //�������

    //�Ƚ������������в��䣩
    bool operator<(BinTree<T> const &t) { return _root && t._root && lt(_root, t._root); }
    //�е���
    bool operator==(BinTree<T> const &t) { return _root && t._root && (_root == t._root); }

//    void stretchToLPath() { stretchByZag(_root); }          //����zag��ת��ת��Ϊ������
//    void stretchToRPath() { stretchByZig(_root, _size); }   //����zig��ת��ת��Ϊ������
};

#include "bintree.cpp"

