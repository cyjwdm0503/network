/**
SOCK对应的头文件
**/
#ifndef SOCK_H
#define SOCK_H

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
#include <ws2tcpip.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#pragma comment(lib, "Ws2_32.lib")

	/*
	用于解决发送UDP报文到不可达的UDP服务器时会返回-1的错误错误代码10054
	*/
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)


typedef int socklen_t;

#else

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "sys/time.h"
#include "sys/types.h"
#include "unistd.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include <cerrno>
#include <sys/ioctl.h>
#endif

#define TCP

//注意以下对应BIG_ENDIAN的宏定义。
//在VMware虚拟机上BIG_ENDIAN被宏定义。网络字节序是BIG_ENDIAN
//测试发现系统是确是LITTLE_ENDIAN。难道是虚拟机的原因
//为了保证统一性,因此附加定义_BIG_ENDIAN_
#define NetToHostShort(value) 	\
	{\
	u_short s_value = ntohs((u_short)value);\
	memcpy(&value,&s_value,sizeof(u_short));\
	}

#define NetToHostLong(value) \
	{\
		u_long l_value  = ntohl((u_long)value);\
		memcpy(&value,&l_value,sizeof(u_long));\
	}

#define HostToNetShort(value) 	\
	{\
		u_short s_value  = htons((u_short)value);\
		memcpy(&value,&s_value,sizeof(u_short));\
	}

#define HostToNetLong(value)\
	{\
		u_long l_value  = htonl((u_long)value);\
		memcpy(&value,&l_value,sizeof(u_long));\
	}

#define HostToNetDouble(value) 	\
	{\
	char d_value_8[8]; \
	memcpy( d_value_8,(char*)&value,8);\
	ChangeEndianCopy8((char*)&value,d_value_8);\
	}


#define NetToHostDouble(value) 	\
	{\
	char d_value_8[8]; \
	memcpy(d_value_8,(char*)&value,8);\
	ChangeEndianCopy8((char*)&value,d_value_8);\
	}



static void ChangeEndianCopy2(char *pTarget, char *pSource)
{
#ifndef _BIG_ENDIAN_
	pTarget[1] = pSource[0];
	pTarget[0] = pSource[1];
#endif
}

static void ChangeEndianCopy4(char *pTarget, char *pSource)
{
#ifndef _BIG_ENDIAN_
	pTarget[3] = pSource[0];
	pTarget[2] = pSource[1];
	pTarget[1] = pSource[2];
	pTarget[0] = pSource[3];
#endif // !BIG_ENDIAN
}

static void ChangeEndianCopy8(char *pTarget, char *pSource)
{
#ifndef _BIG_ENDIAN_
	pTarget[7] = pSource[0];
	pTarget[6] = pSource[1];
	pTarget[5] = pSource[2];
	pTarget[4] = pSource[3];
	pTarget[3] = pSource[4];
	pTarget[2] = pSource[5];
	pTarget[1] = pSource[6];
	pTarget[0] = pSource[7];
#endif // !BIG_ENDIAN
}


//用于判定socket读取错误
#ifdef WIN32
#define GET_LAST_ERROR() WSAGetLastError() 
#define EWOULDBLOCK WSAEWOULDBLOCK
#else
#define GET_LAST_ERROR() errno
#endif // WIN32

#endif
