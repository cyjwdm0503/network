/**
SOCK对应的头文件
**/

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>


#pragma comment(lib, "Ws2_32.lib")

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
