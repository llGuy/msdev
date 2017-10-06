#include <iostream>

using namespace std;

int main()
{
	bool process = true;
	while (process)
	{
		unsigned __int64 result = 1;
		int number;
		cin >> number;
		if (number == -1)
		{
			process = false;
		}
		for (int i = 1; i < number; i++)
		{
			result = result * i;
		}
		cout << result << endl; 
	}
}