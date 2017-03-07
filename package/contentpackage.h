/************************************************************************/
/*���ݱ�֤���package,�²�ӦΪchannelpackage���Ӧ��Э��
�����²��յ��������ַ���ȡ����Ӧ��contentpackage����ȡ����Ӧ���ϲ�Ӧ�����ݰ�
/**��package��Ҫ��������֤��·�ܹ���ȷ���ӡ�������������Ӧ�����ݰ����ϲ㡣
/************************************************************************/

#ifndef CONTENTPACKAGE_H
#define CONTENTPACKAGE_H
#include "Package.h"
#include <cstring>

#define  MAX_CONTENT_LEN 127
#define  MAX_CONTENT_PACKAGE_LEN 4096
#define CONTENTTagNone				0x00

//���ڶ�ӦCContentPackage�����ݰ����ȡ��Լ���Ӧ���ϲ�Э��
struct CContentHeadType
{
	unsigned int Type;			/**< ��ʾ�ϲ�Э���Э��ID */	
	unsigned int ExtensionLen;	/**< ��չ���ĳ��� */
	unsigned int Length;		/**< ���峤�� */

	inline void Init();
	inline void ToStream(char *pStream);
	inline void FromStream(char *pStream);
};


/**���ڱ�Ǳ���ı������ݡ��յ��ò㱨�ģ����ж��ǲ��Ǳ������ݡ�Ȼ�������ϲ���������
*/
struct CContentExtHeadType
{
	unsigned int Tag;		/**< ״̬��ʾ��*/
	unsigned int TagLen;	/**< ��չ���ĳ��� */
	char Data[MAX_CONTENT_LEN];	/**< ��չ������ */
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
	/**��ð���ĳ��ȣ�����XTP��ͷ
	* @return ����ĳ��ȣ�����XTP��ͷ
	*/
	int GetBodyLength();

	/**�����չ��ͷ�ĳ���
	* @return ��չ��ͷ�ĳ���
	*/
	unsigned int GetExtensionLen();

	/**�����չ��ͷ�ı�ʾ
	* @return ��չ��ͷ�ı�ʾ
	*/
	unsigned int GetExtTag();

	/**�����չ��ͷ���ݵĳ���
	* @return ��չ��ͷ���ݵĳ���
	*/
	unsigned int GetExtTagLen();

	/**�����չ��ͷ������
	*@return ��չ��ͷ������
	*/
	char* GetExtData();

	/**������չ��ͷ����
	*@param Tag ��չ��ͷ�ı�ʾ
	*@param TagLen ��չ��ͷ���ݵĳ���
	*@param pData ��չ��ͷ������
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