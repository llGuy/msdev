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

