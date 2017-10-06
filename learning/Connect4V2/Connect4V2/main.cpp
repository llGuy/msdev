#include <iostream>
#include <string>
#include "person.h"
#include <Windows.h>

using namespace std;

int main()
{
	person person1;
	person person2;
	cin>>person1.name;
	cin>>person2.name;
	char column[7][6]={ { '.','.','.','.','.','.' },{ '.','.','.','.','.','.' },{ '.','.','.','.','.','.' },{ '.','.','.','.','.','.' },{ '.','.','.','.','.','.' },{ '.','.','.','.','.','.' },{ '.','.','.','.','.','.' } };

	int turn=rand()%2;
	int x;
	int address=0;
	bool game=true;
	while(game)
	{
		for(int i=0; i<6; i++)
		{
			cout<<column[0][i]<<" "<<column[1][i]<<" "<<column[2][i]<<" "<<column[3][i]<<" "<<column[4][i]<<" "<<column[5][i]<<" "<<column[6][i]<<" "<<endl;;
		}
		if(turn==0)
		{
			cout<<person1.name;
		}
		if(turn==1)
		{
			cout<<person2.name;
		}
		cin>>x;
		bool p=true;
		while(p)
		{
			p=false;
			if(column[x-1][0]!='.')
			{
				cout<<"try again\n\n";
				break;
			}
			if(column[x-1][address+1]!='.'||address==5)
			{
				if(turn==0)
				{
					column[x-1][address]='x';
					turn=1;
				}
				else {
					column[x-1][address]='o';
					turn=0;
				}
				break;
			}
			if(column[x-1][address+1]=='.') {
				address=address+1;
				p=true;
			}
		}
	}
}