#ifndef PROTOCOL_CHANNELSESSION_H
#define PROTOCOL_CHANNELSESSION_H
#include "session.h"
class CChannelSession : public CSession, public CSessionCallback
{
  public:
	CChannelSession(CDispatcher *selecter, CChannel *pChannel, int MaxPackageSize);
	virtual ~CChannelSession();

	void GetIds(int *readid, int *writeid);

	void HandleInput();

	void HandleOutput();

	virtual void OnDisconnected(int ErrorCode);

	virtual int HandleEvent(int event, DWORD dwParam, void *pParam);
};

#endif