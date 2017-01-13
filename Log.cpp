#include "Log.h"
#include <cerrno>
#include <cstring>
#ifdef WIN32
#include "afxsock.h"
#endif
using namespace std;



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

void CLog::Printerrno(int re)
{
    #ifdef WIN32
	cout<<GetLastError();
    #else
    cout<<re<<"\t"<<strerror(errno)<<endl;
    #endif // WINDOWS

}
