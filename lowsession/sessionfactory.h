/************************************************************************/
/* 
����ά�����ӵĶ���������һ��session�յ�������Ϣ�����´����µ�session���ɵ�session���ٹ���
������Ҫ�ж�contentsession�Ƿ��ܹ��յ�����������������ղ���Ҳ�ж����ߡ�

*/
/************************************************************************/
#ifndef SESSIONFACTORY
#define SESSIONFACTORY

#include "connectmanager.h"
#include "listenermanager.h"
#include "session.h"
#include "applicationsession.h"

class CSessionFactory : public CHandler, public CConnectCallback
{
  public:
	CSessionFactory(CSelectReactor *selectreactor);

	void OnTimer(int event);

	int HandleEvent(int event, DWORD dwParam, void *pParam);

	void OnConnected(int code);

	void OnDisConnected(int code);

	void SetConnectLoc(string connectLoc);
	void SetListenLoc(string listenLoc);
	void Start();

	virtual CSession *CreateSession(CChannel *channel);

  private:
	CConnectManager *m_connectManager;
	CListenerManager *m_listenManager;
	CSelectReactor *m_selectReactor;
};

#endif