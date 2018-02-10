#include "Compiler.h"



Compiler::Compiler()
{
}

int Compiler::FirstQuestion() {
	string _answ;
	cout << "~check\n~add\n~clean\n~delete\n\n";
	cin >> _answ;
	cout << endl;
	
	if(_answ == "check") return check;
	if(_answ == "add") return add;
	if(_answ == "clean") return clean;
	if(_answ == "delete") return deletepwd;
	else return 1;
}

void Compiler::deleteContent() {
	EntMAnager.clearFile();
}

void Compiler::deleteEntry() {

}

void Compiler::Add() {
	EntMAnager.UpdateVector();
	cout << "number of pwd to add: ";
	int _num_pwd = 1;
	cin >> _num_pwd;
	for(int i = 0; i < _num_pwd; i++) {
		string _temp[2];
		cout << "name: ";
		cin >> _temp[0];
		cout << "pwd: ";
		cin >> _temp[1];

		//asks for entry input: name + pwd
		EntMAnager.AddEntries(Entry(_temp[0],_temp[1]));	

		cout << endl << endl;
	}
	EntMAnager.UpdateFle();
}

void Compiler::Check() {
	EntMAnager.UpdateVector();
	EntMAnager._vec_of_ent.convString();
	cout << "number of pwd: " << EntMAnager._vec_of_ent._size << "\n";

	cout << "user,pwd;\n\n";
	for(int i = 0; i < EntMAnager._vec_of_ent._size; i++) {

		//prints to the screen every name + pwd
		cout << EntMAnager._vec_of_ent._str_pwd[i] << endl;			
	}
	// test: cout << EntMAnager._vec_of_ent._all_str;
}

void Compiler::Compile() {
	switch (FirstQuestion()) {
	case check:
		Check();
		break;
	case add:
		Add();
		break;
	case clean:
		deleteContent();
		break;
	case deletepwd:
		deleteEntry();
		break;
	}
}

Compiler::~Compiler()
{
}
