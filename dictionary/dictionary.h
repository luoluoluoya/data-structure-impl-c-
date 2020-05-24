//
// Created by 47302 on 2020/5/24.
//

#pragma once

template<typename K, typename V>
class Dictionary {
public:
    virtual int size() const = 0;       //当前词条总数
    virtual bool put ( K, V ) = 0;      //插入词条（禁止雷同词条时可能失败）
    virtual V* get ( K k ) = 0;         //读取词条
    virtual bool remove ( K k ) = 0;    //删除词条
};
