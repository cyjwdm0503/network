#ifndef SELECTREACTOR_H
#define SELECTREACTOR_H

#include "Dispatcher.h"
#include <set>
#include "socks.h"

class CSelectReactor:public CDispatcher
{
public:
	CSelectReactor();
	virtual ~CSelectReactor();

	virtual void SyncRun();
	virtual void PrepareIds( fd_set& readset,fd_set& writeset,int& maxfd);
	virtual void RunHandler( fd_set& readset,fd_set& writeset,int& maxfd);
private:


};



#endif
