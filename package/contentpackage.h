/************************************************************************/
/*数据保证层的package,下层应为channelpackage与对应的协议
利用下层收到的数据字符，取出对应的contentpackage。并取出对应的上层应用数据包
/**该package主要是用来保证链路能够正确连接。并返回完整的应用数据包给上层。
/************************************************************************/

#ifndef CONTENTPACKAGE_H
#define CONTENTPACKAGE_H
#include "Package.h"
#include <cstring>

#define  MAX_CONTENT_LEN 127
#define  MAX_CONTENT_PACKAGE_LEN 4096
#define CONTENTTagNone				0x00

//用于对应CContentPackage的数据包长度。以及对应的上层协议
struct CContentHeadType
{
	unsigned int Type;			/**< 标示上层协议的协议ID */	
	unsigned int ExtensionLen;	/**< 扩展报文长度 */
	unsigned int Length;		/**< 包体长度 */

	inline void Init();
	inline void ToStream(char *pStream);
	inline void FromStream(char *pStream);
};


/**用于标记本层的报文内容。收到该层报文，先判定是不是本层内容。然后再向上层推送数据
*/
struct CContentExtHeadType
{
	unsigned int Tag;		/**< 状态标示　*/
	unsigned int TagLen;	/**< 扩展包的长度 */
	char Data[MAX_CONTENT_LEN];	/**< 扩展包包体 */
	inline void Init();
};


const unsigned int CONTENTHEADLENGTH = sizeof(CContentHeadType);
const unsigned int CONTENTEXTHEADLENGTH = sizeof(CContentExtHeadType);



class CContentPackage:public CPackage
{
public:
	CContentPackage();
	~CContentPackage();

	virtual void Clear();

	virtual int GetActiveID();

	virtual int ValidPackage();

	virtual int MakePackage();

	CContentHeadType *GetContentHeader();
	/**获得包体的长度，包括XTP报头
	* @return 包体的长度，包括XTP报头
	*/
	int GetBodyLength();

	/**获得扩展报头的长度
	* @return 扩展报头的长度
	*/
	unsigned int GetExtensionLen();

	/**获得扩展报头的标示
	* @return 扩展报头的标示
	*/
	unsigned int GetExtTag();

	/**获得扩展报头内容的长度
	* @return 扩展报头内容的长度
	*/
	unsigned int GetExtTagLen();

	/**获得扩展报头的内容
	*@return 扩展报头的内容
	*/
	char* GetExtData();

	/**设置扩展报头内容
	*@param Tag 扩展报头的标示
	*@param TagLen 扩展报头内容的长度
	*@param pData 扩展报头的内容
	*/
	void SetExtHeader(unsigned int Tag, unsigned int TagLen, char *pData );

private:
	CContentHeadType m_contenthead;
	CContentExtHeadType m_contentexthead;
};

void CContentHeadType::Init()
{
	memset(this,0,sizeof(CContentHeadType));
}

void CContentHeadType::ToStream( char *pStream )
{
	memcpy(pStream,this,sizeof(CContentHeadType));
}

void CContentHeadType::FromStream( char *pStream )
{
	memcpy(this,pStream,sizeof(CContentHeadType));
}


void CContentExtHeadType::Init()
{
	memset(this,0,sizeof(CContentExtHeadType));
}



#endif