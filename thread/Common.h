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
#include <sys/time.h>
#endif

//���дconst int ������ͽṹ���б���
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

const EVENT_MSG EVENT_CHANNELTIME_ID = 101;
const EVENT_MSG	EVENT_STOP = 9999;
#endif
