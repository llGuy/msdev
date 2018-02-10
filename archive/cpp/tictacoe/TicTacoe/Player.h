#pragma once
#include <string>

using namespace std;
class Player
{
public:
	Player();
	~Player();
	string name;
	int occupied = 0;
	void place(int coord);
};
class Coords
{
public:
	Coords();
	~Coords();
};

