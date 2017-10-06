#include <iostream>
#include <string>

using namespace std;

int main()
{
	bool process = true;
	while (process)
	{
		int arraySize;
		int a;
		cin >> a;
		cin >> arraySize;
		unsigned __int64 newA = 1;
		for (int i = 1; i <= arraySize; i++)
		{
			newA = a * newA;
		}
		cout << newA << endl;
	}
}