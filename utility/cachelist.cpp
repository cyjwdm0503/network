#include "stdafx.h"
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

	//�����һ����գ���ɾ��
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
	//�����һ����գ���ɾ��
	while(m_nodeList.size()>0 && m_nodeList.front()->isdeleted())
	{
		m_nodeList.erase(m_nodeList.begin());
	}

	if(m_nodeList.empty() || m_nodeList.back()->avablesize() < length)
	{//����һ���µ�node
		CacheNode *node = new CacheNode(length);
		ptr = node->push((char*)data,length);
		m_nodeList.push_back(node);
	}
	//������ǰ��node������
	else if(m_nodeList.back()->avablesize() >= length)
	{
		ptr = m_nodeList.back()->push(data,length);
	}
	
	return ptr;
}

int CCacheList::pop_front( int maxlength )
{
	//�����һ����գ���ɾ��
	while(m_nodeList.size()>0 && m_nodeList.front()->isdeleted())
	{
		m_nodeList.erase(m_nodeList.begin());
	}
	return m_nodeList.front()->pop(maxlength);
}

int CCacheList::is_empty()
{
	std::list<CacheNode*>::iterator it = m_nodeList.begin();
	for(; it != m_nodeList.end(); )
	{
		if((*it)->isdeleted())
		{
			it = m_nodeList.erase(it);
			continue;
		}
		it++;
	}
	return m_nodeList.size() ==0 ? true: false;
}

bool CacheNode::isdeleted()
{
	return m_deleteAll;
}

void CacheNode::clear()
{
	if(size()== 0 && (m_cur-m_buf) == m_length && avablesize() == m_maxSize)
	{	
		delete m_buf;
		m_buf = NULL;
		m_cur = NULL;
		m_deleteAll = true;
	}
}

int CacheNode::size()
{
	return m_length-(m_cur-m_buf);
}

int CacheNode::avablesize()
{
	return m_maxSize-size();
}

int CacheNode::pop( int length )
{
	int ret = 0;
	if(size() < length)
	{
		ret = size();
	}
	else
	{
		ret = length;			
	}
	m_cur += ret;
	//��pop���Ե���clear
	clear();
	return ret;
}

void* CacheNode::getdata( int& length )
{
	if(length > size())
		length = size();
	char* ptr =  m_cur;
	return ptr;
}

char* CacheNode::push( void* data,int len )
{
	char* tmp = m_buf+m_length;
	memcpy(tmp,data,len);
	m_length +=len;
	return tmp;
}

CacheNode::~CacheNode()
{
	if(m_buf != NULL)
	{
		delete m_buf;
		m_buf = NULL;
	}
	m_cur =  NULL;
}

CacheNode::CacheNode( int maxsize ) :m_maxSize(maxsize)
{
	m_buf = new char[m_maxSize];
	m_cur =  m_buf;
	m_length = 0;
	m_deleteAll =  false;
}
