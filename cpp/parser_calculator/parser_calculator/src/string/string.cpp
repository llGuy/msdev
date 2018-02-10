#include "string.h"

String::String(char* s)
{
	m_size = CPTRSize(s);
	if (m_size < 16)
	{
		SSOI(s, m_size);
		m_size *= -1;
	}
	else HAllocationI(s, m_size);
}
String::String(const char* s)
{
	m_size = CPTRSize(s);
	if (m_size < 16)
	{
		SSOI(s, m_size);
		m_size *= -1;
	}
	else HAllocationI(s, m_size);
}
String::String(const size_type size)
{
}
String::~String(void)
{
	if (!SSO()) delete[] m_l.m_ptr;
}
void String::HAllocationI(const char* s, size_type size)
{
	m_l.m_cap = size * 2;
	m_l.m_ptr = new char[m_l.m_cap];
	memcpy(m_l.m_ptr, s, sizeof(char) * (size + 1));
}
void String::SSOI(const char* s, size_type size)
{
	memcpy(m_sso, s, sizeof(char) * (size + 1));
}
const String::size_type String::CPTRSize(const char* s) const
{
	size_type i = 0;
	while (s[i] != '\0') ++i;
	return i;
}
const String::size_type String::Size(void) const
{
	return m_size < 0 ? m_size * -1 : m_size;
}
const bool String::SSO(void) const
{
	return m_size < 0;
}
const char* String::C_Str(void)
{
	return SSO() ? m_sso : &m_l.m_ptr[0];
}
String String::operator+(const String& s)
{
	size_type newSize = s.Size() + this->Size();
	char* newCStr = new char[newSize];
	String& bound = *this;
	for (size_type i = 0; i < newSize; ++i)
	{
		if (i == bound.Size()) bound = s;
		newCStr[i] = bound.C_Str()[i];
	}
	return String(newCStr);
}
String& String::operator+=(const String& s)
{
	size_type newSize = s.Size() + this->Size();
	if (newSize < 16)
	{
		// SSO
		for (size_type i = this->Size(); i < newSize; ++i)
		{
			m_sso[i] = s.C_Str()[i - this->Size()];
		}
	}
	else
	{
		// newChar
	}
}