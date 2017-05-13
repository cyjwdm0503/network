#include "fileddescribe.h"

class XXXX
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
const short XXXX_ID = 01;
MAKGE_FIELD_DESC(XXXX,XXXX_ID,"XXXXCOMMENT")

class XXXX2
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
const short XXXX2_ID = 01;
MAKGE_FIELD_DESC(XXXX2,XXXX_ID,"XXXX2COMMENT")