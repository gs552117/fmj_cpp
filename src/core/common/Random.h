#ifndef _Random_H_
#define _Random_H_

class Random
{
public:
    Random();
    Random(long seed);
    ~Random();

    //����һ�������intֵ
    //����ֵ [0, val)
    int nextInt(int val);

    //����һ�������boolֵ
    //����ֵ true false
    bool nextbool();
private:
    void init();

public:
    static bool bInit;

};

#endif