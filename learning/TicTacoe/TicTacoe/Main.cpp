#include <iostream>
#include <string>
#include <Windows.h>
#include "Typing.h"
#include "Player.h"
using namespace std;

int main()
{
	int x;
	char board[9]={ '.','.','.','.','.','.','.','.','.' };
	Player Player1;
	Player Player2;
	Typing::effect("Welcome to Tic Tac Toe!\n\n");
	Typing::effect("Player 1, enter your name: ");
	cin >> Player1.name;
	Typing::effect("Player 2, enter your name: ");
	cin>> Player2.name;
	cout<<"\n\n";
	int flipcoin=rand()%2;
	int turn=0;
	if(flipcoin==0)
	{
		turn=0;
		Typing::effect(Player1.name);
		Typing::effect(" will start.\n\n");
	}
	else {
		turn=1;
		Typing::effect(Player2.name);
		Typing::effect(" will start.\n\n");

	}
	Typing::effect("0 1 2\n3 4 5\n6 7 8\n\n");
	bool game=true;
	while(game)
	{
		for(int i=0; i<9; i++)
		{
			cout<<board[i]<<" ";
			if(i==2)
			{
				cout<<endl;
			}
			if(i==5)
			{
				cout<<endl;
			}
			if(i==8)
			{
				cout<<endl;
			}
		}
		cout<<endl;
		string sorry="sorry, you can't play here\n";
		if(turn==1) {
			Typing::effect(Player2.name);
			Typing::effect("\n");
			cin>>x;
			if(board[x]!='.')
			{
				Typing::effect(sorry);
				turn=1;
			}
			else
			{
				board[x]='x';
				turn=0;
			}
			if(turn==0) {
				Typing::effect(Player1.name);
				Typing::effect("\n");
				cin>>x;
				if(board[x]=='x'||board[x]=='o')
				{
					Typing::effect(sorry);
					turn=0;
				}
				else
				{
					board[x]='o';
					turn=1;
				}
			}
		}
	}
}