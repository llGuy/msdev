#pragma once
#include "EntryManager.h"
class Compiler
{
public:
	Compiler();
	~Compiler();
	typedef enum _decision {
		check = 1,
		add = 2,
		clean = 3,
		deletepwd = 4
	};

	//Deletes entries
	void deleteEntry();

	//Deletes content that is in the file
	void deleteContent();

	//Compiles everything and puts it all together
	void Compile();

//private:
	EntryManager EntMAnager;
	int FirstQuestion();

	//Add pwd function
	void Add();
	
	//Check pwd function
	void Check();
};

#pragma once
#include "Entry.h"
#include "Encrypt.h"
#include <iostream>
#include <string>

using namespace std;
class Vector
{
public:
	Vector();
	~Vector();
	int _size;
	string *_str_pwd;
	string _all_str;

	//adds entry to vector
	void addEntry(Entry input);

	//puts all the entries.strComp() together to make 1 string
	void convString();

private:
	Entry *_arr_ent;
	int _capacity;
};

#pragma once
#include <iostream>
#include <string>
using namespace std;
class Encrypt
{
public:
	Encrypt(/*string _input*/);
	~Encrypt();

	//string that will be used for enc. process
	string _inputString;
	
	//key to Xor with pwd for encryption
	string _key = "@#jk)</?lk~`][{=+-0dmjd$^&";
	
	//string after EncryptedString
	string _encryptedString;
	
	//Encryption process
	string EncryptSequence();
	
	//Decryption process
	string DecryptSequence();
};

#pragma once
#include <iostream>
#include <string>

using namespace std;

class Entry
{
public:
	Entry(string name = "Null", string password = "Null");
	~Entry();
	string _name;
	string _pwd;

	//puts name pwd together in 1 string
	string strComp();
};

#pragma once
#include "Entry.h"
#include "Encrypt.h"
#include "Vector.h"
#include <iostream>
#include <string>
#include <fstream>
class EntryManager
{
public:
	//directory
	string kFILE = "c:\\Users\\luc\\Documents\\SourceB.txt";

	EntryManager();
	~EntryManager();

	//Adds to the vector, the entries
	void AddEntries(Entry _input);	

	//Adds vector entries to the file
	void UpdateFle();	

	void clearFile();

	//updates passwords to the vector
	void UpdateVector();

	Vector _vec_of_ent;

	//all the name,pwds from the file (decrypted)
	string _outp_fle;
};

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
#include "Encrypt.h"



Encrypt::Encrypt(/*string _input*/)
{
	//_inputString = _input;
}

string Encrypt::EncryptSequence()
{
	string _initOutput = _inputString;
	int _positionOfKey = 0;
	for(int _position = 0; _position < _inputString.length(); _position++)
	{
		//cycles through the key and Xor (^)
		if(_positionOfKey != _key.length())
		{
			//Xors current letter of the input with the corresponding position of the key
			_initOutput[_position] = _inputString[_position]^_key[_positionOfKey];
			_positionOfKey = _positionOfKey + 1;
		}
		if(_positionOfKey == _key.length())
		{
			_positionOfKey = 0;
		}
	}
	_encryptedString = _initOutput;
	return _encryptedString;
}

string Encrypt::DecryptSequence()
{
	//inverse process of EncryptSequence()

	string _originalString = _inputString;
	int _keyPosition = 0;
	for(unsigned _position = 0; _position < _originalString.length(); _position++)
	{
		if(_keyPosition != _key.length())
		{
			_originalString[_position] = _originalString[_position]^_key[_keyPosition];
			_keyPosition += 1;
		}
		if(_keyPosition == _key.length())
		{
			_keyPosition = 0;
		}
	}
	return _originalString;
}

Encrypt::~Encrypt()
{
}
#include "Entry.h"



Entry::Entry(string name, string password)
{
	_name = name;
	_pwd = password;
}

string Entry::strComp()
{
	//formats the string as name,pwd;
	return _name + "," + _pwd + ";";
}

Entry::~Entry()
{
}
#include "EntryManager.h"

using namespace std;


EntryManager::EntryManager()
{
}

void EntryManager::UpdateVector()
{
	ifstream _rd_fle;
	_rd_fle.open(kFILE/*,ios_base::binary|ifstream::in*/);
	//opens file stream
	Encrypt _enc;
	string temp;
	while(_rd_fle) {
		char c;
		_rd_fle.get(c);
		temp.push_back(c);
	}
	//sets temp as the encrypted text in kFILE
	_enc._inputString = temp;
	//sets input string = temp(encrypted text)
	_outp_fle = _enc.DecryptSequence();
	//sets _outp_fle as the decrypted text

	//equivalent to the number of entries there are
	int _int_temp = 0;

	//checks for ';' to separate all the entries - number of ';' to create array
	for(int i = 0; i < _outp_fle.length(); i++) {
		if(_outp_fle[i] == ';') {
			_int_temp += 1;
		}
	}
	//sets positions of ';' to check where to cut the string
	//coords of SC => coordinates of semi-colons
	int *_coords_of_SC = new int[_int_temp];
	//size of array of SC
	int _temp_size = 0;
	for(int i = 0; i < _outp_fle.length(); i++) {
		if(_outp_fle[i] == ';') {
			_coords_of_SC[_temp_size] = i;
			_temp_size++;
		}
	}
	
	_temp_size = 0;
	//adds each entry as a string to an array
	string *_str_of_ents = new string[_int_temp];
	for(int i = 0; i < _int_temp; i++) {
		_str_of_ents[i] = _outp_fle.substr(_temp_size, _coords_of_SC[i] - _temp_size);
		_temp_size = _coords_of_SC[i] + 1;
	}
	
	//PROCESS OF ADDING ALL THE ENTRIES TO THE VECTOR
	_temp_size = 0;
	//array to note where the ',' and ';' are in the entry
	int _new_coords[2] ={0,0};
	//array of string including name + pwd
	string _usr_pwd[2];
	for(int y = 0; y < _int_temp /*number of entries*/; y++) {
		//checks position of ',' and ';'
		for(int i = 0; i < _str_of_ents[y].length(); i++) {
			if(_str_of_ents[y][i] == ',') {
				_new_coords[0] = i;
			}
			if(_str_of_ents[y][i] == ';') {
				_new_coords[1] = i - 1;
			}
		}
			//separates the name and pwd and adds them to the vector
		if(_str_of_ents[y].size() != 0) {
			_usr_pwd[0] = _str_of_ents[y].substr(0,_new_coords[0]);
			_usr_pwd[1] = _str_of_ents[y].substr(_new_coords[0]+1,_new_coords[1] - _new_coords[0]);
			_vec_of_ent.addEntry(Entry(_usr_pwd[0],_usr_pwd[1]));
		}
		int _new_coords[2] ={ 0,0 };
	}
	_rd_fle.close();
}

void EntryManager::AddEntries(Entry _input)
{
	//adds entry to the vector
	_vec_of_ent.addEntry(_input);
}

void EntryManager::clearFile()
{
	//empties the file
	ofstream _clr_fle;
	_clr_fle.open(kFILE,std::ofstream::out | std::ofstream::trunc);
	_clr_fle.close();
}

void EntryManager::UpdateFle()
{
	//first clears the file
	clearFile();
	//converts all the entries to 1 string
	_vec_of_ent.convString();
	Encrypt _enc_obj;
	//encrypts the string
	_enc_obj._inputString = _vec_of_ent._all_str;
	ofstream _rsc_fle;
	_rsc_fle.open(kFILE /*,ofstream::trunc*/);
	//adds the string to the file
	_rsc_fle << _enc_obj.EncryptSequence();
	cout << "Encrypted string: " <<_enc_obj._encryptedString << endl << endl;
	_rsc_fle.close();
}



EntryManager::~EntryManager()
{
}
#include "Vector.h"



Vector::Vector()
{
	_capacity = 8;
	_size = 0;
	_arr_ent = new Entry[_capacity];
		
}

void Vector::addEntry(Entry input)
{
	if(_size != _capacity)
	{
		//checks if it is possible to add an entry, making sure it isn't full
		_arr_ent[_size] = input;
		_size++;
	}
	else {
		//if it is filled up, multiplies capacity of the vector by 2
		Entry *_arr_temp = new Entry[_capacity*2];
		for(int _pos = 0; _pos < _capacity; _pos++)
		{
			//adds all previous data into the new upgraded array
			_arr_temp[_pos] = _arr_ent[_pos];
		}
		delete[] _arr_ent;
		_arr_ent = _arr_temp;
	}
}

void Vector::convString()
{
	//creates array of strings
	 _str_pwd = new string[_size];
	for(int _pos = 0; _pos < _size; _pos++)
	{
		_str_pwd[_pos] = _arr_ent[_pos].strComp();
		_all_str += _str_pwd[_pos];
	}
}

Vector::~Vector()
{
}
#include "Entry.h"
#include "Encrypt.h"
#include "Vector.h"
#include "EntryManager.h"
#include "Compiler.h"

#include <iostream>
#include <string>

using namespace std;
//const string kFILE = "c:\\Users\\luc\\Desktop\\SourceB.txt";

int main()
{
	if(1) {
		Compiler ProgramCompiler;
		ProgramCompiler.Compile();
	}
	//last lol,lel;
	else {
		if(0) {
			EntryManager test;
			test.UpdateVector();
			test.AddEntries(Entry("computer","processor"));
			test.AddEntries(Entry("piano","chopin"));
			test.UpdateFle();
		}
		else {
			Compiler testComp;
			testComp.Check();
		}
	}
}
