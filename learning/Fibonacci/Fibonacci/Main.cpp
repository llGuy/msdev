#include <iostream>

using namespace std;

int main()
{
	int number = 1;

	for (int *i = 0; i < 50; i++)
	{
		number = number + *i[-1];
		cout << number << endl;
	}
}