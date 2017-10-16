/************************************************************************/
/* 
锟斤拷锟斤拷维锟斤拷锟斤拷锟接的讹拷锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷session锟秸碉拷锟斤拷锟斤拷锟斤拷息锟斤拷锟斤拷锟铰达拷锟斤拷锟铰碉拷session锟斤拷锟缴碉拷session锟斤拷锟劫癸拷锟斤拷
锟斤拷锟斤拷锟斤拷要锟叫讹拷contentsession锟角凤拷锟杰癸拷锟秸碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷詹锟斤拷锟揭诧拷卸锟斤拷锟斤拷摺锟?

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