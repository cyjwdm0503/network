#ifndef COMMON_H
#define COMMON_H

#define   WIN32_LEAN_AND_MEAN

#ifdef WIN32
//#ifndef TEST
//#define TEST
//
//#include "crtdbg.h"
//
//inline void EnableMemLeakCheck()
//{
//	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
//}
//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif
//#endif
#include <WinSock2.h>
#include <windows.h>
#include <process.h>
#else
#include "pthread.h"
#include "unistd.h"
#include <sys/time.h>
#endif

//如果写const int 会在类和结构体中报错
typedef int EVENT_MSG;

const EVENT_MSG	EVENT_NULL = 0;
const EVENT_MSG	EVENT_RET_CONNECT = 1;
const EVENT_MSG	EVENT_TRY_ACCEPT = 2;
const EVENT_MSG	EVENT_RET_ACCEPT = 3;
const EVENT_MSG	EVENT_ERR_DISCONNECT = 4 ;
const EVENT_MSG	EVENT_ERR_OUTTIME = 5;

const EVENT_MSG EVENT_CHANNEL_READ_ERRO = 6;
const EVENT_MSG EVENT_CHANNEL_WRITE_ERRO = 7;
const EVENT_MSG EVENT_CONTENT_READ_ERRO = 8;
const EVENT_MSG EVENT_CONTENT_READTIMEOUT = 9;
const EVENT_MSG EVENT_CONTENT_WRITETIMEOUT = 10;


const EVENT_MSG	EVENT_STOP = 9999;
#endif
