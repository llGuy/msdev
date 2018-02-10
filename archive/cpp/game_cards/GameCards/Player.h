#pragma once
#include <string>

using namespace std;

class Player
{
public:
	Player();
	~Player();
	string name;
	int HP = 100;
	int CP = 0;
	int DAMAGED = 0;
	int REVIVED = 0;
	int reviveuse = 1;
	int tiredness = 1;
	int PANuse = 1;
	int snapuse = 1;

	int snap(int HPInput);			//Defined
	int punch(int HPInput);			//Defined
	int PAN(int HPInput);			//Defined
	int kick(int HPInput);			//Defined
	int revive(int HPInput);		//Defined
	void rest();			//Defined
};

