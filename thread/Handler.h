#ifndef HANDLER_H
#define HANDLER_H

class CDispatcher;
class CHandler
{
public:
	CHandler();
	~CHandler();
	virtual void GetIds(int* readid,int* writeid){};
	virtual void HandleInput(){};
	virtual void HandleOupt(){};
private:
	CDispatcher* m_dispatcher;
};


#endif