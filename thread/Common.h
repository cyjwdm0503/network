#ifndef COMMON_H
#define COMMON_H


#ifdef WIN32
#include <windows.h>
#include <process.h>
#else
#include "pthread.h"
#include "unistd.h"
#endif

#endif
