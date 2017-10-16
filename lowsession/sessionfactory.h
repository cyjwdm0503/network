/************************************************************************/

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

	virtual CSession *CreateClientSession(CChannel *channel);
	virtual CSession *CreateServerSession(CChannel *channel);
	
  private:
	CConnectManager *m_connectManager;
	CListenerManager *m_listenManager;
	CSelectReactor *m_selectReactor;
};

#endif