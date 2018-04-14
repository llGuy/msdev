#include <iostream>

using namespace std;

const int SIZE = 20;

int main()
{
	char column[SIZE][SIZE];
	bool process=true;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			column[i][j] = '.';
		}
	}
	while(process)
	{

		for(int i=19; i>=0; i--)
		{
			for (int j = 0; j < SIZE; j++) {
				cout << column[j][i] << " ";
			}
			cout << "\n";
		}
		int x;
		int y;
		cin>>x;
		cin>>y;
		column[y-1][x-1]='x';
	}
}