/**
SOCK对应的头文件
**/
#ifndef SOCK_H
#define SOCK_H

#ifdef WIN32

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
#endif

#define TCP

#endif
