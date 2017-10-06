#include <iostream>
#include <stdio.h>
#include <string>
#define NUM_OF_STICKS 20
using namespace std;

//////////////////////////////////////////////////////////
/////////////////////ALLUMETTES/////////////////////////////////////

class allumette
{
public:
	allumette(int id = 1);
	~allumette();
	char _appr = '|';
	int _id;
};

allumette::allumette(int id)
{
	_id = id;
}


allumette::~allumette()
{
}

///////////////////////////ALLUMETTES///////////////////////////////
///////////////////////////PLAYER///////////////////////////////

class player
{
public:
	player(string name = "guy");
	~player();
	string _name;
};

player::player(string name)
{
	_name = name;
}

player::~player()
{
}

////////////////////////PLAYER//////////////////////////////////
////////////////////////GAME//////////////////////////////////

class game
{
public:
	game();
	~game();
	int _fourMul;
	allumette  *_sticks = new allumette[NUM_OF_STICKS];
	int _num_of_sticks = NUM_OF_STICKS;
	void removeSticks(int num);
	void playGame();
	void printSticks();
	void playComputer();
	int checkFour(int start);
	player _player[2];
};


game::game()
{
	for(int a = 0; a < NUM_OF_STICKS; a++) {
		_sticks[a] = a + 1;
	}
}

void game::printSticks() {
	cout << "\n\n";
	for(int i = 0; i < _num_of_sticks; i++) {
		cout << _sticks[i]._appr;
	}
	cout << "\n\n";
}

void game::removeSticks(int num) {
	if(num > 3) {
		num = 3;
	}
	_num_of_sticks = _num_of_sticks - num;
	allumette *temp = new allumette[_num_of_sticks];
	delete[] _sticks;
	_sticks = temp;
	/*if(_num_of_sticks == 0) {
		_game_bool = false;
	}*/
}

int game::checkFour(int start) {
	for(int i = start; i > 0; i--)
	{
		if(i % 4 == 0) {
			_fourMul = i;
			return start - i;
			break;
		}
	}
}

void game::playComputer() {
	int turn_decider = 1;
	int turn = 2;
	while(_num_of_sticks != 0) {
		turn = turn - turn_decider;
		turn_decider = turn_decider * (-1);
		if(turn == 1) {
			printSticks();
			cout << _num_of_sticks << " d'allumettes qui restent: " << "Combien d'allumettes a enlever " << ": ";
			int temp_;
			cin >> temp_;
			removeSticks(temp_);
			cout << "\n\n";
		}
		else {
			removeSticks(checkFour(_num_of_sticks));
		}
	}
}

void game::playGame() {
	cout << "Jeu d'allumettes!\n\n";
	cout << "Nom du jouer 1: ";
	std::cin >> _player[0]._name;
	cout << "Nom du jouer 2: ";
	std::cin >> _player[1]._name;
	cout << endl;

	int turn_decider = 1;
	int turn = 2;
	while(_num_of_sticks != 0) {
		cout << "\n";
		printSticks();
		turn = turn - turn_decider;
		turn_decider = turn_decider * (-1);
		cout << _num_of_sticks << " d'allumettes qui restent: " << "Combien d'allumettes a enlever " << _player[turn - 1]._name << ": ";
		int temp_;
		cin >> temp_;
		removeSticks(temp_);
		cout << "\n\n";
	}
}

game::~game()
{
	delete[] _sticks;
}

/////////////////////////GAME/////////////////////////////////
/////////////////////////MAIN/////////////////////////////////

int main() {
	printf("Voudrez-vous jouer contre l'ordinateur ou conter un joueur (1 pour non, n'importe pour oui): ");
	int choice;
	cin >> choice;
	game myGame;
	if(choice == 1) {
		myGame.playGame();
	}
	else {
		myGame.playComputer();
	}
}

/////////////////////////MAIN/////////////////////////////////
//////////////////////////////////////////////////////////
