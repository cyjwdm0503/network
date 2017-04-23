#include "Log.h"
#include <cerrno>
#include <cstring>
#ifdef WIN32
#include "afxsock.h"
#endif
using namespace std;

#include <cstdio>
#include <ctime>


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
	cout<<"GetLastError:"<<GetLastError()<<endl;
    #else
    cout<<"GetLastError:"<<re<<"\t"<<errno<<"\t"<<strerror(errno)<<endl;
    #endif // WINDOWS

}

void CLog::PrintLog( char* info )
{
	time_t now;
	time(&now);
	char timeBuffer[100];
	strftime(timeBuffer, 100,"%b %d %H:%M:%S",localtime(&now));
	printf("%s %s %s %d[%d]: %s %s\n", timeBuffer,info);
}
