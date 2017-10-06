#include "Board.h"
#include <iostream>
using namespace std;

Board::Board(int rows, int cols) {
	_rows = rows;
	_columns = cols;
	_boardState = new char[size()];
    resetState();
}


Board::~Board() {
	delete _boardState;
}

void Board::resetState() {
	int totalSize = _rows*_columns;
	for (int i = 0; i < totalSize; i++) {
		_boardState[i] = STATE_EMPTY;
	}
}

void Board::play(){
    bool stop = false;
    
    print();
    char player = playerYellow();
    while (stop == false) {
        if( play(player) ){
            stop = true;
        }else{
            player = player == playerYellow() ? playerRed() : playerYellow();
        }
    }
    
}

int Board::insertAtTopOf(int whichColumn, char state){
    int insertedAtRow = _rows;
    if (whichColumn < _columns) {
        int foundNonEmptyRow = _rows;
        
        for (int row = 0; row<_rows; row++) {
            if (stateFor(row, whichColumn) != STATE_EMPTY) {
                foundNonEmptyRow = row;
                break;
            }
        }
        if( foundNonEmptyRow > 0){
            insertedAtRow = foundNonEmptyRow-1;
            setStateFor(insertedAtRow, whichColumn, state);
        }
    }
    return insertedAtRow;
}

int Board::countSameState(int row, int col, int incRow, int incCol){
    int count = 0;
    char state = stateFor(row, col);

    if (state != STATE_EMPTY) {
        count = 1;
        // ForwardLoop
        for (int i=1;i<size();i++) {
            int checkRow = row + i * incRow;
            int checkCol = col + i * incCol;
            
            char thisState = stateFor(checkRow, checkCol);
            if( thisState == state){
                count++;
            }else{
                break;
            }
        }
        // BackwardLoop
        for (int i=1;i<size();i++) {
            int checkRow = row - i * incRow;
            int checkCol = col - i * incCol;
            
            char thisState = stateFor(checkRow, checkCol);
            if( thisState == state){
                count++;
            }else{
                break;
            }
        }
    }
    return count;
}

bool Board::checkWinningMove(int row, int col){
    int horizontal = countSameState(row, col, 0, 1);
    int vertical   = countSameState(row, col, 1, 0);
    if( horizontal >= 4 || vertical >= 4){
        return true;
    }else{
        return false;
    }
}

char Board::stateFor(int row, int column){
    int index = indexInBoard(row, column);
    return index < size() ? _boardState[index] : STATE_EMPTY;
}

bool Board::setStateFor(int row, int column, char state){
    bool success = false;
    int index = indexInBoard(row, column);
    if (index < size()) {
        _boardState[index] = state;
        success = true;
    }
    return success;
}

int Board::indexInBoard(int row, int column){
    return row * _columns + column;
}

int Board::size(){
    return _columns*_rows;
}
void Board::print(){
    for (int row=0; row<_rows; row++) {
        for (int col=0; col < _columns; col++) {
            cout << stateFor(row,col);
        }
        cout << endl;
    }
    cout << "0123456";
    cout << endl;
}

char Board::playerYellow(){
    return STATE_YELLOW_PLAYER;
}
char Board::playerRed(){
    return STATE_RED_PLAYER;
}


bool Board::play(char player){
    bool won = false;
    int col;
    cout << (player == STATE_RED_PLAYER ? "Red Player (o): " : "Yellow player (x): ");
    cin >> col;
    
    int playedAt = insertAtTopOf(col, player);
    while( playedAt == _rows){
        cout << "Invalid columns, try again"<<endl;
        cout << (player == STATE_RED_PLAYER ? "Red Player (o): " : "Yellow player (x): ");
        cin >> col;
        playedAt = insertAtTopOf(col, player);
    }
    print();
    cout << "Played at " << playedAt << "," << col << endl;
    if( checkWinningMove(playedAt, col)){
        cout << "You WON" << endl;
        won = true;;
    }
    return won;
}

