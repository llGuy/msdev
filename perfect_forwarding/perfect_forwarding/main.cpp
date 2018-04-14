#include <utility>
#include <vector>

struct Foo
{
	Foo(void) = default;
	Foo(const Foo& f)
	{

	}
	Foo(Foo&& f)
	{

	}
	Foo(int i, bool b, float f)
		: m_i(i), m_b(b), m_f(f)
	{}
	Foo(int i, bool b, float f, std::vector<int> const& v)
		: m_i(i), m_b(b), m_f(f), m_v(v)
	{}
	Foo(int i, bool b, float f, std::vector<int>&& v)
		: m_i(i), m_b(b), m_f(f), m_v(std::move(v))
	{}

	int m_i;
	bool m_b;
	float m_f;
	std::vector<int> m_v;
};

struct Bar
{
	// variadic templates
	template<typename ..._Args>
	void AddFoo(_Args&&... a)			// forwarding reference
	{
		v.emplace_back(_STD forward<_Args>(a)...);
	}
private:
	std::vector<Foo> v;
};

void Foobar(Foo&& f)
{
	Foo f1(f);
}

int main(void)
{
	Bar b;
	std::vector<int> v = {1, 2, 3};
	//Foo f(1, true, 2.f);
	b.AddFoo(1, true, 2.0f, std::move(v));		//copy construct

	Foo f;
	Foobar(Foo());
}