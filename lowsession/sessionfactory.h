/************************************************************************/
/* 
����ά�����ӵĶ���������һ��session�յ�������Ϣ�����´����µ�session���ɵ�session���ٹ���
������Ҫ�ж�contentsession�Ƿ��ܹ��յ�����������������ղ���Ҳ�ж����ߡ�

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