#include <iostream>
#include <string>

using namespace std;

int main()
{
	for (int i = 1; i < 101; i++)
	{
		if (i % 3 == 0)
		{
			cout << "Fizz";
			if (i % 15 == 0) {
				cout << "Buzz" << endl;
			}
			else {
				cout << endl;
			}
		}
		else if (i % 5 == 0) {
			cout << "Buzz" << endl;
		}
		else {
			cout << i << endl;
		}
	}
}