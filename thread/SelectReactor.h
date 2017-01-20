#ifndef SELECTREACTOR_H
#define SELECTREACTOR_H

#include "Dispatcher.h"
#include <list>
class CSelectReactor:public CDispatcher
{
public:
	CSelectReactor();
	~CSelectReactor();
	virtual void SyncRun();
	void  AddHandler( CHandler* handler );

	void  RemoveHandler( CHandler* handler );


private:
	std::list<CHandler*> m_IOlist;

};
#endif