#ifndef STRING_HEADER
#define STRING_HEADER

#include <iostream>
#include <memory>

class String
{
public:
	// if it's negative, it's sso, otherwise, it's heap
	using size_type = signed int;

	String(void) = default;
	String(char* s);
	String(const char* s);
	String(const size_type size);
	~String(void);
public:
	// getters
	const size_type Size(void) const;
	const bool SSO(void) const;
	const char* C_Str(void);

	String operator+(const String& s);
	String& operator+=(const String& s);
private:
	const size_type CPTRSize(const char* s) const;
	void HAllocationI(const char* s, size_type size);
	void SSOI(const char* s, size_type size);
private:
	//	: 24 bytes total
	size_type m_size;				// 8 bytes
	union							// union is 16 bytes
	{
		struct
		{
			char* m_ptr;		// 8 bytes
			size_type m_cap;		// 8 bytes
		} m_l;						// 16 bytes total
		char m_sso[16];				// 16 bytes
	};
};

#endif