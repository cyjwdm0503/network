#include "SelectReactor.h"
void CSelectReactor::AddHandler( CHandler* handler )
{
	CMutexGuard guard(m_mtx);
	m_IOlist.insert(handler);

}

void CSelectReactor::RemoveHandler( CHandler* handler )
{
	CMutexGuard guard(m_mtx);
	m_IOlist.erase(handler);
}

void CSelectReactor::SyncRun()
{
	
	
	int maxfd;
	fd_set  readset;
	fd_set  writeset;


	PrepareIds(readset,writeset,maxfd);
	//select
	timeval t;
	t.tv_sec = 0;
	t.tv_usec = 10;
	select(maxfd+1,&readset,&writeset,NULL,&t);
	RunHandler(readset,writeset,maxfd);

}

void CSelectReactor::PrepareIds( fd_set& readset,fd_set& writeset,int& maxfd)
{
	FD_ZERO(&readset);
	FD_ZERO(&writeset);
	maxfd = 0;
	std::set<CHandler*>::iterator it= m_IOlist.begin();
	for(; it!= m_IOlist.end(); it++)
	{
		//首先获取所有的ids 写入fd_set;从而利用fd_set 进行输入与输出
		int readfd = 0,writefd= 0;
		(*it)->GetIds(&readfd,&writefd);
		if(readfd >0)
		{
			FD_SET(readfd,&readset);
			maxfd =  max(readfd,maxfd);
		}
		if(writefd >0)
		{
			FD_SET(writefd,&writeset);
			maxfd =  max(readfd,writefd);
		}

	}

}

void CSelectReactor::RunHandler( fd_set& readset,fd_set& writeset,int& maxfd )
{
	std::set<CHandler*>::iterator it= m_IOlist.begin();
	for(; it!= m_IOlist.end(); it++)
	{
		int readfd = 0,writefd= 0;
		(*it)->GetIds(&readfd,&writefd);
		//首先获取所有的ids 写入fd_set;从而利用fd_set 进行输入与输出
		if(FD_ISSET(readfd,&readset) && readfd>0)
		{
			(*it)->HandleInput();
		}
		if(FD_ISSET(writefd,&writeset) && writefd>0)
		{
			(*it)->HandleOupt();
		}
	}
}

CSelectReactor::CSelectReactor()
{

}

CSelectReactor::~CSelectReactor()
{

}

