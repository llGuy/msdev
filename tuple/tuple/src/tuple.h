#pragma once
#include <stdint.h>
#include <iostream>
template<typename _First, typename... _Rest>
class Tuple
	: public Tuple<_Rest...>
{
public:
	using Type = _First;
	Tuple(void) = default;

	Tuple(_First&& val, _Rest&&... rest)
		: m_value(val)
	{
	}
	inline
	_First& Value(void)
	{
		return m_value;
	}
private:
	_First m_value;
};

/*template<typename _First>
class Tuple
{
public:
	using Type = _First;
	Tuple(void) = default;

	Tuple(_First&& val)
		: m_value(val)
	{
	}
	inline
		_First& Value(void)
	{
		return m_value;
	}
private:
	_First m_value;
};
/*
template<uint32_t _Index, typename _First, typename... _Rest>
struct GetImp
{
	static auto Value(const Tuple<_First, _Rest...>& tuple) -> decltype(GetImp<_Index - 1, _Rest...>::Value(tuple))
	{
		return GetImp<_Index - 1, _Rest...>::Value(tuple);
	}
};
template<uint32_t _Index, typename _First, typename... _Rest>
struct GetImp<0, _First, _Rest...>
{
	static _First Value(const Tuple<_First, _Rest...>& tuple)
	{
		return tuple.Value();
	}
};

template<uint32_t _Index, typename _First, typename... _Rest>
auto Get(const Tuple<_First, _Rest...>& tuple) -> decltype(GetImp<_Index - 1, _Rest...>::Value(tuple))
{
	return GetImp<_Index, _First, _Rest...>::Value(tuple);
}*/

int main(void)
{
	
}