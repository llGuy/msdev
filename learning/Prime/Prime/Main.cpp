#include <iostream>
#include <string>

using namespace std;

void prime(unsigned __int64 number);

int main()
{
	bool process = true;
	while (process)
	{
		unsigned __int64 number;
		int searchCount;
		cout << "enter a number\n";
		cin >> number;
		cout << "enter a search number\n";
		cin >> searchCount;
		
		for (unsigned __int64 i = number; i <= number + searchCount; i++)
		{
			cout << i << ": ";
			prime(i);
		}
	}
}

void prime(unsigned __int64 number)
{
		unsigned __int64 num;
		unsigned __int64 newInt = 1;

		for (int i = 2; i <= (number / 2); i++)
		{
			num = number % i;
			newInt = num * 2;
			if (newInt == 0)
			{
				cout << "It is not a prime because it is divisible by " << i << endl;
				break;
			}
		}
		if (newInt != 0)
		{
			cout << "It is a prime\n";
		}
}