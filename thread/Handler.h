#ifndef HANDLER_H
#define HANDLER_H

class CDispatcher;
class CHandler
{
public:
	CHandler();
	~CHandler();
	void GetIds(int* readid,int* writeid);
	void HandleInput();
	void HandleOupt();
private:
	CDispatcher* m_dispatcher;
};


#endif