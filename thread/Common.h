#ifndef COMMON_H
#define COMMON_H

#define   WIN32_LEAN_AND_MEAN

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#include <process.h>
#else
#include "pthread.h"
#include "unistd.h"
#endif


enum EVENT_MSG
{
	EVENT_TRY_CONNECT,
	EVENT_RET_CONNECT,
	EVENT_TRY_ACCEPT,
	EVENT_RET_ACCEPT,
	EVENT_ERR_DISCONNECT,
	EVENT_ERR_OUTTIME
};


#endif
