#ifndef HANDLER_H
#define HANDLER_H

class CSelectReactor;
class CHandler
{
public:
	CHandler(CSelectReactor* selecter):m_dispatcher(selecter){};
	virtual ~CHandler(){m_dispatcher =  NULL;};
	virtual void GetIds(int* readid,int* writeid){};
	virtual void HandleInput(){};
	virtual void HandleOupt(){};
private:
	CSelectReactor* m_dispatcher;
};


#endif