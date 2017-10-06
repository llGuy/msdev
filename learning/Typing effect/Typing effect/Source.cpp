#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	char g;
	string message = "Console has a message for you. Press any key to view your new message.\n";
	int y = 0;
	while (message[y] != '\0')
	{
		cout << message[y];
		Sleep(rand() % 1 + 25);
			y++;
	};
	cin >> g;
	string intro = "Hello World, my name is Console and I am typing this at a random pace. I am typing a lot of stuff to test whether this is random or not.\n";
	int x = 0;
	while (intro[x] != '\0')
	{
		cout << intro[x];
		Sleep(rand() % 1 + 50);
		x++;
	};
	cout << "\n\nEnd of message\n";
}