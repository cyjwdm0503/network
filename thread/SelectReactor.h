#ifndef SELECTREACTOR_H
#define SELECTREACTOR_H

#include "Dispatcher.h"
#include <set>
class CSelectReactor:public CDispatcher
{
public:
	CSelectReactor();
	~CSelectReactor();

	virtual void SyncRun();
	void  AddHandler( CHandler* handler );
	void  RemoveHandler( CHandler* handler );
	void PrepareIds( fd_set& readset,fd_set& writeset,int& maxfd);
	void RunHandle( fd_set& readset,fd_set& writeset,int& maxfd);
private:
	std::set<CHandler*> m_IOlist;

};



#endif