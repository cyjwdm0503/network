#include "fileddescribe.h"

class SendField
{
public:
	CBaseIntTpye m_int;
	CBaseShortType m_short;
	CBaseStringType m_string;
	CBaseCharType m_char;
	CBaseDoubleType m_double;
	FIELD_DESC(
		TYPE_DESC(m_int);
	TYPE_DESC(m_short);
	TYPE_DESC(m_string);
	TYPE_DESC(m_char);
	TYPE_DESC(m_double);
	);
};
const short SendField_ID = 01;
MAKGE_FIELD_DESC(SendField,SendField_ID,"发送内容")

class RecvField
{
public:
	CBaseIntTpye m_int;
	CBaseShortType m_short;
	CBaseStringType m_string;
	CBaseCharType m_char;
	CBaseDoubleType m_double;
	FIELD_DESC(
		TYPE_DESC(m_int);
	TYPE_DESC(m_short);
	TYPE_DESC(m_string);
	TYPE_DESC(m_char);
	TYPE_DESC(m_double);
	);
};
const short RecvField_ID = 02;
MAKGE_FIELD_DESC(RecvField,RecvField_ID,"接收内容")

