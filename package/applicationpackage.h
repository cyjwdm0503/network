#ifndef APPLICATIONPACKAGE_H 
#define APPLICATIONPACKAGE_H

#include "Package.h"
#include "fieldset.h"

const unsigned int APPLICATIONPACKAGE_MAXLENGTH = 3096;
/**应用层报文头结构
*/
struct	CApplicationPackageHeader
{
	unsigned char	Type;				/**< 包类型（'P'发布，'R'请求，'O'应答） */
	unsigned char	Chain;				/**< 报文的连续标志 */
	unsigned char	PubSession;		    /**< 发布会话号,每次更换会话，小于此会话号的数据将会丢弃 */
	unsigned char	FrontID;			/**< 交易前置的标识 */
	unsigned short	ContentLength;		/**< 除报头之外，各field长度和 */
	unsigned short	CommPhaseNo;		/**< 通讯阶段序号,每次更换序号，SequenceNo都从1重新开始 */
	unsigned short	SubjectID;			/**< 主题 */
	unsigned short    FrontSubjectID;	    /**< 前置主题代码*/
	unsigned int 	Tid;				/**< 报文的id	*/
	unsigned int 	SequenceNo;			/**< 报文的序号 */
	unsigned int 	RequestID;			/**< 请求ID*/
	unsigned int 	SessionID;			/**< 请求发起者在前置的会话ID*/
	unsigned int    FrontSeqNo;		    /**< 在前置主题中的序号*/
	unsigned int    CompSeqNo;
	unsigned int	ActiveID;
	/**将成员变量的内容清0
	*/
	CApplicationPackageHeader();
 

	/**将本对象的内容放入pStream，并改变字节序
	*@param pStream 存贮改变字节序后数据的缓冲区
	*/
	  void ToStream(char *pStream);

	/**将pStream的数据放入本对象，并改变字节序
	*@param pStream 存贮改变字节序前数据的缓冲区
	*/
	  void FromStream(char *pStream);
};

const int  APPLICATIONHEADERLENGTH	= sizeof(CApplicationPackageHeader);

#ifndef SETATTR
#define  SETATTR(Name,ValueType)\
	void Set##Name(ValueType value)\
{\
	m_ApplicationHeader.##Name = (##value);\
}

#endif

#ifndef GETATTR
#define  GETATTR(Name,ValueType)\
	ValueType Get##Name()\
{\
	return m_ApplicationHeader.##Name;\
}

#endif

class CApplicationPackage:public CFieldSet
{



public:
	virtual int GetActiveID();

	virtual int ValidPackage();

	virtual int MakePackage();

	virtual bool CopyPackage(CPackage* pPackage);

	SETATTR(Type,unsigned char);
	SETATTR(Chain,unsigned char);
	SETATTR(PubSession,unsigned char);
	SETATTR(FrontID,unsigned char);
	SETATTR(ContentLength,unsigned short);
	SETATTR(CommPhaseNo,unsigned short);
	SETATTR(SubjectID,unsigned short);
	SETATTR(FrontSubjectID,unsigned short);
	SETATTR(Tid,unsigned int);
	SETATTR(SequenceNo,unsigned int);
	SETATTR(RequestID,unsigned int);
	SETATTR(SessionID,unsigned int);
	SETATTR(FrontSeqNo,unsigned int);
	SETATTR(CompSeqNo,unsigned int);
	SETATTR(ActiveID,unsigned int);

	GETATTR(Type,unsigned char);
	GETATTR(Chain,unsigned char);
	GETATTR(PubSession,unsigned char);
	GETATTR(FrontID,unsigned char);
	GETATTR(ContentLength,unsigned short);
	GETATTR(CommPhaseNo,unsigned short);
	GETATTR(SubjectID,unsigned short);
	GETATTR(FrontSubjectID,unsigned short);
	GETATTR(Tid,unsigned int);
	GETATTR(SequenceNo,unsigned int);
	GETATTR(RequestID,unsigned int);
	GETATTR(SessionID,unsigned int);
	GETATTR(FrontSeqNo,unsigned int);
	GETATTR(CompSeqNo,unsigned int);
private:
	CApplicationPackageHeader m_ApplicationHeader;


};

#endif