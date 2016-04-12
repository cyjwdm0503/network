#include "Log.h"
#include <cerrno>
#include <cstring>
using namespace std;

#define DEBUGOUT(errno)  \
cout<<__FILE__<<"\t"<<__LINE__ \
CLog::GetInstance().Printerrno(errno)

CLog* CLog::g_Log = NULL;

CLog* CLog::GetInstance()
{
  if(g_Log == NULL)
  {
    return g_Log = new CLog();
  }
  else
    return g_Log;
}

CLog::CLog()
{
  ;
}
CLog:: ~CLog()
{
  delete g_Log;
  g_Log = NULL;
}

void CLog::Printerrno(int error)
{
  cout<<error<<"\t"<<strerror(error)<<endl;
}
