#include "board.h"

board::board()
{
}
void board::defineBoard() {
	for(int iDefine=0; iDefine<6; iDefine++) {
		for(int yDefine=0; yDefine<7; yDefine++) {
			_board[yDefine][iDefine]='.';
		}
	}
}
void board::drawBoard() {
	for(int iDraw=0; iDraw<6; iDraw++) {
		for(int yDraw=0; yDraw<7; yDraw++) {
			cout<<_board[yDraw][iDraw]<<" ";
		}
		cout<<endl;
	}
    cout << "0 1 2 3 4 5 6" << endl;
}
void board::gameInitiate() {
	didSomeoneWin=false;
    bool gameBoolean = true;
	int debugCounter = 0;
    
    bool automatic = false;
	while(gameBoolean==true) {
		drawBoard();
		
        int chosen;
        if( automatic ){
            // play vertical
            chosen = switchTurns ? 1 : 2;
            // play horizontal
            //chosen = debugCounter / 2;
        }else{
            cin >> chosen;
        }
        
        debugCounter++;
        if(debugCounter == 7) {
            cout<<"I WANT TO STOP NOW!!!" << endl;
        }
        
		dropCoin(chosen);
        if (didSomeoneWin) {
            drawBoard();
            gameBoolean = false;
            cout << "WON!!!!" << endl;
        }
	}
}
bool board::dropCoin(int xCoordinate) {
	int yCoordinate=0;
	while(placingProcess) {
		if(_board[xCoordinate][0]!='.') {											//Checks if there is no more space on the y coordinate of a certain x coordinate
			cout<<"try again\n";
			break;
		}
		else if(_board[xCoordinate][yCoordinate+1]!='.'||yCoordinate==5) {			//Checks if the spot superior(in this case underneath) of the y coordinate is occupied
			if(switchTurns==true) {
				_board[xCoordinate][yCoordinate]='o';
				//return switchTurns=false;
                switchTurns=false;
                otherXCoordinate = xCoordinate;
                otherYCoordinate = yCoordinate;
                break;
			}
			else {
				_board[xCoordinate][yCoordinate]='x';
				//return switchTurns=true;
                switchTurns=true;
                otherXCoordinate = xCoordinate;
                otherYCoordinate = yCoordinate;
                break;
			}
			break;
		}else {
			yCoordinate=yCoordinate+1;
		}
	}
	checkIfPlayerWon();
	if(didSomeoneWin==true) {
		placingProcess=false;
		cout<<"There is a winner!" << endl;
	}
    return true;
}
bool board::checkIfPlayerWon() {
    
    ifTheNextSpotIsTheSame(0,1);
    ifTheNextSpotIsTheSame(1,0);
    ifTheNextSpotIsTheSame(1,1);
    ifTheNextSpotIsTheSame(1,-1);
    
    return true;
}
void board::ifTheNextSpotIsTheSame(int dx,int dy) {
    int xCoord = otherXCoordinate;
    int yCoord = otherYCoordinate;
    
    char checkValue = _board[xCoord][yCoord];
    
    // Check Forward
    int checked = 0;
    bool checkMore = true;
    counterOfTheSameCoin = 1;// Count current coin
    while( checkMore && checked < 4){
        checkMore= false;
        int xCoordCheck = xCoord + dx;
        int yCoordCheck = yCoord + dy;
        
        if( xCoordCheck < defaultXCoordinate && xCoordCheck >= 0  && yCoordCheck < defaultYCoordinate && yCoordCheck >=0){
            if(_board[xCoordCheck][yCoordCheck]==checkValue) {
                xCoord=xCoord+dx;
                yCoord=yCoord+dy;
                checked += 1;
                counterOfTheSameCoin+=1;
                checkMore = true;
            }
        }
    }

    // Check Backwards
    xCoord = otherXCoordinate;
    yCoord = otherYCoordinate;
    checkMore = true;
    while( checkMore && checked < 4){
        checkMore= false;
        int xCoordCheck = xCoord - dx;
        int yCoordCheck = yCoord - dy;
        
        if( xCoordCheck < defaultXCoordinate && xCoordCheck >= 0  && yCoordCheck < defaultYCoordinate && yCoordCheck >=0){
            if(_board[xCoordCheck][yCoordCheck]==checkValue) {
                xCoord=xCoord-dx;
                yCoord=yCoord-dy;
                checked += 1;
                counterOfTheSameCoin+=1;
                checkMore = true;
            }
        }
    }
    if( counterOfTheSameCoin >= 4){
        didSomeoneWin = true;
    }
    
    
}
void board::playGame() {
	defineBoard();
	gameInitiate();
}
board::~board()
{
}
