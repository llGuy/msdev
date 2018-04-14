#include "string.h"

namespace ltd
{
	string::string(const char* s)
	{
		m_size = CPTRSize(s);
		if (m_size < 16)
		{
			SSOI(s, m_size);
			m_size *= -1;
		}
		else HAllocationI(s, m_size);
	}
	string::string(const size_type size)
	{
	}
	string::~string(void)
	{
		if (!SSO()) delete[] m_l.m_ptr;
	}
	void string::HAllocationI(const char* s, size_type size)
	{
		m_l.m_cap = size * 2;
		m_l.m_ptr = new char[m_l.m_cap];
		memcpy(m_l.m_ptr, s, sizeof(char) * (size + 1));
	}
	void string::SSOI(const char* s, size_type size)
	{
		memcpy(m_sso, s, sizeof(char) * (size + 1));
	}
	const string::size_type string::CPTRSize(const char* s) const
	{
		size_type i = 0;
		while (s[i] != '\0') ++i;
		return i;
	}
	const string::size_type string::size(void) const
	{
		return m_size < 0 ? m_size * -1 : m_size;
	}
	const bool string::SSO(void) const
	{
		return m_size < 0;
	}
	const char* string::c_str(void)
	{
		return SSO() ? m_sso : &m_l.m_ptr[0];
	}
}