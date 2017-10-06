#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
{
}

int Player::kick(int HPInput)
{
	if (tiredness <= 4)
	{
		CP = rand() % 15 + 6;
		tiredness = tiredness + 1;
	}
	else {
		cout << "Your legs are too tired to kick.\n\n";
	}
	DAMAGED = HP - CP;
	HP = DAMAGED;
	CP = 0;
	return HP;
}

int Player::punch(int HPInput)
{
	if (tiredness <= 4)
	{
		CP = rand() % 10 + 6;
	}
	else {
		CP = rand() % 2 + 4;
	}
	DAMAGED = HP - CP;
	HP = DAMAGED;
	tiredness = tiredness + 1;
	CP = 0;
	return HP;
}
int Player::snap(int HPInput)
{
	if (snapuse <= 3)
	{
		if (tiredness < 4)
		{
			CP = rand() % 10 + 6;
			snapuse = snapuse + 1;
		}
		else if (tiredness >= 4)
		{
			CP = rand() % 1 + 6;
			snapuse = snapuse + 1;
		}
		tiredness = tiredness + 1;
	}
	else {
		cout << "You cannot use this anymore.\n\n";
	}
	DAMAGED = HP - CP;
	HP = DAMAGED;
	CP = 0;
	return HP;
}

int Player::PAN(int HPInput)
{
	if (PANuse == 1)
	{
		if (tiredness < 4)
		{
			CP = rand() % 30 + 11;
			tiredness = tiredness + 1;
		}
		else {
			CP = rand() % 20 + 11;
			tiredness = tiredness + 1;
		}
		PANuse = PANuse + 1;
	}
	else {
		cout << "You can use this again.\n\n";
	}
	DAMAGED = HP - CP;
	HP = DAMAGED;
	CP = 0;
	return HP;
}

void Player::rest()
{
	if (tiredness > 4)
	{
		tiredness = tiredness - 3;
	}
	else {
		cout << "You are not tired enough to rest.\n\n";
	}
}

int Player::revive(int HPInput)
{
	if (reviveuse <= 3)
	{
		REVIVED = HP + 20;
		HP = REVIVED;
	}
	else {
		cout << "You cannot revive yourself.\n\n";
	}
	return HP;
}

Player::~Player()
{
}
