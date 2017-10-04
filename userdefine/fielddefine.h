//用代码生成工具生成对应的代码
#ifndef FIELDDEFINE_H
#define FIELDDEFINE_H

#include "fielddescribe.h"

class SendField
{
public:
	CIntType m_int;
	CWordType m_short;
	CStringType<10> m_string;
	CCharType m_char;
	CDoubleType<10,3> m_double;
	FIELD_DESC(
	TYPE_DESC(m_int);
	TYPE_DESC(m_short);
	TYPE_DESC(m_string);
	TYPE_DESC(m_char);
	TYPE_DESC(m_double);
	);
};
const short SendField_ID = 01;

class RecvField
{
public:
	CIntType m_int;
	CWordType m_short;
	CStringType<10> m_string;
	CCharType m_char;
	CDoubleType<10,3> m_double;
	FIELD_DESC(
	TYPE_DESC(m_int);
	TYPE_DESC(m_short);
	TYPE_DESC(m_string);
	TYPE_DESC(m_char);
	TYPE_DESC(m_double);
	);
};
const short RecvField_ID = 02;

#endif
