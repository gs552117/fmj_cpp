#include "Random.h"

#include <iostream>  
#include <stdlib.h> 
#include <time.h> 

Random::Random()
{
    init();
}

Random::Random(long seed)
{

}


Random::~Random()
{
}

void Random::init()
{
    if (false == bInit)
    {
        //��ʼ����������ӣ�ֻ�ڳ����״�ʹ��Random����ʱ��ִ��һ��
        srand((unsigned int)time(NULL));
        bInit = true;
    }
}

int Random::nextInt(int val)
{
    return (rand() % val);
}

bool Random::nextbool()
{
    if (rand() % 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Random::bInit = false;
