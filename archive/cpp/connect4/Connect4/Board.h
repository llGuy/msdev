#pragma once

class Board
{
	static const char STATE_EMPTY = '.';
	static const char STATE_YELLOW_PLAYER = 'x';
	static const char STATE_RED_PLAYER = 'o';
    
	int _columns;
	int _rows;
    // Board with 0,0 at top, left
	char * _boardState;
    
    int size();
    int indexInBoard(int row, int column);
    int countSameState(int row, int col, int incRow, int incCol);
    
public:
	Board(int rows, int cols);
	~Board();

	// Reset Board State to empty
	void resetState();

    bool play(char player);
    
	int insertAtTopOf(int whichColumn, char player);
    bool checkWinningMove(int row, int col);
    
    char stateFor(int row, int column);
    bool setStateFor(int row, int column, char state);
    void print();
    
    char playerYellow();
    char playerRed();
    
    void play();
};

