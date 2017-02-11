#ifndef SELECTREACTOR_H
#define SELECTREACTOR_H

#include "Dispatcher.h"
#include <set>
class CSelectReactor:public CDispatcher
{
public:
	CSelectReactor();
	virtual ~CSelectReactor();

	virtual void SyncRun();
	void PrepareIds( fd_set& readset,fd_set& writeset,int& maxfd);
	void RunHandler( fd_set& readset,fd_set& writeset,int& maxfd);
private:


};



#endif