#pragma once
#include <iostream>
#include <string>
using namespace std;
class Encrypt
{
public:
	Encrypt(string _input);
	~Encrypt();
	string _inputString;
	string _key = "@#jk)</?lk~`][{=+-0dmjd$^&";
	string _encryptedString;
	string EncryptSequence();
	string DecryptSequence();
	//int FindNumLetters(string _input);				Replaced by [string].length()
};

