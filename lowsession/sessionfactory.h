/************************************************************************/
/* 
用于维护连接的断线重连。一个session收到短线信息后，重新创建新的session。旧的session不再管理
后期需要判定contentsession是否能够收到服务器心跳，如果收不到也判定断线。

*/
/************************************************************************/
#ifndef  SESSIONFACTORY
#define SESSIONFACTORY


#include "connectmanager.h"
#include "listenermanager.h"
class CSessionFactory:public CHandler
{
public:
	CSessionFactory(CSelectReactor* selectreactor);
	
	virtual void OnTimer( int event );

	virtual int HandleEvent( int event,DWORD dwParam,void* pParam );

private:
	CConnectManager* m_connectManager;
	CListenerManager* m_listenManager;
	CSelectReactor* m_selectReactor;


};

#endif