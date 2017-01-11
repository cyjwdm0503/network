/**
打印对应的log信息

**/

#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>

#define DEBUGOUT(errno)  \
    std::cout<<__FILE__<<"\t"<<__LINE__;

//CLog::GetInstance()->Printerrno(errno);



class CLog
{
public:
  static CLog* g_Log;
  static CLog* GetInstance();

  CLog();
  ~CLog();
  void Printerrno(int error);
};

#endif
