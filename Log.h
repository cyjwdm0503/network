#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <cstdlib>
#include <cstdio>


class CLog
{
public:
  static CLog* g_Log;
  static CLog* GetInstance();

  CLog();
  ~CLog();
  void Printerrno(int errno);
};

#endif
