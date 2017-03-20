#include "cachelist.h"

CCacheList::CCacheList( )
{

}

CCacheList::~CCacheList()
{
}

void* CCacheList::get_data( int& length )
{
	void* ptr = NULL;

	//如果第一个清空，则删除
	if(m_nodeList.size()>0 && m_nodeList.front()->isdeleted())
	{
		m_nodeList.erase(m_nodeList.begin());
	}

	if(m_nodeList.size() == 0 || m_nodeList.back()->isdeleted())
	{
		length = 0;
		return NULL;
	}
	else
	{
		 ptr =  m_nodeList.front()->getdata(length);
		
		return ptr;
	}
}

void* CCacheList::push_back( void* data, int length )
{
	char* ptr =  NULL;
	//如果第一个清空，则删除
	if(m_nodeList.size()>0 && m_nodeList.front()->isdeleted())
	{
		m_nodeList.erase(m_nodeList.begin());
	}

	if(m_nodeList.empty() || m_nodeList.back()->avablesize() < length)
	{//插入一个新的node
		CacheNode *node = new CacheNode(MAXNODELENGTH);
		ptr = node->push((char*)data,length);
		m_nodeList.push_back(node);
	}
	//利用以前的node加数据
	else if(m_nodeList.back()->avablesize() >= length)
	{
		ptr = m_nodeList.back()->push(data,length);
	}
	
	return ptr;
}

int CCacheList::pop_front( int maxlength )
{
	return m_nodeList.front()->pop(maxlength);
}

int CCacheList::is_empty()
{
	std::list<CacheNode*>::iterator it = m_nodeList.begin();
	for(; it != m_nodeList.end(); it++)
	{
		if((*it)->isdeleted())
		{
			it = m_nodeList.erase(it);
		}
	}
	return m_nodeList.size() ==0 ? true: false;
}
