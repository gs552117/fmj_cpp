#pragma once

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class HMStack: public vector < T >
{
public:
    void push(T t)
    {
        this->push_back(t);
    }

    //�Ƴ�ջ�����󣬲���Ϊ������ֵ ���ظö��󡣿գ��򷵻�null
    T pop()
    {
        if (this->size() <= 0)
        {
            return NULL;
        }

        T t = this->back();
        this->pop_back();

        return t;
    }

    //����һ��Ԫ�� 
    void add(T t)
    {
        this->push(t);
    }


};