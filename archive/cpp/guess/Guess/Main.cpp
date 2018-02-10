#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n = 10;
	int choice = 8;
	int choice2;

	for (int i = 1; i <= 3; i++)
	{
		int round = i;
		cin >> choice2;
		if (choice2 < 8)
		{
			cout << "Round " << i << ": You guessed " << choice2 << ", I tell you it's higher" << ". You pay " << choice2 << endl;
		}
		else if (choice2 > 8)
		{
			cout << "Round " << i << ": You guessed " << choice2 << ", I tell you it's lower" << ". You play " << choice2 << endl;
		}
		else if (choice2 == 8)
		{
			cout << "Congratulations you won!" << endl;
			i = 3;
		}
		else if (i = 3, choice2 != 8)
		{
			cout << "Game over! I chose " << choice << "You pay " << temp << endl;
		}
	}
}