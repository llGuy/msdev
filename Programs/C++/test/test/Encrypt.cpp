#include "Encrypt.h"



Encrypt::Encrypt(string _input)
{
	_inputString = _input;
}

string Encrypt::EncryptSequence()
{
	string _initOutput = _inputString;
	int _positionOfKey = 0;
	for(int _position = 0; _position < _inputString.length(); _position++)
	{
		if(_positionOfKey != _key.length())
		{
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
	string _originalString = EncryptSequence();
	int _keyPosition = 0;
	for(unsigned _position = 0; _position < EncryptSequence().length(); _position++)
	{
		if(_keyPosition != _key.length())
		{
			_originalString[_position] = EncryptSequence()[_position]^_key[_keyPosition];
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
