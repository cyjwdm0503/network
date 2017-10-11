#ifndef APPLICATIONPACKAGE_H 
#define APPLICATIONPACKAGE_H

#include "Package.h"
#include "fieldset.h"

const unsigned int APPLICATIONPACKAGE_MAXLENGTH = 3096;
/**Ӧ�ò㱨��ͷ�ṹ
*/
struct	CApplicationPackageHeader
{
	unsigned char	Type;				/**< �����ͣ�'P'������'R'����'O'Ӧ�� */
	unsigned char	Chain;				/**< ���ĵ�������־ */
	unsigned char	PubSession;		    /**< �����Ự��,ÿ�θ����Ự��С�ڴ˻Ự�ŵ����ݽ��ᶪ�� */
	unsigned char	FrontID;			/**< ����ǰ�õı�ʶ */
	unsigned short	ContentLength;		/**< ����ͷ֮�⣬��field���Ⱥ� */
	unsigned short	CommPhaseNo;		/**< ͨѶ�׶����,ÿ�θ�����ţ�SequenceNo����1���¿�ʼ */
	unsigned short	SubjectID;			/**< ���� */
	unsigned short    FrontSubjectID;	    /**< ǰ���������*/
	unsigned int 	Tid;				/**< ���ĵ�id	*/
	unsigned int 	SequenceNo;			/**< ���ĵ���� */
	unsigned int 	RequestID;			/**< ����ID*/
	unsigned int 	SessionID;			/**< ����������ǰ�õĻỰID*/
	unsigned int    FrontSeqNo;		    /**< ��ǰ�������е����*/
	unsigned int    CompSeqNo;
	unsigned int	ActiveID;
	/**����Ա������������0
	*/
	CApplicationPackageHeader();
 

	/**������������ݷ���pStream�����ı��ֽ���
	*@param pStream �����ı��ֽ�������ݵĻ�����
	*/
	  void ToStream(char *pStream);

	/**��pStream�����ݷ��뱾���󣬲��ı��ֽ���
	*@param pStream �����ı��ֽ���ǰ���ݵĻ�����
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