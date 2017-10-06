#pragma once
#include <iostream>
using namespace std;

class board
{
public:
	board();
	~board();
	const int defaultXCoordinate=7;
	const int defaultYCoordinate=6;
	int otherYCoordinate;
	int otherXCoordinate;
	
	int counterOfTheSameCoin=1;
	bool placingProcess=true;
	bool switchTurns=true;
	bool didSomeoneWin=false;
	bool foundIfPlayerWon;
	int yCoordinate=0;
	int xCoordinate=0;
	char _board[7][6];
	bool checkIfPlayerWon();
	void gameInitiate();
	void defineBoard();
	void drawBoard();
	bool dropCoin(int xCoordinate);
	void playGame();
	void ifTheNextSpotIsTheSame(int dx,int dy);
};

