#include "Log.h"
#include <cerrno>
#include <cstring>
#ifdef WIN
//#include "afxsock.h"
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
#ifdef WIN
	PrintLog("GetLastError:%d\n",WSAGetLastError());
#else
	PrintLog("GetLastError:%d\tdesc:%s\n",re,strerror(errno));
	//cout<<"GetLastError:"<<re<<"\t"<<errno<<"\t"<<strerror(errno)<<endl;
#endif // WINDOWS

}

void CLog::PrintLog(const char* info,...)
{
	m_mtx.Lock();
	time_t now;
	time(&now);
	char timeBuffer[100];
	strftime(timeBuffer, 100,"%b %d %H:%M:%S\t",localtime(&now));
    fprintf(stdout,"%s", timeBuffer);
	va_list v;
	va_start(v,info);
	vfprintf(stdout, info,v);
	va_end(v);
	m_mtx.UnLock();
}
