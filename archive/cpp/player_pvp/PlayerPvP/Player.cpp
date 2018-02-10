#include "Player.h"

Player::Player()
{
};

Player::~Player()
{
};

int Player::PAN(int input)
{
	this->hp = input;
	int PANNED = this->hp - 50;
	this->hp = PANNED;
	panuse = panuse + 1;
	return PANNED;
}
int Player::snapFunc(int input)
{
	this->hp = input;
	int snapped = this->hp - 5;
	hp = snapped;
	snapuse = snapuse + 1;
	return snapped;
}
int Player::kickFunc(int input)
{
	this->hp = input;
	int kicked = this->hp - 20;
	hp = kicked;
	return hp;
}
int Player::punchFunc(int input)
{
	this->hp = input;
	int punched = this->hp - 15;
	hp = punched;
	return hp;
}
int Player::revive(int input)
{
	this->hp = input;
	int revivedHP = this->hp + 20;
	hp = revivedHP;
	reviveuse = reviveuse + 1;
	return hp;
}