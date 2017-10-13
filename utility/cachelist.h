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

	CacheNode(size_t maxsize);
	~CacheNode();
	/************************************************************************/
	/* push  对应的内容。返回起始地址                                            */
	/************************************************************************/
	char* push(void* data,size_t len);

	/************************************************************************/
	/* 返回对应长度的内容，返回实际的长度与指针位置                              */
	/************************************************************************/
	void* getdata(size_t& length);

	/************************************************************************/
	/* 弹出对应长度的内容，在getdata后调用 length 需要的长度，return实际的长度                                     */
	/************************************************************************/
	size_t pop(size_t length);
	//剩下可以放数据的长度
	size_t avablesize();
	//剩下未pop的数据长度
	size_t size();

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
	size_t m_maxSize;
	char* m_cur;
	size_t m_length;
	bool m_deleteAll;
};

class CCacheList
{
public:
	CCacheList();
	~CCacheList();
	
	void* get_data(size_t& length);
	void* push_back(void* data, size_t length);
	size_t pop_front(size_t maxlength);
	int is_empty();
private:
	 
	std::list<CacheNode*> m_nodeList;
	size_t m_nodeSize;

};


#endif
