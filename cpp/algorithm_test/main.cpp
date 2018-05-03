#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <iterator>

struct thing
{
  int a, b;
};

template<typename _Ty, std::size_t _Sze>
class Array
{
public:
  struct Iterator
  {
  public:
    Iterator& operator++(int)
    {
      ++m_Value;
      return *this;
    }
    _Ty& operator*(void)
    {
      return *m_Value;
    }
  private:
    _Ty* m_Value;
  };
  
  _Ty& operator[](std::size_t sbscr)
  {
    assert(sbscr < _Sze);
    return m_Arr[sbscr];
  }
private:
  _Ty m_Arr[_Sze];
};

template<std::size_t _Sz>
void Sort(std::array<int, _Sz>& arr, std::function<bool(int, int)> comp)
{
  // base index that will keep track of item being sorted
  struct
  {
    uint32_t baseIndex;
    uint32_t index;
  } c { 1, 1 };
  for(; c.baseIndex < _Sz; ++c.baseIndex)
  {
    for(c.index = c.baseIndex; c.index > 0; --c.index)
    {
      int& ind  = arr[c.index];
      int& ind2 = arr[c.index - 1];
      if(comp(arr[c.index], arr[c.index - 1]))
      {
	std::cout << "swapping " << ind << " and " << ind2 << "\n";
	std::swap(ind, ind2);
      }
    }
  }
}

void func(int a)
{
    
}

int main(int argc, char* argv[])
{
  std::vector<int> v { 0, 2, 4, 6};

  /* testing ostream_iterator */
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

  /* testing all of */
  if(std::all_of(v.begin(), v.end(),
		 [](int n)->bool { return n % 2 == 0; }))
    {
      std::cout << "all the numbers are divisible by 2" << std::endl;
    }

  // testing for each
  std::for_each(v.begin(), v.end(), [](int& i) { ++i; });
  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

  std::cout << "\n\n" << std::endl;

  // testing count
  std::vector<int> v2 { 2, 3, 4, 5, 6, 8, 10, 8, 6 };
  int numberOfItems = std::count(v.begin(), v.end(), 3 /* target value */);
  std::cout << numberOfItems << std::endl;

  int numberOfDivisibleBy2 = std::count_if(v2.begin(), v2.end(),
					   [](int i) { return i % 2 == 0; });
  std::cout << numberOfDivisibleBy2 << std::endl;

  // testing find
  auto iter = std::find(std::begin(v2), std::end(v2), 4);
  if(iter != std::end(v2)) std::cout << "vector contains " << *iter << "\n";

  // testing find_end
  std::vector<int> subsequence { 0, 1, 2 };
  std::vector<int> sequence { -1, 0, 1, 2, 3, 4};

  std::vector<int>::iterator result = std::find_end(sequence.begin(), sequence.end(),
    subsequence.begin(), subsequence.end());
  if(result != sequence.end())
    std::cout << "subsequence found" << std::endl;
  
  // testing copy
  std::vector<int> from(10);
  // fills with increasing numbers
  //std::iota(from.begin(), from.end(), 0);
  std::vector<int> to;
  std::copy(from.begin(), from.end(), std::back_inserter(to));

  std::copy(to.begin(), to.end(), std::ostream_iterator<int>(std::cout, " "));

  std::cout << "\n";

  // sorting
  std::vector<int> values { 3, 5, 1, 4, 2 };
  std::sort(values.begin(), values.end(),
	    [](int a, int b)
	    {
	      if(a == 1)
		return false;
	      if(b == 1)
		return true;
	      return a < b;
	    });
  std::copy(values.begin(), values.end(), std::ostream_iterator<int>(std::cout, " "));

  std::array<int, 5> a { 4, 5, 2, 1, 3 };
  Sort(a, [](const int& a, const int& b) { return a > b; });

  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
}
