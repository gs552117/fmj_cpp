#include "common.h"
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <string>

#ifdef WIN32
int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = (long)clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

void SleepMilliSecond(long lMilliseconds)
{
    Sleep(lMilliseconds);
}

#else
void SleepMilliSecond(long lMilliseconds)
{
    usleep(lMilliseconds * 1000);
}
#endif


std::string int_to_string(int n)
{
    std::ostringstream stream;
    stream << n;
    return stream.str();
}

bool IsFileExist(const char *name)
{
    bool bRet = false;
    std::ifstream in;
    in.open(name, std::ios::in | std::ios::_Nocreate);
    if (in.is_open())
    {
        bRet = true;
        in.close();
    }

    return bRet;
}
