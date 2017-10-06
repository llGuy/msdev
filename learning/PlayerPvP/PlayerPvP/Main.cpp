#include <iostream>
#include <string>
#include <Windows.h>
#include "Player.h"

using namespace std;

int main()
{
	string welcome = "Welcome to my first game for two players!";
	int x = 0;
	while (welcome[x] != '\0')
	{
		cout << welcome[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
	Sleep(800);
	cout << endl << endl;

	Player Player1;
	Player Player2;
	
	string player1Intro = "Player 1: enter your name : ";
	x = 0;
	while (player1Intro[x] != '\0')
	{
		cout << player1Intro[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
	cin >> Player1.name;
	
	x = 0;
	string player2Intro = "Player 2: enter your name : ";
	while (player2Intro[x] != '\0')
	{
		cout << player2Intro[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
	cin >> Player2.name;
	string tutChoice = "Press 1 to go through a quick tutorial on how to play or 0 to skip it.\n";
	x = 0;
	while (tutChoice[x] != '\0')
	{
		cout << tutChoice[x];
		Sleep(rand() % 25 + 25);
		x++;
	};
	char tutorialOrNot;
	cin >> tutorialOrNot;
	cout << "\n\n";
	if (tutorialOrNot == '1')
	{
		x = 0;
		string tutorial = "To kick the opponent, type 'kick' and this will deal 20 damage.\n\nTo punch the opponent, type 'punch' and this will deal 15 damage.\n\nTo snap the opponent's arm, type 'snap' and this will deal 5 damage. This will let you attack a second time in a row.\nThis attack only has three uses.\n\nTo PAN someone, type 'pan' and this will deal 50 damage and will let you attack a second time in a row.\nThis attack only has one use.\n\nTo revive yourself, type 'revive' to restore 20 hp.\nThis only have 2 uses.\n\n";
		while (tutorial[x] != '\0')
		{
			cout << tutorial[x];
			Sleep(rand() % 25 + 25);
			x++;
		};
		cout << "\n\nPress any key to continue: ";
		char pl;
		cin >> pl;
		cout << "\n\n";
		Sleep(2000);
	}
	int headsTails;
	int coinFlip = rand() % 2;
	cout << Player1.name <<", heads or tails? Press 1 for heads or 0 for tails.\n The winner will be revealed when the battle begins.";
	cin >> headsTails;

	cout << "\n\nOk battle starts in \n5\n";
	Sleep(1000);
	cout << "4\n";
	Sleep(1000);
	cout << "3\n";
	Sleep(1000);
	cout << "2\n";
	Sleep(1000);
	cout << "1\n";
	Sleep(1000);

	bool battle = true;

	int turn = 1;
	if (headsTails == coinFlip)
	{
		cout << Player1.name;
		turn = 1;
	}
	if (headsTails != coinFlip)
	{
		cout << Player2.name;
		turn = 0;
	}
	cout << " has won the coin flip.\nWhat is your first move?\n";

	while (battle)
	{
		if (turn == 1)
		{
			cout << "\n<" << Player1.name << "("  << Player1.hp << " HP)" <<">  ";
			string attack;
			cin >> attack;
			if (attack == "kick")
			{
				Player2.kickFunc(Player2.hp);
				cout << "\nDAMMMMMMMMMMM! You reduced " << Player2.name << "' s HP to " << Player2.hp << "\n\n";
				turn = 0;
			}
			if (attack == "punch")
			{
				Player2.punchFunc(Player2.hp);
				cout << "\nOUCH! " << Player2.name << "'s HP is down to " << Player2.hp << "\n\n";
				turn = 0;
			}
			if (attack == "snap")
			{ 
				if (Player2.snapuse <= 1)
				{
					Player2.snapFunc(Player2.hp);
					cout << "\nOMG! " << Player2.name << "' s HP is reduced to " << Player2.hp << "\n\n";
				}
				else
				{
					cout << "\nYou have already used this attack and must choose another one.\n";
				}
				turn = 1;
			}
			if (attack == "PAN")
			{
				if (Player2.panuse == 0)
				{
					Player2.PAN(Player2.hp);
					cout << endl << Player2.name << " GOT PANNED! You just destroyed his HP to " << Player2.hp << "\n\n";
					turn = 1;
				}
				else{
					cout << "\nYou have already used this attack and must choose another one.\n";
					turn = 1;
				}
			}
			if (attack == "revive")
			{
				if (Player1.reviveuse <= 1)
				{
					Player1.revive(Player1.hp);
					cout << endl << Player1.name << " has restored 20 HP and is now at " << Player1.hp;
					turn = 0;
				}
				else {
					cout << "\nYou cannot revive yourself anymore.\n";
					turn = 1;
				}
			}

		}
		if (turn == 0)
		{
			cout << "\n<" << Player2.name << "(" << Player2.hp << " HP)" << ">  ";
			string attack;
			cin >> attack;
			if (attack == "kick")
			{
				Player1.kickFunc(Player1.hp);
				cout << "\nDAMMMMMMMMMMM! You reduced " << Player1.name << "' s HP to " << Player1.hp << "\n\n";
				turn = 1;
			}
			if (attack == "punch")
			{
				Player1.punchFunc(Player1.hp);
				cout << "\nOUCH! " << Player1.name << "'s HP is down to " << Player1.hp << "\n\n";
				turn = 1;
			}
			if (attack == "snap")
			{
				if (Player1.snapuse <= 2)
				{
					Player1.snapFunc(Player1.hp);
					cout << "\nOMG! " << Player1.name << "' s HP is reduced to " << Player1.hp << "\n\n";
					turn = 0;
				}
				else
				{
					cout << "\nYou have already used this attack and must choose another one.\n";
					turn = 0;
				}
			}
			if (attack == "PAN")
			{
				if (Player1.panuse == 0)
				{
					Player1.PAN(Player1.hp);
					cout << endl << Player1.name << " GOT PANNED! You just destroyed his HP to " << Player1.hp << "\n\n";
					turn = 0;
				}
				else {
					cout << "\nYou have already used this attack and must choose another one.\n";
					turn = 0;
				}
			}
			if (attack == "revive")
			{
				if (Player2.reviveuse <= 1)
				{
					Player2.revive(Player2.hp);
					cout << endl << Player2.name << " has restored 20 HP and is now at " << Player2.hp << endl;
					turn = 1;
				}
				else {
					cout << "\nYou cannot revive yourself anymore.\n";
					turn = 0;
				}
			}
		}

		if (Player1.hp <= 0)
		{
			string Player1Win = "                END				\n\n\n\n";
			string Player1Won = " has won with a remaining hp of ";
			x = 0;
			while (Player1Win[x] != '\0')
			{
				cout << Player1Win[x];
				Sleep(50);
				x++;
			};
			x = 0; 
			cout << Player1.name;
			while (Player1Won[x] != '\0')
			{
				cout << Player1Won[x];
				Sleep(50);
				x++;
			};
			cout << Player2.hp;
			battle = false;
		}
		if (Player2.hp <= 0)
		{
			string Player2Win = "                END				\n\n\n\n";
			string Player2Won = " has won with a remaining hp of ";
			x = 0;
			while (Player2Win[x] != '\0')
			{
				cout << Player2Win[x];
				Sleep(50);
				x++;
			};
			x = 0;
			cout << Player1.name;
			while (Player2Won[x] != '\0')
			{
				cout << Player2Won[x];
				Sleep(50);
				x++;
			};
			cout << Player1.hp;
			battle = false;
		}
	};
}