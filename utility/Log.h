/**
打印对应的log信息

**/

#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include "Mutex.h"

#define DEBUGOUT(errno)  \
	{\
	 CLog::GetInstance()->PrintLog("%s_%s_%d\n",__FILE__,__FUNCTION__,__LINE__);\
	 CLog::GetInstance()->Printerrno(errno);\
	}




class CLog
{
protected:
  static CLog* g_Log;
  CLog();
  virtual ~CLog();
  CMutex m_mtx;
public:
  static CLog* GetInstance();
  void Printerrno(int error);
  void PrintLog(const char* info,...);
};

#endif
