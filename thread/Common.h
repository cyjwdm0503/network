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

typedef const int EVENT_MSG;

EVENT_MSG	EVENT_TRY_CONNECT = 0;
EVENT_MSG	EVENT_RET_CONNECT = 1;
EVENT_MSG	EVENT_TRY_ACCEPT = 2;
EVENT_MSG	EVENT_RET_ACCEPT = 3;
EVENT_MSG	EVENT_ERR_DISCONNECT = 4 ;
EVENT_MSG	EVENT_ERR_OUTTIME = 5;


#endif
