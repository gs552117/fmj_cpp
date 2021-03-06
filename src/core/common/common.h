#ifndef _common_h_
#define _common_h_

#include <iostream> 

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#ifdef WIN32

#pragma warning (disable:4819)

#define snprintf _snprintf
int gettimeofday(struct timeval *tp, void *tzp);
#endif

void SleepMilliSecond(long lMilliseconds);

std::string int_to_string(int n);

bool IsFileExist(const char *name);

#endif
