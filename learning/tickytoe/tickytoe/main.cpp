#include <iostream>
#include <string>
#include "typ.h"
#include "player.h"
using namespace std;
void reset();
char board[9]={ '.','.','.','.','.','.','.','.','.' };
int main()
{
	
	player player1;
	player player2;
	typ::eff("tic tac toe\n\n");
	typ::eff("Player 1 enter your name: ");
	cin>>player1.name;
	typ::eff("Player 2 enter your name: ");
	cin>>player2.name;
	typ::eff("To restart the game type -1\n\n");
	bool AMTP=true;											//Amount times played
	while(AMTP)
	{
		AMTP=false;
		int decision;
		int flip=rand()%2;
		int turn;
		if(flip==0)
		{
			typ::eff(player1.name);
			typ::eff(" starts\n\n");
			turn=0;
		}
		if(flip==1)
		{
			typ::eff(player2.name);
			typ::eff(" starts\n\n");
			turn=1;
		}
		typ::eff("1 2 3\n4 5 6\n7 8 9\n\n");
		string sorry="sorry you can't play here\n\n";
		bool game=true;
		int x=0;
		while(game)
		{

			for(int i=0; i<9; i++)
			{
				cout<<board[i]<<" ";
				if(i==2||i==5||i==8)
				{
					cout<<endl;
				}
			}
			cout<<"\n\n";
			if(turn==0)
			{
				typ::eff(player1.name);
				cout<<": ";
				cin>>x;
				if(x==-1)
				{
					reset();
					typ::eff("game has been reset\n\n");
					AMTP=true;
					break;

				}
				if(board[x-1]!='.')
				{
					typ::eff(sorry);
					turn=0;
				}
				if(board[x-1]=='.')
				{
					board[x-1]='x';
					turn=1;
					for(int i=0; i<9; i++)
					{
						cout<<board[i]<<" ";
						if(i==2||i==5||i==8)
						{
							cout<<endl;
						}
					}
					if(board[0]!='.'&& board[1]!='.' && board[2]!='.' && board[3]!='.' && board[3]!='.' && board[4]!='.' && board[5]!='.' && board[6]!='.' && board[7]!='.' && board[8]!='.')
					{
						Sleep(1000);
						typ::eff("\n\nFinished!\n\nwould you like to play again? 1 for yes or anything else for no.\n");
						cin>>decision;
						if(decision==1)
						{
							AMTP=true;
							reset();
						}
						break;
					}
				}
			}

			cout<<"\n\n";
			if(turn==1)
			{
				typ::eff(player2.name);
				cout<<": ";
				cin>>x;
				if(x==-1)
				{
					reset();
					typ::eff("game has been reset\n\n");
					AMTP=true;
					break;

				}
				if(board[x-1]!='.')
				{
					typ::eff(sorry);
					turn=1;
				}
				if(board[x-1]=='.')
				{
					board[x-1]='o';
					turn=0;
					if(board[0]!='.'&& board[1]!='.' && board[2]!='.' && board[3]!='.' && board[3]!='.' && board[4]!='.' && board[5]!='.' && board[6]!='.' && board[7]!='.' && board[8]!='.')
					{
						Sleep(1000);
						typ::eff("\n\nFinished!\n\nwould you like to play again? 1 for yes or anything else for no.\n");
						cin>>decision;
						if(decision==1)
						{
							AMTP=true;
							reset();
						}
						break;
					}
				}
			}

		}
	}
}
void reset()
{
	board[0]='.';
	board[1]='.';
	board[2]='.';
	board[3]='.';
	board[4]='.';
	board[5]='.';
	board[6]='.';
	board[7]='.';
	board[8]='.';
	board[9]='.';
}