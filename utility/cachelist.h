/************************************************************************/
/* 
目前用于channelprotocol 发送tcp包的缓存管理的list
*/
/************************************************************************/
#ifndef CACHELIST_H
#define CACHELIST_H

#include <list>
#include <string>
#include <cstring>
const int MAXNODELENGTH = 25;

class CacheNode
{
public:

	CacheNode(int maxsize);
	~CacheNode();
	/************************************************************************/
	/* push  对应的内容。返回起始地址                                            */
	/************************************************************************/
	char* push(void* data,int len);

	/************************************************************************/
	/* 返回对应长度的内容，返回实际的长度与指针位置                              */
	/************************************************************************/
	void* getdata(int& length);

	/************************************************************************/
	/* 弹出对应长度的内容，在getdata后调用                                      */
	/************************************************************************/
	int pop(int length);
	//剩下可以放数据的长度
	int avablesize();
	//剩下未pop的数据长度
	int size();

private:


	//
	void clear();
public:
	/************************************************************************/
	/* 在尝试push前调用。                                                                     */
	/************************************************************************/
	bool isdeleted();
private:
	char* m_buf;
	int m_maxSize;
	char* m_cur;
	int m_length;
	bool m_deleteAll;
};

class CCacheList
{
public:
	CCacheList();
	~CCacheList();
	
	void* get_data(int& length);
	void* push_back(void* data, int length);
	int pop_front(int maxlength);
	int is_empty();
private:
	 
	std::list<CacheNode*> m_nodeList;
	int m_nodeSize;

};


#endif
