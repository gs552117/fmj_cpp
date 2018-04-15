#pragma once

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class HMQueue : public vector < T >
{
public:
    void push(T t)
    {
        this->push_back(t);
    }

    void pop()
    {
        this->erase(this->begin());
    }

    //����һ��Ԫ�� 
    void add(T t)
    {
        this->push(t);
    }

    //�Ƴ������ʶ���ͷ����Ԫ��    �������Ϊ�գ��򷵻�null
    T poll()
    {
        if (this->size() <= 0)
        {
            return NULL;
        }

        T t = this->front();
        this->pop();

        return t;
    }
    //���ض���ͷ����Ԫ��             �������Ϊ�գ��򷵻�null
    T peek()
    {
        if (this->size() <= 0)
        {
            return NULL;
        }

        T t = this->front();

        return t;
    }

    void removeLast()
    {
        T a = this->back();
        delete a;
        this->pop_back();
    }
};