#include <iostream>
#include <string>

using namespace std;

int main()
{
	bool process = true;
	while (process)
	{
		int a;
		int b;
		cin >> a;
		cin >> b;
		for (int i = 2; i < a; i++)
		{
			if (a % i == 0)
			{
				if (b % i == 0)
				{
					cout << i << endl;
				}
			}

		}
	}
}