#include <iostream>
#include <string>
#pragma once

using namespace std;

class Player {
public:
	Player();
	~Player();
	string name;
	int panuse = 0;
	int snapuse = 0;
	int reviveuse = 0;
	int hp = 100;
	int punch = 5;
	int punchFunc(int input);
	int kick = 10;
	int kickFunc(int input);
	int snapArm = 20;
	int snapFunc(int input);
	int numberOfsnapArm = 0;
	int pan = 50;
	int PAN(int input);
	int numberOfPan = 0;
	int revive(int input);
};