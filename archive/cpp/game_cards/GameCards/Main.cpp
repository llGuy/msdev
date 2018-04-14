#include "TypingEffect.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

int main() {
	Player Player1;
	Player Player2;
	string tutorial = "This is a strategy game where one player uses an attack then it alternates to the opponent who uses an attack, so on and so forth. Make sure to use the available attacks wisely.\n\nTo use kick, type 'kick', this will deal approximately between 15 to 20 damage. \n\nTo use punch, type 'punch', this will deal approximately 10 to 15 damage.\n\nTo use the snap, type 'snap', this will deal approximately 10 to 15 damage and let you use a second attack in a row but snap can only be used 3 times.\n\nTo use the frying pan, type 'pan', this will deal approximately 30 to 40 damage and will let you play a second time in a row. This can only be used once.\n\nBoth players will get tired and will deal less damage, therefore type 'rest' to restore energy.\n\nTo restore some health, type 'revive' and this will restore 20 health. This only has 3 uses.\n\n";
	string attack;
	char PAKTC;					//PAK = Press any key to continue
	int decision;
	int coinDecision;
	int flipcoin = rand() % 2;
	string coinReveal = " has won the coin flip\n\n";
	int turn;
	TypingEffect::effect("Welcome to StratCards! This is a 2-player game.\n\n");
	TypingEffect::effect("Player 1, please enter your name: ");
	cin >> Player1.name;
	TypingEffect::effect("Player 2, please enter your name: ");
	cin >> Player2.name;
	cout << endl << endl;
	TypingEffect::effect("Press 1 for a quick tutorial or any other number to skip it: ");
	cin >> decision;
	cout << endl;
	if (decision == 1)
	{
		TypingEffect::effect(tutorial);
		TypingEffect::effect("Press any key to continue: ");
		cin >> PAKTC;
		cout << endl;
	}
	TypingEffect::effect(Player1.name);
	TypingEffect::effect(", heads or tails? Press 1 for heads or 0 for tails: ");
	cin >> coinDecision;
	if (coinDecision == flipcoin)
	{
		turn = 1;
		TypingEffect::effect("\n\n");
		TypingEffect::effect(Player1.name);
		TypingEffect::effect(coinReveal);
	}else{
		turn = 0;
		TypingEffect::effect("\n\n");
		TypingEffect::effect(Player2.name);
		TypingEffect::effect(coinReveal);
	}
	TypingEffect::effect("\n\nBattle starts in:\n");
	TypingEffect::countDown("54321");
	cout << endl;
	bool battle = true;
	while (battle)
	{
		if (turn == 1)
		{
			if (Player2.HP <= 0)
			{
				TypingEffect::effect(Player1.name);
				TypingEffect::effect(" has won the game!\n\n");
				battle = false;
			}
			TypingEffect::effect(Player1.name);
			cout << " (" << Player1.HP << "HP)";
			cout << ": ";
			cin >> attack;
			cout << "\n";
			if (attack == "punch")
			{
				Player2.punch(Player2.HP);
				TypingEffect::effect(Player2.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player2.HP << "\n\n";
				if (Player2.tiredness > 4)
				{
					turn = 1;
				}
				else {
					turn = 0;
				}
			}
			if (attack == "kick")
			{
				Player2.kick(Player2.HP);
				TypingEffect::effect(Player2.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player2.HP << "\n\n";
				if (Player2.tiredness > 4)
				{
					turn = 1;
				}
				else {
					turn = 0;
				}
			}
			if (attack == "pan")
			{
				Player2.PAN(Player2.HP);
				TypingEffect::effect(Player2.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player2.HP << "\n\n";
			}
			if (attack == "snap")
			{
				Player2.snap(Player2.HP);
				TypingEffect::effect(Player2.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player2.HP << "\n\n"; 
			}
			if (attack == "revive")
			{
				Player1.revive(Player1.HP);
				TypingEffect::effect(Player1.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player1.HP << "\n\n";
				turn = 0;
			}
			if (attack == "rest")
			{
				Player1.rest();
				if (Player2.tiredness <= 4)
				{
					turn = 1;
				}
				else {
					turn = 0;
				}
			}
			if (Player2.tiredness > 4)
			{
				TypingEffect::effect(Player2.name);
				TypingEffect::effect(" is tired and will deal less damage.\n\n");
				turn = 0;
			}
		}
		if (turn == 0)
		{
			if (Player1.HP <= 0)
			{
				TypingEffect::effect(Player2.name);
				TypingEffect::effect(" has won the game!\n\n");
				battle = false;
			}
			TypingEffect::effect(Player2.name);
			cout << " (" << Player2.HP << "HP)";
			cout << ": ";
			cin >> attack;
			cout << endl;
			if (attack == "punch")
			{
				Player1.punch(Player1.HP);
				TypingEffect::effect(Player1.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player1.HP << "\n\n";
				turn = 1;
			}
			if (attack == "kick")
			{
				Player1.kick(Player1.HP);
				TypingEffect::effect(Player1.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player1.HP << "\n\n";
				if (Player2.tiredness > 4)
				{
					turn = 0;
				}
				else {
					turn = 1;
				}
			}
			if (attack == "pan")
			{
				Player1.PAN(Player1.HP);
				TypingEffect::effect(Player1.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player1.HP << "\n\n";
			}
			if (attack == "snap")
			{
				Player1.snap(Player1.HP);
				TypingEffect::effect(Player1.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player1.HP << "\n\n";
			}
			if (attack == "revive")
			{
				Player2.revive(Player2.HP);
				TypingEffect::effect(Player2.name);
				TypingEffect::effect("' s HP is at ");
				cout << Player2.HP << "\n\n";

				turn = 1;
			}
			if (attack == "rest")
			{
				Player2.rest();
				if (Player1.tiredness <= 4)
				{
					turn = 0;
				}
				else {
					turn = 1;
				}
			}
			if (Player1.tiredness > 4)
			{
				TypingEffect::effect(Player2.name);
				TypingEffect::effect(" is tired and will deal less damage.\n\n");
				turn = 1;
			}
		}
	};
}