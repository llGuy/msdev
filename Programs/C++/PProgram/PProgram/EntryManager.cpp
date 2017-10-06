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
