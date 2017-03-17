#include "cachelist.h"
CCacheList::CCacheList()
{

}

CCacheList::~CCacheList()
{
}

void* CCacheList::get_data( int& length )
{

}

void* CCacheList::push_back( void* data, int length )
{
	if(m_nodeList.empty())
	{//插入一个新的node
		CacheNode node;
		node.append((char*)data,length);
		m_nodeList.push_back(node);
	}
	else if((m_nodeSize - m_nodeList.back().size()) >= length)
	{
	
	}
}

int CCacheList::pop_front( int maxlength )
{

}

bool CCacheList::is_empty()
{

}

void CCacheList::clear()
{

}
