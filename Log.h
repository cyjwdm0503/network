/**
打印对应的log信息

**/

#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define DEBUGOUT(errno)  \
    std::cout<<__FILE__<<"\t"<<__LINE__<<"\t";\
	if(errno != -1)\
	{\
		CLog::GetInstance()->Printerrno(errno);\
	}




class CLog
{
public:
  static CLog* g_Log;
  static CLog* GetInstance();

  CLog();
  virtual ~CLog();
  void Printerrno(int error);
};

#endif
